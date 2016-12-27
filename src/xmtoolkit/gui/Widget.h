#ifndef WIDGET_H
#define WIDGET_H
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif
//Para decirle al compilador para que SO Window va solo GCC
//MSDN:
//0X0410 for Windows 98, 0x0500 for Windows 2000
//0x0501 for Windows XP, 0x0502 for Windows Server 2003,
//0x0600 for Windows Vista, 0x0601 for Windows 7.
//http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#ifndef _WIN32_WINDOWS
#define  _WIN32_WINDOWS 0x0501
#endif

#include <windows.h>
#include "XmToolKit.h"
#include "String.h"
#include "EventListener.h"
#include "Event.h"

class MouseEventListener;
class ResizeEventListener;
class ButtonEventListener;
class KeyEventListener;

class Widget
{
protected:
    HWND mRawParent;
    HWND mHandle;
    DWORD mStyle, mExStyle;
    bool mIsMouseHover;
    struct WidgetState{
        DWORD style;
        DWORD exStyle;
        stSize size;
        int extra;
    };
    static HINSTANCE instance;
    virtual WidgetState* saveWidgetState(int extra = 0);
    virtual WidgetState* getSavedWigetState();
    virtual WidgetState* restoreWidgetState();
    virtual void removeStyle(DWORD);
    virtual void addStyle(DWORD);
    virtual bool setParent(Widget* parent);
    virtual void removeExStyle(DWORD);
    virtual void addExStyle(DWORD);
    virtual bool existStyle(DWORD);
    virtual bool existExStyle(DWORD);
    virtual void setStyle(DWORD);
    virtual DWORD getStyle();
    virtual void setExStyle(DWORD);
    virtual DWORD getExStyle();
    virtual void setText(const char* text);
    virtual String getText();
    virtual void setHwnd(HWND hwnd);
    virtual void onChangeParent();
    //WindowProc, aqui se procesan los mensajes que son comunes para todos los Widget
    static LRESULT CALLBACK WidgetProcedure
        (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    //Magia: no tocar!
    static void setParent(Widget*widget, HWND parent);
    static void setPosition(Widget*widget, int x, int y);
    static void getPosition(Widget*widget, int *x, int *y);
    static void move(Widget*widget, int x, int y, int w,int h);
private:
    ResizeEventListener*mResizeListener;
    MouseEventListener*mMouseListener;
    ButtonEventListener*mButtonListener;
    KeyEventListener*mKeyListener;
    WidgetState mSaveState;
public:
    Widget();
    virtual ~Widget();
    virtual bool operator == (Widget *widget);
    virtual operator HWND();
    virtual void setVisible(bool value);
    virtual bool isVisible();
    virtual void setSize(int width, int height);
    virtual void getSize(int*width, int*height);
    virtual bool isEnabled();
    virtual void setEnabled(bool value);
    virtual String getTooltipText();
    virtual void setTooltipText(const char* text);
    virtual void getPosition(int *x, int *y);
    virtual void setPosition(int x, int y);
    virtual void getMinimumSize(int *width, int *height) = 0;
    virtual void getPreferedSize(int *width, int *height) = 0;
    //Eventos
    virtual void setMouseEventListener(MouseEventListener *listener);
    virtual void setResizeEventListener(ResizeEventListener *listener);
    virtual void setButtonEventListener(ButtonEventListener *listener);
    virtual void setKeyEventListener(KeyEventListener*listener);

 };
#endif // WIDGET_H
