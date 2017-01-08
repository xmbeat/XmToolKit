/*
 * Canvas.cpp
 *
 *  Created on: 6 ene. 2017
 *      Author: xmbeat
 */

#include "Widget.h"
#include "Canvas.h"
#include "WinGraphics.h"
#include "GUIException.h"
#include <windows.h>

namespace XmToolKit {

	LRESULT CALLBACK Canvas::CanvasProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
		Canvas *canvas = (Canvas*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);
		if (msg == WM_PAINT){
			PAINTSTRUCT ps;
			RECT rect;
			HDC hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			canvas->mGraphics->setSize(width, height);
			canvas->onDraw(canvas->mGraphics);
			BitBlt(hdc, 0, 0, width, height, *(canvas->mGraphics), 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
			return 1;
		}
		else if (msg == WM_ERASEBKGND){
			return 1;
		}
		return Widget::WidgetProcedure(hwnd, msg, wParam, lParam);
	}

	Canvas::Canvas() {
		static bool isRegistered = false;
		if (!isRegistered){
			WNDCLASSEXW canvasClass = {0};
			canvasClass.cbSize = sizeof(WNDCLASSEXW);
			canvasClass.lpfnWndProc = CanvasProc;
			canvasClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			canvasClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
			canvasClass.lpszClassName = L"XmCanvasControl";
			if (RegisterClassExW(&canvasClass) == 0){
				throw GUIException("Win32 RegisterClassExW failed!");
			}
			isRegistered = true;
		}
		HWND  hwnd = CreateWindowExW(WS_EX_STATICEDGE, L"XmCanvasControl", NULL, WS_VISIBLE, 0, 0, 0, 0, NULL, NULL, Widget::instance, NULL);
		if (hwnd == NULL){
			throw GUIException("Win32::CreateWindowExW() failed to create CanvasControl");
		}
		this->setHwnd(hwnd);
		mGraphics = new WinGraphics(GetDC(*this), 0, 0);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) this);
	}

	void Canvas::onDraw(Graphics *graphics){
		int width, height;
		graphics->getSize(&width, &height);
		graphics->setFill(mBackgroundColor);
		graphics->drawRect(0, 0, width, height);
		graphics->drawText("Hola mundo",0, 0, width, height);
	}
	//TODO Mover a Widget;
	Graphics* Canvas::getGraphics(){
		return mGraphics;
	}

	Canvas::~Canvas() {
		delete mGraphics;
	}

} /* namespace XmToolKit */
