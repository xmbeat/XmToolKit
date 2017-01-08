#include "XmToolKit.h"
#include "Widget.h"
#include "Event.h"
#include "EventListener.h"
namespace XmToolKit {

//STATIC FIELDS
	int Widget::MAX_SIZE = -1;

	stSize Widget::GetWindowPos(HWND hwnd) {
		RECT rect;
		POINT Pos;
		stSize Ret;
		GetWindowRect(hwnd, &rect);
		Pos.x = rect.left;
		Pos.y = rect.top;
		ScreenToClient(GetParent(hwnd), &Pos);
		Ret.x = Pos.x;
		Ret.y = Pos.y;
		Ret.width = rect.right - rect.left;
		Ret.height = rect.bottom - rect.top;
		return Ret;
	}
	Widget::WidgetState* Widget::saveWidgetState(int extra) {
		mSaveState.style = getStyle();
		mSaveState.exStyle = getExStyle();
		mSaveState.extra = extra;
		mSaveState.size = GetWindowPos(*this);
		return &mSaveState;
	}
	Widget::WidgetState* Widget::getSavedWigetState() {
		return &mSaveState;
	}
	Widget::WidgetState* Widget::restoreWidgetState() {
		this->setStyle(mSaveState.style);
		this->setExStyle(mSaveState.exStyle);
		this->setSize(mSaveState.size.width, mSaveState.size.height);
		return &mSaveState;
	}
	bool Widget::existStyle(DWORD style) {
		return (getStyle() & style) == style;
	}

	bool Widget::existExStyle(DWORD exStyle) {
		return (getExStyle() & exStyle) == exStyle;
	}

	void Widget::addExStyle(DWORD exStyle) {
		setExStyle(getExStyle() | exStyle);
	}

	void Widget::removeExStyle(DWORD exStyle) {
		setExStyle(getExStyle() & ~exStyle);
	}

	void Widget::addStyle(DWORD style) {
		setStyle(getStyle() | style);
	}

	void Widget::removeStyle(DWORD style) {
		setStyle(getStyle() & ~style);
	}
	void Widget::setExStyle(DWORD exStyle) {
		mExStyle = exStyle;
		if (IsWindow(mHandle))
			SetWindowLongPtr(mHandle, GWL_EXSTYLE, mExStyle);
	}
	DWORD Widget::getExStyle() {
		if (IsWindow(mHandle))
			mExStyle = GetWindowLongPtr(mHandle, GWL_EXSTYLE);
		return mExStyle;
	}
	void Widget::setStyle(DWORD style) {
		mStyle = style;
		if (IsWindow(mHandle))
			SetWindowLongPtr(mHandle, GWL_STYLE, mStyle);
	}
	DWORD Widget::getStyle() {
		if (IsWindow(mHandle))
			mStyle = GetWindowLongPtr(mHandle, GWL_STYLE);
		return mStyle;
	}

	void Widget::setMargin(const Rect &rect) {
		mMargin = rect;
	}

	void Widget::getMargin(Rect *rect) {
		*rect = mMargin;
	}

