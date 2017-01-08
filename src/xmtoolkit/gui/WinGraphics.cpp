/*
 * WinGraphics.cpp
 *
 *  Created on: 5 ene. 2017
 *      Author: xmbeat
 */

#include "XmToolKit.h"
#include "WinGraphics.h"

#include <windows.h>
namespace XmToolKit {

	WinGraphics::WinGraphics(HDC hdc, int width, int height) {
		mHDC = CreateCompatibleDC(hdc);
		SetBkMode(mHDC, TRANSPARENT);
		SelectObject(mHDC, GetStockObject(DEFAULT_GUI_FONT));
		mBitmap = NULL;
		mRealWidth = 0;
		mRealHeight = 0;
		setSize(width, height);
		mOriginalBrush = NULL;
		mOriginalPen = NULL;
		mLineWidth = 1;
		mLineColor = 0;
	}

	WinGraphics::operator HDC (){
		return mHDC;
	}

	void * WinGraphics::getRawData(){
		return mArrayData;
	}
	void WinGraphics::getRealSize(int *width, int *height){
		if (width){
			*width = mRealWidth;
		}
		if (height){
			*height = mRealHeight;
		}
	}
	void WinGraphics::getSize(int *width, int *height){
		if (width){
			*width = mWidth;
		}
		if (height){
			*height = mHeight;
		}
	}
	void WinGraphics::setSize(int width, int height){
		mWidth = width;
		mHeight = height;
		if (width > mRealWidth || height > mRealHeight){
			int growSize = 32;
			mRealWidth = (width / growSize) * growSize  + growSize;
			mRealHeight = (height / growSize) * growSize + growSize;
			BITMAPINFO bitmapInfo = {0};
			bitmapInfo.bmiHeader.biBitCount = 32; //AARRGGBB
			bitmapInfo.bmiHeader.biCompression = BI_RGB;
			bitmapInfo.bmiHeader.biHeight = mRealWidth;
			bitmapInfo.bmiHeader.biWidth = mRealWidth;
			bitmapInfo.bmiHeader.biSizeImage = mRealWidth * mRealWidth * 4;
			bitmapInfo.bmiHeader.biPlanes = 1;
			bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
			DeleteObject(mBitmap);
			mBitmap = CreateDIBSection(mHDC, &bitmapInfo, DIB_RGB_COLORS, &mArrayData, NULL, 0);
			SelectObject(mHDC, mBitmap);
		}
	}

	void WinGraphics::drawLine(int x, int y, int x2, int y2) {
		MoveToEx(mHDC, x, y, NULL);
		LineTo(mHDC, x2, y2);
	}

	void WinGraphics::drawOval(int x, int y, int width, int height) {
		Ellipse(mHDC, x, y, x + width, y + height);
	}

	void WinGraphics::drawRect(int x, int y, int width, int height) {
		Rectangle(mHDC, x, y, x + width, y + height);
	}

	void WinGraphics::drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight) {
		RoundRect(mHDC, x, y, x + width, y + height, arcWidth, arcHeight);
	}

	void WinGraphics::drawText(const char *utf8, int x, int y, int width, int height) {
		wchar_t * utf16 = toUTF16(utf8);
		if (utf16 != NULL) {
			this->drawText(utf16, x, y, width, height);
		}
		delete utf16;
	}

	void WinGraphics::drawText(const wchar_t * utf16, int x, int y, int width, int height) {
		RECT rect;
		rect.top = y;
		rect.left = x;
		rect.bottom = y + height;
		rect.right = x + width;
		//TODO support for alignment text
		DrawTextExW(mHDC, (LPWSTR) utf16, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE, NULL);
	}

	void WinGraphics::setLineWidth(int width) {
		int style = PS_SOLID;
		if (width < 1) {
			style = PS_NULL;
		}
		HPEN pen = CreatePen(style, mLineWidth, mLineColor);
		HPEN prevPen = (HPEN) SelectObject(mHDC, pen);
		if (mOriginalPen != NULL) {
			DeleteObject(prevPen);
		}
		else {
			mOriginalPen = prevPen;
		}
	}

	int WinGraphics::getLineWidth(){
		return mLineWidth;
	}
	//TODO add support for alpha channel
	void WinGraphics::setFill(int r, int g, int b){
		int color = (b && 0xFF) | ((g && 0xFF) << 8) | ((r && 0xFF) << 16);
		this->setFill(color);
	}
	void WinGraphics::setFill(int rgb){
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH prevBrush = (HBRUSH) SelectObject(mHDC, brush);
		if (mOriginalBrush != NULL){
			DeleteObject(prevBrush);

		}
		else{
			mOriginalBrush = prevBrush;
		}
	}

	int WinGraphics::getFill(){
		LOGBRUSH brushInfo;
		GetObjectW(mHDC, sizeof(brushInfo), &brushInfo);
		return brushInfo.lbColor;
	}

	WinGraphics::~WinGraphics() {
		if (mOriginalPen != NULL) {
			DeleteObject(SelectObject(mHDC, mOriginalPen));
		}
		if (mOriginalBrush != NULL) {
			DeleteObject(SelectObject(mHDC, mOriginalBrush));
		}
		DeleteDC(mHDC);
		DeleteObject(mBitmap);
	}

} /* namespace XmToolKit */
