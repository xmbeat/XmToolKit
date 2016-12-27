#include "XmToolKit.h"
XmToolKit::stSize XmToolKit::GetWindowPos(HWND hwnd)
{
    RECT rect;
    POINT Pos;
    stSize Ret;
    GetWindowRect(hwnd,&rect);
    Pos.x=rect.left;
    Pos.y=rect.top;
    ScreenToClient(GetParent(hwnd),&Pos);
    Ret.x=Pos.x;
    Ret.y=Pos.y;
    Ret.width=rect.right - rect.left;
    Ret.height=rect.bottom - rect.top;
    return Ret;
}

int XmToolKit::mainLoop(HWND hwnd){
    MSG msg;
    int ret;
    while((ret=GetMessageA(&msg,NULL,0,0))!=0 ){
        if (ret==-1){
            //throw AppException("Application::MainLoop()");
        }
        else
        {
            if (!IsDialogMessage(hwnd,&msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return msg.wParam;
}

int XmToolKit::mainLoop(){
    MSG msg;
    int ret;
    while((ret=GetMessage(&msg,NULL,0,0))!=0){
        if (ret==-1){
            //throw AppException("Application::MainLoop()");
        }
        else if (NULL == Window::activeWindow || !IsDialogMessage(Window::activeWindow, &msg)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}

void XmToolKit::doEvents(){
    MSG uMsg;
    while(PeekMessageW(&uMsg,0,0,0,0)){
        switch (GetMessage(&uMsg,0,0,0)){
            case 0:
                PostQuitMessage(uMsg.wParam);
                return;
            case -1:
                //throw AppException("Application::DoEvents()");
                break;
            default:
                TranslateMessage(&uMsg);
                DispatchMessage(&uMsg);
        }
    }
}


wchar_t* XmToolKit::toUTF16(const char* utf8){
    int length = MultiByteToWideChar(CP_UTF8,0,utf8,-1,NULL,0);
    if (length>0){
        wchar_t *buffer = new wchar_t[length];
        if (MultiByteToWideChar(CP_UTF8,0,utf8,-1,buffer,length)==0){
            //if (GetLastError()==ERROR_NO_UNICODE_TRANSLATION){
                //throw ConvertionException("BLALA");
            //}
            delete buffer;
            return NULL;
        }
        return buffer;
    }
    return NULL;
}

char* XmToolKit::toUTF8(wchar_t* utf16){
    int length = WideCharToMultiByte(CP_UTF8,0,utf16,-1,NULL,0,NULL,NULL);
    if (length>0){
        char* buffer = new char[length];
        if(WideCharToMultiByte(CP_UTF8,0,utf16,-1,buffer,length,NULL,NULL)==0){
            delete buffer;
            return NULL;
        }
        return buffer;
    }
    return NULL;
}
//Por el momento solo activa los estilos y carga los common controls v6
void XmToolKit::init(int argc,char**args){
    HINSTANCE instance = LoadLibrary(TEXT("comctl32"));
    struct INITCOMMONCONTROLSEX{
        int dwSize;
        int dwICC;
    };
    typedef int (WINAPI *InitProc)(INITCOMMONCONTROLSEX*);
    InitProc proc = (InitProc)GetProcAddress(instance,"InitCommonControlsEx");
    if (proc){
        INITCOMMONCONTROLSEX flags;
        flags.dwSize = sizeof(flags);
        flags.dwICC = 512;//ICC_USEREX_CLASSES;
        proc(&flags);
    }
}
