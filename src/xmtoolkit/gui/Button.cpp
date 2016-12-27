#include "XmToolKit.h"

using namespace XmToolKit;
#include "Button.h"

Button::Button(const char* text){
    wchar_t *realText = toUTF16(text);
    this->setHwnd(CreateWindowEx(
        WS_EX_NOPARENTNOTIFY,
        TEXT("button"),
        realText,
        WS_ACTIVECAPTION | WS_CLIPSIBLINGS | WS_MAXIMIZEBOX |
        WS_TABSTOP | BS_MULTILINE | BS_PUSHBUTTON,
        0,0,0,0,NULL,NULL,Widget::instance,NULL
    ));
    SendMessage(*this,WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),TRUE);
    delete realText;
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
