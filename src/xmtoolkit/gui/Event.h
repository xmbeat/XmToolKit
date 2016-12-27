#ifndef EVENT_H
#define EVENT_H
#include "Widget.h"
typedef enum
{
  MASK_SHIFT    = 1 << 0,
  MASK_ALT      = 1 << 1,
  MASK_CONTROL  = 1 << 2
} MaskType;
typedef enum{
    BUTTON_LEFT = 1,
    BUTTON_MIDDLE = 2,
    BUTTON_RIGHT = 3,
}ButtonType;
//Forward Declaration
class Widget;
class Event
{
public:
    Widget* widget;
    Event():widget(0){}
    virtual ~Event() {}
};
class MouseEvent:public Event{
public:
    int x,y,wheel;
    int state;//Alt+shift+controlstate
    MouseEvent():x(0),y(0),wheel(0), state(0){}
    virtual ~MouseEvent(){}
};

class ButtonEvent:public Event{
public:
    int state;//MaskType
    int button;
    int x;
    int y;
    ButtonEvent():state(0),button(0),x(0),y(0){}
    virtual ~ButtonEvent(){}
};


class KeyEvent:public Event{
public:
    int state;
    int keycode;
    int keyval;
    KeyEvent():state(0),keycode(0),keyval(0){}
};
class ResizeEvent:public Event{
public:
    int x,y,width,height;
    ResizeEvent():x(0),y(0),width(0),height(0){}
};
#endif // EVENT_H
