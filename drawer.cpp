#include "Drawer.h"

#include "toolBar.h"
#include "toolBarBtn.h"
#include "mouseEvent.h"
#include "buttonEvent.h"
#include "paintEvent.h"
#include "line.h"
#include "rectangle.h"
#include "WindowLessAction.h"
#include "WindowLessMenu.h"


// 构造函数
Drawer::Drawer() : Widget(NULL) {
	// 设置自己的一些属性
	setText(TEXT("Drawer"));
	resize(800, 600);
	
	m_toolbar = new ToolBar(this);
	m_arrowBBtn = new ToolbarBtn(m_toolbar);
	m_lineTBBtn = new ToolbarBtn(m_toolbar);
	m_rectTBBtn = new ToolbarBtn(m_toolbar);

	m_beginPoint = new Point;

	// 绘制自己的界面
	m_arrowBBtn->setText(TEXT("Arrow"));
	m_lineTBBtn->setText(TEXT("Line"));
	m_rectTBBtn->setText(TEXT("Rect"));

	init();
	initContextMenu();
}

// 析构函数
Drawer::~Drawer() {
	if (m_memHdc)
		DeleteDC(m_memHdc);
	if (m_memBitMap)
		DeleteObject(m_memBitMap);
	ReleaseDC(getHwnd(), m_hdc);
	if (m_tempShape)
		delete m_tempShape;
	for (auto i : m_shapeList)
		delete i;
	delete m_rectTBBtn;
	delete m_lineTBBtn;
	delete m_arrowBBtn;
	delete m_toolbar;
	delete m_beginPoint;
}


/**
 * @brief 一些有意义的初始化
 */
void Drawer::init() {
	// 获取工具栏和总窗口的位置大小
	GetWindowRect(getHwnd(), &m_rc);
	GetWindowRect(m_toolbar->getHwnd(), &m_toolbarRC);

	// 计算画布大小
	int nleftUpX = m_toolbarRC.left;
	int nleftUpY = m_toolbarRC.top;
	m_nBitmapWidth = m_toolbarRC.right - m_toolbarRC.left;
	m_nBitmapHeight = m_rc.bottom - m_toolbarRC.top;
	m_flashArea.left = m_toolbarRC.left;
	m_flashArea.top = m_toolbarRC.bottom;
	m_flashArea.right = m_toolbarRC.right;
	m_flashArea.bottom = m_rc.bottom;
}

void Drawer::initContextMenu()
{
	m_pContextMenu = new WindowLessMenu(this);
	WindowLessAction* arrAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* lineAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* rectAction = new WindowLessAction(m_pContextMenu);

	arrAction->setText(L"arr");
	lineAction->setText(L"line");
	rectAction->setText(L"rect");

	m_pContextMenu->addAction(arrAction);
	m_pContextMenu->addAction(lineAction);
	m_pContextMenu->addAction(rectAction);
	m_pContextMenu->setVisiable(false);
}

/**
 * @brief 将所有图形绘制到内存画布，一次展示全部
 */
void Drawer::drawAll() {
	m_memHdc = CreateCompatibleDC(m_hdc);
	m_memBitMap = CreateCompatibleBitmap(m_hdc, m_nBitmapWidth, m_nBitmapHeight);
	static HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(m_memHdc, m_memBitMap);
	SelectObject(m_memHdc, hbrush);
	Rectangle(m_memHdc, 0, 0, m_nBitmapWidth, m_nBitmapHeight);

	// 在内存画布上画
	for (auto shape : m_shapeList) {
		shape->setHDC(m_memHdc);
		shape->draw();
	}
	// 如果临时shape也有
	if (m_tempShape) {
		m_tempShape->setHDC(m_memHdc);
		m_tempShape->draw();
	}

	// 搬到现实画布
	int loc = m_toolbarRC.bottom - m_toolbarRC.top;
	BitBlt(m_hdc, 0, loc, m_nBitmapWidth, m_nBitmapHeight, m_memHdc, 0, loc, SRCCOPY);

	// 恢复原本的HDC
	for (auto shape : m_shapeList)
		shape->setHDC(m_hdc);
	if (m_tempShape)
		m_tempShape->setHDC(m_hdc);

	// 释放对象
	DeleteObject(m_memBitMap);
	DeleteDC(m_memHdc);
}

void Drawer::dealRightBtnEvent(MouseEvent* event)
{
	Point* loc = event->getPos();
	m_pContextMenu->move(loc->x(), loc->y());
}


