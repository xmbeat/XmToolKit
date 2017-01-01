/*
 * Application.cpp
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#include "XmToolKit.h"
//Implementación para Windows
#ifdef _WIN32
#include <windows.h>
#include "Window.h"
int XmToolKit::mainLoop() {
	MSG msg;
	int ret;
	while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (ret == -1) {
			//ThrowException
		} else {
			if (NULL == Window::activeWindow || !IsDialogMessage(Window::activeWindow, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return msg.wParam;
}

int XmToolKit::handleEvents() {
	MSG msg;
	int ret;
	while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {
		ret = GetMessage(&msg, NULL, 0, 0);
		switch (ret) {
		case 0:
			PostQuitMessage(msg.wParam);
			break;
		case -1:
			//ThrowException
			break;
		default:
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

//Por el momento solo activa los estilos y carga los common controls v6
int XmToolKit::init(int argc, char**args) {
	HINSTANCE instance = LoadLibrary(TEXT("comctl32"));

	struct INITCOMMONCONTROLSEX {
		int dwSize;
		int dwICC;
	};
	typedef int (WINAPI *InitProc)(INITCOMMONCONTROLSEX*);
	InitProc proc = (InitProc) GetProcAddress(instance, "InitCommonControlsEx");
	if (proc) {
		INITCOMMONCONTROLSEX flags;
		flags.dwSize = sizeof(flags);
		flags.dwICC = 512; //ICC_USEREX_CLASSES;
		proc(&flags);
	}
	return 0;
}

wchar_t* XmToolKit::toUTF16(const char* utf8) {
	int length = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	if (length > 0) {
		wchar_t *buffer = new wchar_t[length];
		if (MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buffer, length) == 0) {
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

char* XmToolKit::toUTF8(wchar_t* utf16) {
	int length = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL,
	NULL);
	if (length > 0) {
		char* buffer = new char[length];
		if (WideCharToMultiByte(CP_UTF8, 0, utf16, -1, buffer, length, NULL,
		NULL) == 0) {
			delete buffer;
			return NULL;
		}
		return buffer;
	}
	return NULL;
}

//Implementación para Linux (Pendiente)
#elif __gnu_linux__

#endif
