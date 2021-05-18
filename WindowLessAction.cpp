#include "painter.h"
#include "rectangle.h"
#include "shape.h"
#include "size.h"
#include "WindowLessAction.h"

class WindowWidget;

namespace {
	const int SHAPE_PADING = 5;
}

WindowLessAction::WindowLessAction(WindowLessWidget* parent) : WindowLessWidget(parent)
{

}

WindowLessAction::~WindowLessAction()
{
	if (m_shape)
		delete m_shape;
}

void WindowLessAction::show()
{
	WindowLessWidget::show();

	if (m_pText)
	{
		getPainter()->drawText(m_pText, getRect());
		return;
	}

	if (m_shape)
	{
		checkShapeSize();
		checkShapeLoc();
		m_shape->draw();
	}
	
}

void WindowLessAction::checkShapeSize()
{
	if (!m_shape)
		return;

	int width = getWidth();
	int height = getHeight();

	Size shapeSize = m_shape->getSize();
	shapeSize.setWidth(shapeSize.getWidth() < width - SHAPE_PADING ? shapeSize.getWidth() : width - SHAPE_PADING);
	shapeSize.setHeight(shapeSize.getHeight() < height - SHAPE_PADING ? shapeSize.getHeight() : height - SHAPE_PADING);

	m_shape->resize(shapeSize.getWidth(), shapeSize.getHeight());
}

void WindowLessAction::checkShapeLoc()
{
	Point& actionLoc = getLoc();
	int actionWidth = getWidth();
	int actionHeight = getHeight();
	Size shapeSize = m_shape->getSize();
	
	int diffWidth = (actionWidth - shapeSize.getWidth()) / 2;
	int diffHeight = (actionHeight - shapeSize.getHeight()) / 2;

	Point shapeNewLoc = {actionLoc.x() + diffWidth, actionLoc.y() + diffHeight};

	m_shape->moveFunction(*m_shape->getBegin(), shapeNewLoc);
}

