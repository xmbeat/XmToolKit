
#include "XmToolKit.h"
#include "Button.h"
namespace XmToolKit {

Button::Button(const char* text){
    wchar_t *realText = toUTF16(text);
    wchar_t *buttonClass = toUTF16("button");
    HWND handle = CreateWindowExW(
    		WS_EX_NOPARENTNOTIFY,
    		buttonClass,
			realText,
			WS_TABSTOP | WS_CLIPSIBLINGS | BS_MULTILINE | BS_PUSHBUTTON,
			0, 0, 0, 0, NULL, NULL, Widget::instance, NULL);
    this->setHwnd(handle);
    SendMessage(*this,WM_SETFONT,(WPARAM) GetStockObject(DEFAULT_GUI_FONT), TRUE);
    delete realText;
    delete buttonClass;
}

void Button::setText(const char* text){
    Widget::setText(text);
}
String Button::getText(){
    return Widget::getText();
}

void Button::getMinimumSize(int* width, int*height){
    if (width){
        *width = 20;
    }
    if (height){
        *height = 8;
    }
}
void Button::getPreferedSize(int* width, int*height){
     if (width){
        *width = 90;
    }
    if (height){
        *height = 24;
    }
}
Button::~Button()
{
    //dtor
}


} /* namespace XmToolKit */
