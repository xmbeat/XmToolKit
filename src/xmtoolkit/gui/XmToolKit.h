/*
 * XmToolKit.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_XMTOOLKIT_H_
#define XMTOOLKIT_GUI_XMTOOLKIT_H_
#ifdef _WIN32
#define UNICODE
#include <windows.h>
#endif
namespace XmToolKit{
	int init(int argc, char** args);
	int mainLoop();
	int handleEvents();
	wchar_t* toUTF16(const char* utf8);
	char* toUTF8(wchar_t* utf16);

	struct Rect {
		int left;
		int top;
		int right;
		int bottom;
		Rect(){
			left = top = right = bottom = 0;
		}
	};
	struct stSize {
		int x;
		int y;
		int width;
		int height;
		stSize() {
			x = y = width = height = 0;
		}
		stSize(int _x, int _y, int _width, int _height) {
			x = _x;
			y = _y;
			width = _width;
			height = _height;
		}
	};

	class Widget;
	class Container;
	class Window;
	class Button;
	class EventListener;
	class Event;
	class MouseEvent;
	class ButtonEvent;
	class KeyEvent;
	class ResizeEvent;
	class MouseEventListener;
	class WindowEventListener;
	class ResizeEventListener;
	class ButtonEventListener;
	class KeyEventListener;
	class EventListener;
}


#endif /* XMTOOLKIT_GUI_XMTOOLKIT_H_ */
