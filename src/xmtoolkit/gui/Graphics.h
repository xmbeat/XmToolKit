/*
 * Graphics.h
 *
 *  Created on: 5 ene. 2017
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_GRAPHICS_H_
#define XMTOOLKIT_GUI_GRAPHICS_H_
namespace XmToolKit {

	class Graphics {
		public:
			Graphics(){}
			virtual void getSize(int *width, int *height) = 0;
			virtual void drawText (const wchar_t * utf16, int x, int y, int width, int height) = 0;
			virtual void drawText(const char *utfText, int x, int y, int width, int height) = 0;
			virtual void drawLine(int x, int y, int x2, int y2) = 0;
			virtual void drawOval(int x, int y, int width, int height) = 0;
			virtual void drawRect(int x, int y, int width, int height) = 0;
			virtual void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight) = 0;
			virtual void setFill(int r, int g, int b) = 0;
			virtual void setFill(int rgb) = 0;
			virtual int getFill() = 0;
			virtual void setLineWidth(int width) = 0;
			virtual int getLineWidth() = 0;
			virtual ~Graphics(){}
	};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_GRAPHICS_H_ */