/**
 * @brief 处理按钮按下事件
 * @param event 事件
 * @remark 这里创建的对象
 */
void Drawer::mousePressEvent(MouseEvent* event) {	
	if (event->getButtonType() == MouseEvent::ButtonType::RIGHTBUTTON)
		dealRightBtnEvent(event);

	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;  

	// 获取鼠标开始的点
	m_beginPoint->setX(event->getPos()->x());
	m_beginPoint->setY(event->getPos()->y());

	switch (m_shapeType) {
	case Shape::ShapeType::NODEFINE:
		m_tempShape = checkAllShapeState(*m_beginPoint);
		break;
	case Shape::ShapeType::LINE: 
	{
		Line* line = new Line(m_hdc);
		line->setBegin(*m_beginPoint);
		line->setEnd(*m_beginPoint);
		m_tempShape = (Shape*)line;
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = new Rect(m_hdc);
		rect->setBegin(*m_beginPoint);
		rect->setBegin(*m_beginPoint);
		m_tempShape = (Shape*)rect;
		break;
	}
	}
}


/**
 * @brief 处理按钮移动事件
 */
void Drawer::mouseMoveEvent(MouseEvent* event) {
	// 如果不是鼠标左键按下，不处理
	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// 如果没选择任何shape，则不处理
	if (!m_tempShape)
		return;
	
	Point endPoint(event->getPos()->x(), event->getPos()->y());
	switch (m_shapeType) {
	// 工具栏为arrow模式
	case Shape::ShapeType::NODEFINE:
		if (m_tempShape->getState() == Shape::StateType::TOMOVE)
			m_tempShape->moveFunction(*m_beginPoint, endPoint);
		else if (m_tempShape->getState() == Shape::StateType::TOZOOM)
			m_tempShape->zoomFunction(*m_beginPoint, endPoint);
		m_beginPoint->setX(endPoint.x());
		m_beginPoint->setY(endPoint.y());
		break;
	case Shape::ShapeType::LINE: 
	{
		Line* line = (Line*)m_tempShape;
		line->setEnd(endPoint);
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = (Rect*)m_tempShape;
		rect->setEnd(endPoint);
		break;
	}
	}

	// 把所有的展示出来，包括容器，包括当前tempShape
	drawAll();
}


/**
 * @brief 处理按钮放开事件
 */
void Drawer::mouseReleaseEvent(MouseEvent* event) {
	if (event->getButtonType() != MouseEvent::ButtonType::LEFTBUTTON)
		return;

	// 如果当前shape为空，则不处理
	if (!m_tempShape)
		return;

	// 如果当前形状为NORMAL，则为新创建的shape，添加到list中
	if (m_tempShape->getState() == Shape::StateType::NOMAL)
		m_shapeList.push_back(m_tempShape);
	else 
		m_tempShape->setState(Shape::StateType::NOMAL);

	m_tempShape = nullptr;

	// 强制重绘，擦除临时形状，只显示paintEvent中的形状
	InvalidateRect(getHwnd(), &m_flashArea, TRUE);
}

/**
 * @brief 处理重绘事件
 */
void Drawer::paintEvent(PaintEvent* event) {
	drawAll();
}

/**
 * @brief 处理按钮按下事件
 */
void Drawer::buttonPressEvent(ButtonEvent* event) {
	int eventBtnId = event->getBtnId();

	if (m_arrowBBtn->getObjectId() == eventBtnId) {
		m_shapeType = Shape::ShapeType::NODEFINE;
	}
	else if (m_lineTBBtn->getObjectId() == eventBtnId) {
		m_shapeType = Shape::ShapeType::LINE;
	}
	else if (m_rectTBBtn->getObjectId() == eventBtnId) {
		m_shapeType = Shape::ShapeType::RECT;
	}
}

/**
 * @brief 检查当前所有shape的状态
 * @param point 鼠标点击的位置
 * @return 如果有shape被选中，返回其指针
 * @remark 可能会有很多图形都会被选中，但只选择最后一个，因为最后一个往往在最上面
 */
Shape* Drawer::checkAllShapeState(const Point& point)
{
	Shape* shape = nullptr;
	for (int i = m_shapeList.size() - 1; i >= 0; --i) {
		shape = m_shapeList[i]->checkState(point);
		if (shape)
			return shape;
	}
	return nullptr;
}

