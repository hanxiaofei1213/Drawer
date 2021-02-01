
#include "button.h"

#include <CommCtrl.h>

Button::Button(ShowObject* parent) : ShowObject(parent, WC_BUTTON) {
	// ������ť
	HWND nowhwnd = CreateWindow(
		WC_BUTTON,
		getWindowName(),
		getStyle(),
		getLoc()->x(), getLoc()->y(), getWidth(), getHeight(),
		getParentHwnd(),
		(HMENU)getObjectId(),
		getInstance(),
		NULL
	);

	// ���õ�ǰ���ھ��
	setNowHwnd(nowhwnd);

	// �����趨��ťĬ�ϴ�С
	resize(100, 60);
	move(10, 10);
}

Button::~Button() {

}