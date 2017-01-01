#include <iostream>
#include "xmtoolkit/gui/ToolKit.h"
using namespace std;
using namespace XmToolKit;
class Listener:public MouseEventListener,public ButtonEventListener{
    virtual void onMouseMove(Widget*w, MouseEvent*m){
        Window*ventana = (Window*)w;
        String c = String::toBaseString(m->x,10) + ":" + String::toBaseString(m->y,10);
        ventana->setText(c);
    }
    virtual void onMouseEnter(Widget*w, MouseEvent*m){
        Window*ventana = (Window*)w;
        ventana->setDeleteable(false);
    }
    virtual void onMouseLeave(Widget*w, MouseEvent*m){
        Window*ventana = (Window*)w;
        ventana->setDeleteable(true);
    }
    virtual void onRelease(Widget* widget, ButtonEvent *event)
    {
    }
    virtual void onPress(Widget* widget, ButtonEvent *event)
    {
    }
    virtual void onClick(Widget* widget, ButtonEvent *event)
    {

    }
};

int main(int argc,char**args)
{
    XmToolKit::init(argc,args);
    Window ventana("Hola");
    Button boton("Que pasa");
    Button boton2("Hola");
    Button boton3("Mundo");
    LinearContainer container;
    Rect padding;
    Rect margin;
    ventana.setDefaultCloseOperation(Window::EXIT_ON_CLOSE);
    //ventana.setMinimumSize(200,200);
    container.add(&boton,1.0f);
    padding.left = 8;
    padding.right = 8;
    padding.top = 8;
    padding.bottom = 8;
    margin = padding;
    boton2.setMargin(margin);
    container.setPadding(padding);
    container.setSpacing(8);
    container.add(&boton2,0.0f, false, true);
    container.add(&boton3,2.0f);
    ventana.add(&container);
    ventana.setVisible(true);
    boton.setVisible(true);
    boton2.setVisible(true);
    boton3.setVisible(true);
    Listener listener;
    ventana.setMouseEventListener(&listener);
    ventana.setButtonEventListener(&listener);
    XmToolKit::mainLoop();
    return 0;
}
