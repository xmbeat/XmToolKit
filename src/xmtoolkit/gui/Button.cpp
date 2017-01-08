#include "XmToolKit.h"
#include "Button.h"
namespace XmToolKit {

	Button::Button(const char* text) {
		wchar_t *realText = toUTF16(text);
		wchar_t *buttonClass = toUTF16("button");
		HWND handle = CreateWindowExW(
				WS_EX_NOPARENTNOTIFY,
				TEXT("button"),
				realText,
				WS_TABSTOP | WS_CLIPSIBLINGS | BS_MULTILINE | BS_PUSHBUTTON,
				0, 0, 0, 0,
				NULL, NULL,
				Widget::instance,
				NULL);
		this->setHwnd(handle);
		this->setMinimumSize(24, 14);
		this->setPreferedSize(80, 24);
		SendMessage(*this, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), TRUE);
		delete realText;
		delete buttonClass;
	}

	Button::~Button() {
		//dtor
	}
	LRESULT CALLBACK Button::ButtonProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	}

} /* namespace XmToolKit */
