#ifndef XMTOOLKIT_H
#define XMTOOLKIT_H
//0X0410 for Windows 98, 0x0500 for Windows 2000
//0x0501 for Windows XP, 0x0502 for Windows Server 2003,
//0x0600 for Windows Vista, 0x0601 for Windows 7.
//http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#define UNICODE
#define _UNICODE
#ifndef _WIN32_WINDOWS
#define  _WIN32_WINDOWS 0x0501 //unicode solo para XP y superiores
#endif
//#define _WIN32_IE 0x0501//Para el InitCommonControls y otros
#include <windows.h>
//#include <commctrl.h>
#include "String.h"
#include "algorithms/LinkedList.h"

namespace XmToolKit{
    struct stSize
    {
        int x;
        int y;
        int width;
        int height;
        stSize(){
            x=y=width=height=0;
        }
        stSize(int _x, int _y, int _width,int _height){
            x=_x;
            y=_y;
            width=_width;
            height=_height;
        }
    };
    stSize GetWindowPos(HWND hwnd);
    int mainLoop(HWND hwnd);
    int mainLoop();
    void doEvents();
    wchar_t* toUTF16(const char* utf8);
    char* toUTF8(wchar_t* utf16);
    void init(int argc,char**args);
    #include "EventListener.h"
    #include "Event.h"
    #include "Widget.h"
    #include "Container.h"
    #include "Window.h"
    #include "Button.h"
    #include "LinearContainer.h"
}
#endif // XMTOOLKIT_H
