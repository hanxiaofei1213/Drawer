
#include "button.h"

#include <CommCtrl.h>

Button::Button(ShowObject* parent) : ShowObject(parent, WC_BUTTON) {
	// 创建按钮
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

	// 设置当前窗口句柄
	setNowHwnd(nowhwnd);

	// 重新设定按钮默认大小
	resize(100, 60);
	move(10, 10);
}

Button::~Button() {

}