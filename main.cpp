# include <windows.h>

#include "drawer.h"


//class MyTest : public Widget {
//public:
//	MyTest(Widget* a_parent);
//	~MyTest();
//	
//	int m_x1, m_y1, m_x2, m_y2;
//	Painter* m_painter;
//	ToolBar* tb;
//	ToolbarBtn* tbb1;
//	ToolbarBtn* tbb2;
//	HDC m_hdc;
//
//protected:
//	void buttonPressEvent(ButtonEvent* a_event) override;
//	void paintEvent(PaintEvent* a_event) override;
//	void mousePressEvent(MouseEvent* a_event) override;
//	void mouseMoveEvent(MouseEvent* a_event) override;
//
//private:
//	Button* b1;
//	
//};

//MyTest::MyTest(Widget* a_parent) : Widget(a_parent)
//{
//
//}
//MyTest::~MyTest()
//{
//	delete m_painter;
//}
//void MyTest::buttonPressEvent(ButtonEvent* a_event)
//{
//	int a = 0, b = 0;
//	switch (a_event->getType())
//	{
//	case Event::EventType::BUTTON_CLICK:
//		if (a_event->getBtnId() == b1->getObjectId())
//		{
//			// Çå³ýÁÙÊ±»æ»­µÄ
//			InvalidateRect(this->getHwnd(), NULL, TRUE);
//		}
//		else if (a_event->getBtnId() == tbb1->getObjectId())
//		{
//			MessageBox(NULL, TEXT("tbb1"), TEXT("test"), MB_OK);
//		}
//		break;
//	default:
//		break;
//	}
//}
//void MyTest::paintEvent(PaintEvent* a_event)
//{
//	Rectangle(m_hdc, 40, 40, 150, 90);
//	Ellipse(m_hdc, 40, 40, 150, 90);
//}
//void MyTest::mousePressEvent(MouseEvent* a_event)
//{
//	if (a_event->getButtonType() == MouseEvent::ButtonType::LEFTBUTTON)
//	{
//		m_x1 = a_event->getPos()->x();
//		m_y1 = a_event->getPos()->y();
//	}
//		
//}
//void MyTest::mouseMoveEvent(MouseEvent* a_event)
//{
//	if (a_event->getButtonType() == MouseEvent::ButtonType::LEFTBUTTON)
//	{
//		Rectangle(m_hdc, m_x1, m_y1, a_event->getPos()->x(), a_event->getPos()->y());
//	}
//		
//}
//

// Only for Test
#include <cmath>
#include <time.h>
#include "shape.h"
#include "line.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE , _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	Drawer drawer;

	drawer.show();


	BeginMessageLoop();
	return 0;
}


