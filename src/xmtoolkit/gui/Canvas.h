/*
 * Canvas.h
 *
 *  Created on: 6 ene. 2017
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_CANVAS_H_
#define XMTOOLKIT_GUI_CANVAS_H_
#include "Widget.h"
#include "WinGraphics.h"
#include <windows.h>
namespace XmToolKit {

	class Canvas:public Widget {
		protected:
			WinGraphics *mGraphics;
			static LRESULT CALLBACK CanvasProc(HWND, UINT, WPARAM, LPARAM);
		public:
			Canvas();
			virtual void onDraw(Graphics *graphics);
			virtual Graphics* getGraphics();
			virtual ~Canvas();
	};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_CANVAS_H_ */
