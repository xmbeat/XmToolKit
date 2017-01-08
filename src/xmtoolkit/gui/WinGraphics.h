/*
 * WinGraphics.h
 *
 *  Created on: 5 ene. 2017
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_WINGRAPHICS_H_
#define XMTOOLKIT_GUI_WINGRAPHICS_H_

#include "Graphics.h"
#include <windows.h>
namespace XmToolKit {

	class WinGraphics: public Graphics {
		private:
			HDC mHDC;
			HBITMAP mBitmap;
			void * mArrayData;
			int mWidth;
			int mHeight;
			int mRealWidth;
			int mRealHeight;
			HBRUSH mOriginalBrush;
			HPEN mOriginalPen;
			int mLineWidth;
			int mLineColor;
		public:
			WinGraphics(HDC hdc, int width, int height);
			virtual void getSize(int *width, int *height);
			virtual void setSize(int width, int height);
			virtual void getRealSize(int *width, int *height);
			virtual operator HDC();
			virtual void*  getRawData();
			virtual void drawText (const wchar_t * utf16, int x, int y, int width, int height);
			virtual void drawText(const char * utf8, int x, int y, int width, int height);
			virtual void drawLine(int x, int y, int x2, int y2);
			virtual void drawOval(int x, int y, int width, int height);
			virtual void drawRect(int x, int y, int width, int height);
			virtual void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);
			virtual void setFill(int r, int g, int b);
			virtual void setFill(int rgba);
			virtual int getFill();
			virtual void setLineWidth(int width);
			virtual int getLineWidth();
			virtual ~WinGraphics();
	};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_WINGRAPHICS_H_ */