	void Widget::setPosition(Widget* widget, int x, int y) {
		::SetWindowPos(*widget, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	}
	void Widget::getPosition(Widget* widget, int *x, int*y) {
		stSize pos = GetWindowPos(*widget);
		if (x) {
			*x = pos.x;
		}
		if (y) {
			*y = pos.y;
		}
	}
	void Widget::getPosition(int *x, int*y) {
		if (mHandle) {
			getPosition(this, x, y);
		}
		else {
			if (x) {
				*x = mX;
			}
			if (y) {
				*y = mY;
			}
		}
	}
	void Widget::setPosition(int x, int y) {
		mX = x;
		mY = y;
		if (mHandle) {
			setPosition(this, x, y);
		}
	}
	bool Widget::setParent(Widget*parent) {
		return ::SetParent(*this, *parent) != 0;
	}
	void Widget::setHwnd(HWND hwnd) {
		mHandle = hwnd;
	}
	bool Widget::operator ==(Widget *widget) {
		return (HWND) *this == (HWND) *widget;
	}
	Widget::operator HWND() {
		return mHandle;
	}
	void Widget::setVisible(bool value) {
		ShowWindow(*this, value ? SW_SHOWNA : SW_HIDE);
	}
	bool Widget::isVisible() {
		return existStyle(WS_VISIBLE);
	}

	void Widget::setMinimumSize(int width, int height) {
		mMinWidth = width;
		mMinHeight = height;
	}

	void Widget::getMinimumSize(int *width, int *height) {
		if (width) {
			*width = mMinWidth;
		}
		if (height) {
			*height = mMinHeight;
		}
	}

	void Widget::setMaximumSize(int width, int height) {
		mMaxWidth = width;
		mMaxHeight = height;
	}

	void Widget::getMaximumSize(int *width, int* height) {
		if (width) {
			*width = mMaxWidth;
		}
		if (height) {
			*height = mMaxHeight;
		}
	}

	void Widget::setPreferedSize(int width, int height) {
		mPreferedWidth = width;
		mPreferedHeight = height;
	}

	void Widget::getPreferedSize(int *width, int *height) {
		if (width) {
			*width = mPreferedWidth;
		}
		if (height) {
			*height = mPreferedHeight;
		}
	}

	void Widget::setSize(int width, int height) {
		stSize pos = GetWindowPos(*this);
		MoveWindow(mHandle, pos.x, pos.y, width, height, true);
	}
	void Widget::getSize(int*width, int*height) {
		stSize pos = GetWindowPos(*this);
		*width = pos.width;
		*height = pos.height;
	}
	bool Widget::isEnabled() {
		return !existStyle(WS_DISABLED);
	}
	void Widget::setEnabled(bool value) {
		if (value)
			addStyle(WS_DISABLED);
		else
			removeStyle(WS_DISABLED);
	}
	String Widget::getTooltipText() {
		return "Nothing here";
	}
	void Widget::setTooltipText(const char* text) {
		/*tooltip*/
	}

	void Widget::setText(const char* text) {
		wchar_t*realText = toUTF16(text);
		SendMessage(*this, WM_SETTEXT, 0, (LPARAM) realText);
		delete realText;
	}
	String Widget::getText() {
		int size = SendMessage(*this, WM_GETTEXTLENGTH, 0, 0);
		wchar_t *buffer = new wchar_t[size + 1];
		SendMessage(*this, WM_GETTEXT, size + 1, (LPARAM) buffer);
		char* utf8 = toUTF8(buffer);
		String ret(utf8);
		delete buffer;
		delete utf8;
		return ret;
	}
	void Widget::move(Widget* widget, int x, int y, int w, int h) {
		MoveWindow(*widget, x, y, w, h, true);
	}
	Widget::Widget() :
			mRawParent(0), mHandle(0), mStyle(0), mExStyle(0), mIsMouseHover(false), mMinHeight(0), mMinWidth(0), mMaxHeight(
					0), mMaxWidth(0), mPreferedWidth(0), mPreferedHeight(0), mWidth(0), mHeight(0), mX(0), mY(0), mBackgroundColor(
					0), mResizeListener(0), mMouseListener(0), mButtonListener(0), mKeyListener(0) {
		LOGBRUSH object;
		if (GetObjectW(GetSysColorBrush(COLOR_BTNFACE), sizeof(object), &object) > 0) {
			mBackgroundColor = object.lbColor;
		}

	}
	Widget::~Widget() {
		if (mHandle && IsWindow(mHandle)) {
			DestroyWindow(mHandle);
		}
	}

	void Widget::setMouseEventListener(MouseEventListener *listener) {
		mMouseListener = listener;
	}
	void Widget::setResizeEventListener(ResizeEventListener *listener) {
		mResizeListener = listener;
	}
	void Widget::setButtonEventListener(ButtonEventListener *listener) {
		mButtonListener = listener;
	}
	void Widget::setKeyEventListener(KeyEventListener*listener) {
		mKeyListener = listener;
	}
	HINSTANCE Widget::instance = GetModuleHandle(NULL);

	LRESULT CALLBACK Widget::WidgetProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		Widget *widget = (Widget*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (message) {
			case WM_MOUSEMOVE: {
				if (!widget->mIsMouseHover) {
					widget->mIsMouseHover = true;
					TRACKMOUSEEVENT tmevent;
					tmevent.cbSize = sizeof(TRACKMOUSEEVENT);
					tmevent.dwFlags = TME_LEAVE;
					tmevent.hwndTrack = *widget;
					TrackMouseEvent(&tmevent);
					if (widget->mMouseListener) {
						MouseEvent event;
						event.x = GET_X_LPARAM(lParam);
						event.y = GET_Y_LPARAM(lParam);
						event.state = (int) wParam;
						event.widget = widget;
						widget->mMouseListener->onMouseEnter(widget, &event);
					}
				}
				if (widget->mMouseListener) {
					MouseEvent event;
					event.x = GET_X_LPARAM(lParam);
					event.y = GET_Y_LPARAM(lParam);
					event.state = (int) wParam;
					event.widget = widget;
					widget->mMouseListener->onMouseMove(widget, &event);
				}
				break;
			}
			case WM_MOUSELEAVE: {
				widget->mIsMouseHover = false;
				if (widget->mMouseListener) {
					MouseEvent event;
					event.x = GET_X_LPARAM(lParam);
					event.y = GET_Y_LPARAM(lParam);
					event.state = (int) wParam;
					event.widget = widget;
					widget->mMouseListener->onMouseLeave(widget, &event);
				}
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP: {
				if (widget->mButtonListener) {
					ButtonEvent event;
					event.x = GET_X_LPARAM(lParam);
					event.y = GET_Y_LPARAM(lParam);
					if ((wParam & MK_ALT) == MK_ALT) {
						event.state |= MASK_ALT;
					}
					if ((wParam & MK_CONTROL) == MK_CONTROL) {
						event.state |= MASK_CONTROL;
					}
					if ((wParam & MK_SHIFT) == MK_SHIFT) {
						event.state |= MASK_SHIFT;
					}
					switch (message) {
						case WM_LBUTTONUP:
						case WM_LBUTTONDOWN:
							event.button = BUTTON_LEFT;
							break;
						case WM_RBUTTONDOWN:
						case WM_RBUTTONUP:
							event.button = BUTTON_RIGHT;
							break;
						case WM_MBUTTONDOWN:
						case WM_MBUTTONUP:
							event.button = BUTTON_MIDDLE;
							break;
					}

					if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN) {
						widget->mButtonListener->onPress(widget, &event);
					}
					else {
						widget->mButtonListener->onRelease(widget, &event);
						widget->mButtonListener->onClick(widget, &event);
					}
					break;
				}
				break;
			}
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	void Widget::setBackgroundColor(int color) {
		mBackgroundColor = color;
	}
	int Widget::getBackgroundColor() {
		return mBackgroundColor;
	}

//Magia:no tocar!
	void Widget::setParent(Widget* widget, HWND parent) {
		widget->mRawParent = parent;
		::SetParent(*widget, parent);
		::SetWindowLongPtr(*widget, GWL_STYLE,
				(GetWindowLongPtr(*widget, GWL_STYLE) | WS_CHILD) & ~(WS_BORDER | WS_CAPTION | WS_DLGFRAME));

		widget->onChangeParent();
	}

	void Widget::onChangeParent() {
	}

} /* Namespace XmToolKit*/
