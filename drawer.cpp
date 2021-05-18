#include "buttonEvent.h"
#include "line.h"
#include "MouseDropEvent.h"
#include "mouseEvent.h"
#include "mouseWheelEvent.h"
#include "paintEvent.h"
#include "rectangle.h"
#include "toolBar.h"
#include "toolBarBtn.h"
#include "WindowLessAction.h"
#include "WindowLessMenu.h"

#include "Drawer.h"

namespace {
	const int verPenStyle[] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT };
	const COLORREF rgbArr[] = { RGB(255, 255, 255), 
								RGB(135, 206, 235), 
								RGB(50, 205, 50), 
								RGB(255, 215, 0), 
								RGB(255, 0, 0), };
}



// 构造函数
Drawer::Drawer() : Widget(NULL) {
	// 设置自己的一些属性
	setText(TEXT("Drawer"));
	resize(800, 600);

	m_beginPoint = new Point;

	init();
	initContextMenu();
	initGDI();
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

	delete m_beginPoint;
}




/**
 * @brief 将所有图形绘制到内存画布，一次展示全部
 */
void Drawer::drawAll() {

	Rectangle(m_memHdc, 0, 0, m_nBitmapWidth, m_nBitmapHeight);
	
	// 在内存画布上画
	for (auto shape : m_shapeList) {
		shape->draw();
	}
	// 如果临时shape也有
	if (m_tempShape) {
		m_tempShape->draw();
	}

	// 搬到现实画布
	int loc = m_toolbarRC.bottom - m_toolbarRC.top;
	BitBlt(m_hdc, 0, loc, m_nBitmapWidth, m_nBitmapHeight, m_memHdc, 0, loc, SRCCOPY);
}



/**
 * @brief 一些有意义的初始化
 */
void Drawer::init() {
	// 获取工具栏和总窗口的位置大小
	GetWindowRect(getHwnd(), &m_rc);

	// 计算画布大小
	int nleftUpX = m_toolbarRC.left;
	int nleftUpY = m_toolbarRC.top;

	m_nBitmapWidth = 800;
	m_nBitmapHeight = 600;
	m_flashArea.left = 0;
	m_flashArea.top = 0;
	m_flashArea.right = 800;
	m_flashArea.bottom = 600;
}

void Drawer::initContextMenu()
{
	m_pContextMenu = new WindowLessMenu(this);

	// 添加形状选择
	initContextMenuShapeAction();

	// 添加shape选择
	initContextMenuStyleAction();

	// 添加颜色选择
	initContextMenuColorAction();
	

	m_pContextMenu->setVisiable(false);
}

void Drawer::initGDI()
{
	m_memHdc = CreateCompatibleDC(m_hdc);
	m_memBitMap = CreateCompatibleBitmap(m_hdc, m_nBitmapWidth, m_nBitmapHeight);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(m_memHdc, hPen);
	SelectObject(m_memHdc, hbrush);
	SelectObject(m_memHdc, m_memBitMap);
}


void Drawer::initContextMenuShapeAction()
{
	WindowLessAction* arrAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* lineAction = new WindowLessAction(m_pContextMenu);
	WindowLessAction* rectAction = new WindowLessAction(m_pContextMenu);

	arrAction->setText(L"arr");
	lineAction->setText(L"line");
	rectAction->setText(L"rect");

	std::vector<WindowLessAction*> actions = { arrAction, lineAction, rectAction };
	m_pContextMenu->addActions(actions);
}

void Drawer::initContextMenuStyleAction()
{
	int lineWidth = 200;
	WindowLessAction* action = nullptr;
	Line* line = nullptr;

	for (int i = 0; i < 5; ++i)
	{
		action = new WindowLessAction(m_pContextMenu);
		line = new Line(m_hdc);
		line->resize(lineWidth, 0);
		line->getPainter()->setPenStyle(verPenStyle[i]);
		line->getPainter()->setPenWidth(1);
		action->setShape(line);
		m_pContextMenu->addAction(action);
	}
}

void Drawer::initContextMenuColorAction()
{
	std::vector<WindowLessAction*> vecColorAction;
	for (int i = 0; i < 5; ++i)
	{
		WindowLessAction* action = new WindowLessAction(m_pContextMenu);
		Rect* rect = new Rect(m_hdc);
		rect->resize(30, 30);
		rect->getPainter()->setBrushColor(rgbArr[i]);
		action->setShape(rect);
		vecColorAction.push_back(action);
	}

	m_pContextMenu->addActions(vecColorAction);
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

	// 处理右键菜单事件
	dealContextMenuAction(event);

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
		line->setHDC(m_memHdc);
		setShapePenState(line);
		line->setBegin(*m_beginPoint);
		line->setEnd(*m_beginPoint);
		m_tempShape = (Shape*)line;
		break;
	}
	case Shape::ShapeType::RECT: 
	{
		Rect* rect = new Rect(m_hdc);
		rect->setHDC(m_memHdc);
		setShapePenState(rect);
		rect->setBegin(*m_beginPoint);
		rect->setEnd(*m_beginPoint);
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

void Drawer::mouseDropEvent(MouseDropEvent* event)
{
	switch (event->getDropType())
	{
	case MouseDropEvent::DropType::LEFT2RIGHT:
		// Todo: 两个界面切换
		break;
	case MouseDropEvent::DropType::RIGHT2LEFT:
		break;
	case MouseDropEvent::DropType::TOP2BOTTOM:
		DestroyWindow(getHwnd());
		break;
	case MouseDropEvent::DropType::BOTTOM2TOP:
		// Todo: 保存图片

		break;
	default:
		break;
	}
}

void Drawer::mouseWheelEvent(MouseWheelEvent* event)
{
	int distance = event->getWheelDistance();
	m_nPenWidth += distance;
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

void Drawer::dealContextMenuAction(MouseEvent* event)
{
	int actionId = m_pContextMenu->chooseAction(event);

	switch (actionId)
	{
	case 0:
		m_shapeType = Shape::ShapeType::NODEFINE;
		break;
	case 1:
		m_shapeType = Shape::ShapeType::LINE;
		break;
	case 2:
		m_shapeType = Shape::ShapeType::RECT;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		resetPenStyle(actionId);
		break;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		resetPenColor(actionId);
		break;
	default:
		break;
	}

}

void Drawer::dealRightBtnEvent(MouseEvent* event)
{
	Point* loc = event->getPos();
	m_pContextMenu->move(loc->x(), loc->y());
}

void Drawer::resetPenStyle(int actionId)
{
	m_penStyle = verPenStyle[actionId - 3];
	m_nPenWidth = 1;                // 必须宽度为1才会有不同的样式
}

void Drawer::resetPenColor(int actionId)
{
	m_penColor = rgbArr[actionId - 8];
}

void Drawer::setShapePenState(Shape* shape)
{
	Painter* shapePainter = shape->getPainter();
	shapePainter->setPenWidth(m_nPenWidth);
	shapePainter->setPenStyle(m_penStyle);
	shapePainter->setPenColor(m_penColor);
}
