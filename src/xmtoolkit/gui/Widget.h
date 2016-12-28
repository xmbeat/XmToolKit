
#ifndef XMTOOLKIT_GUI_WIDGET_H_
#define XMTOOLKIT_GUI_WIDGET_H_

namespace XmToolKit{
	class Widget;
}

#include "windows.h"
#include <xmtoolkit/utils/String.h>
#include "XmToolKit.h"

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif


namespace XmToolKit{
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
		static stSize GetWindowPos(HWND hwnd);
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
		static LRESULT CALLBACK WidgetProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
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
};

#endif /* XMTOOLKIT_GUI_WIDGET_H_ */
