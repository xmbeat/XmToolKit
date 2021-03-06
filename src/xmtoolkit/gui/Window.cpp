#include "XmToolKit.h"
#include "Window.h"
#include "EventListener.h"
#include "Event.h"
#include "GUIException.h"
namespace XmToolKit {

//PRIVATE
//Sirve para aplicar un bloqueo a las ventanas padres de esta, para cuando es modal
	void Window::unLockParent(Window* parent) {
		Iterator<Window*> *iterator = mParents.iterator();
		//Liberamos todos los padres
		if (parent == NULL) {
			while (iterator->hasNext()) {
				iterator->next()->unLock();
			}
			mParents.clear();
		} //Liberamos solo un padre
		else {
			if (mParents.remove(parent)) {
				parent->unLock();
			}
		}
	}
//Sirve para desbloquear las ventanas padres de esta, para cuando es modal
	void Window::lockParent() {
		unLockParent();
		Iterator<Window*> *iterator = ventanas.iterator();
		while (iterator->hasNext()) {
			Window *ventana = iterator->next();
			if (ventana != this) {
				//Si la ventana tenia bloqueada a esta, la desbloqueamos primero
				ventana->unLockParent(this);
				//Bloqueamos la ventana
				ventana->lock();
				mParents.add(ventana);
			}
		}
		if (mParent) {
			this->setOwner(*mParent);
		}
		else {
			this->setOwner(NULL);
		}
	}
	void Window::lock() {
		mLocks++;
		if (mLocks == 1) {
			EnableWindow(*this, false);
		}
	}
	void Window::unLock() {
		mLocks--;
		if (mLocks <= 0) {
			mLocks = 0;
			EnableWindow(*this, true);
		}
	}
	bool Window::isLocked() {
		return mLocks > 0;
	}
	void Window::setOwner(HWND hwnd) {
		SetWindowLongPtr(*this, GWLP_HWNDPARENT, (LONG_PTR) hwnd);
	}

//PUBLIC:
	Window::~Window() {
	}
	Window::Window(const char* title) :
			mParent(NULL), mChild(NULL), mIsModal(false), mCloseType(HIDE_ON_CLOSE), mLocks(0), mWindowListener(0), mIsDeleteable(true), mIsVisibleInTaskBar(
					true), mIsFullScreen(false) {
		if (!mainWindow) {
			WNDCLASSEXW wndClass;
			wndClass.lpszMenuName = NULL;
			wndClass.lpszClassName = CLASS_NAME;
			wndClass.lpfnWndProc = WindowProcedure;
			wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
			wndClass.cbWndExtra = 0;
			wndClass.cbClsExtra = 0;
			wndClass.hInstance = instance;
			wndClass.hbrBackground = NULL;
			wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndClass.cbSize = sizeof(wndClass);
			if (!RegisterClassExW(&wndClass)) {
				throw GUIException("Win32::RegisterClassEx failed to create Window widget");
			}
			mainWindow = CreateWindowExW(0, CLASS_NAME, NULL, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, instance, 0);
		}

		wchar_t *realTitle = toUTF16(title);
		this->setHwnd(
				CreateWindowExW(WS_EX_APPWINDOW, CLASS_NAME, realTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT,
						200, 200, 0, NULL, instance, NULL));
		delete realTitle;
		topWindowsCount++;
		ventanas.add(this);
		SendMessage(*this, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), TRUE);
		SetWindowLongPtr(this->mHandle, GWLP_USERDATA, (LONG_PTR) this);
		//SetProp(this->mHandle,"this",this);
		//Calculamos el valor del tamano minimo de la ventana
		this->setMinimumSize(GetSystemMetrics(SM_CXMINTRACK), SM_CYMINTRACK);
	}

	void Window::setPosition(int x, int y) {
		Widget::setPosition(this, x, y);
	}
	void Window::getPosition(int *x, int*y) {
		Widget::getPosition(this, x, y);
	}
	void Window::setDefaultCloseOperation(int mode) {
		mCloseType = mode;
	}
	bool Window::isModal() {
		return mIsModal;
	}

	void Window::setModal(bool value, Window* modalParent) {
		mParent = modalParent;
		if (value != mIsModal) {
			if (value) {
				topWindowsCount++;
			}
			else {
				topWindowsCount--;
			}
			mIsModal = value;
		}
	}

	void Window::setVisible(bool value) {
		bool current = isVisible();
		if (value != current) {
			if (value) {
				if (mIsModal) //Si esta mostrandose y es modal la ventana
				{
					lockParent(); //Bloqueamos las ventanas asociadas con su modalidad
				}
				else if (mIsVisibleInTaskBar) {
					this->setOwner(NULL);
				}
				else {
					this->setOwner(mainWindow);
				}

				int w, h, minW, minH;
				getMinimumSize(&minW, &minH);
				getSize(&w, &h);
				if (w < minW) {
					w = minW;
				}
				if (h < minH) {
					h = minH;
				}
				setSize(w, h);
			}
			else  //Ocultandose
			{
				//Desbloquemoas las ventnas que podrian estar bloqueadas
				unLockParent();
			}
			::ShowWindow(*this, value ? SW_SHOW : SW_HIDE);
		}
	}
	void Window::setVisibleInTaskBar(bool value) {
		bool visible = false;
		if (this->isVisible()) {
			visible = true;
			this->setVisible(false);
		}
		if (!value) {
			this->removeExStyle(WS_EX_APPWINDOW);
		}
		else {
			this->addExStyle(WS_EX_APPWINDOW);
		}
		if (visible) {
			this->setVisible(true);
		}
	}
	void Window::setIcon(/*GdkPixbuf *icon*/) {

	}
	void Window::setText(const char* text) {
		Widget::setText(text);
	}
	String Window::getText() {
		return Widget::getText();
	}

	void Window::setDeleteable(bool value) {
		HMENU hMenu;
		UINT dwExtra;
		if ((hMenu = GetSystemMenu(*this, FALSE)) == NULL)
			return;
		dwExtra = value ? MF_ENABLED : (MF_DISABLED | MF_GRAYED);
		EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | dwExtra);
		mIsDeleteable = value;
	}
	bool Window::isDeleteable() {
		return mIsDeleteable;
	}
	void Window::setFullScreen(bool fullscreen) {
		if (fullscreen == mIsFullScreen)
			return;
		// Guardamos el estado de la ventana si no se esta en modo fullscreen
		if (!mIsFullScreen) {
			// Guardamos la informacion. Forzamos a la ventana al modo restored
			// antes de hacerla fullscreen debido a que windows no esconde el
			// taskbar si la ventana esta maximizada
			WidgetState*state = saveWidgetState(::IsZoomed(*this));
			if (state->extra)
				::SendMessage(*this, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		mIsFullScreen = fullscreen;

		if (mIsFullScreen) {
			//Obtenemos el tamano del monitor
			MONITORINFO info;
			info.cbSize = sizeof(info);
			GetMonitorInfo(MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &info);
			//Animamos el movimiento
			RECT from;
			GetWindowRect(*this, &from);
			DrawAnimatedRects(*this, IDANI_CAPTION, &from, &info.rcMonitor);
			//Removemos estilos para lograr el fullscreen
			this->removeStyle(WS_CAPTION | WS_THICKFRAME);
			this->removeExStyle(WS_EX_DLGMODALFRAME |
			WS_EX_WINDOWEDGE |
			WS_EX_CLIENTEDGE |
			WS_EX_STATICEDGE);
			//Movemos la ventana
			SetWindowPos(*this, NULL, info.rcMonitor.left, info.rcMonitor.top, info.rcMonitor.right - info.rcMonitor.left,
					info.rcMonitor.bottom - info.rcMonitor.top,
					SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
		else {
			// Reset original window style and size.  The multiple window size/moves
			// here are ugly, but if SetWindowPos() doesn't redraw, the taskbar won't be
			// repainted.  Better-looking methods welcome.
			WidgetState*state = this->restoreWidgetState();
			if (state->extra) {
				::SendMessage(*this, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
			else {
				this->setPosition(state->size.x, state->size.y);
			}
		}
	}

	bool Window::isFullScreen() {
		return mIsFullScreen;
	}

	bool Window::isVisibleInTaskBar() {
		return mIsVisibleInTaskBar;
	}

	void Window::setIconFromFile(const char* path) {

	}

	void Window::setResizable(bool value) {
		this->removeStyle(WS_THICKFRAME);
	}

	bool Window::isResizable() {
		return this->existStyle(WS_THICKFRAME);
	}
	void Window::setMinButton(bool value) {
		if (value) {
			this->addStyle(WS_MINIMIZEBOX);
		}
		else {
			this->removeStyle(WS_MINIMIZEBOX);
		}
	}

	bool Window::hasMinButton() {
		return this->existStyle(WS_MINIMIZEBOX);
	}

	void Window::setMaxButton(bool value) {
		if (value) {
			this->addStyle(WS_MAXIMIZEBOX);
		}
		else {
			this->removeStyle(WS_MAXIMIZEBOX);
		}
	}

	bool Window::hasMaxButton() {
		return this->existStyle(WS_MAXIMIZEBOX);
	}
	void Window::getClientSize(int*h, int*w) {
		RECT rect;
		GetClientRect(*this, &rect);
		*h = rect.right - rect.left;
		*w = rect.bottom - rect.top;
	}
	void Window::add(Widget* widget) {
		mChild = widget;
		if (mChild) {
			Widget::setParent(widget, mHandle);
			updateContainer();
		}
	}

	void Window::updateContainer() {
		if (this->mChild) {
			int w, h;
			this->getClientSize(&w, &h);
			this->mChild->setPosition(0, 0);
			this->mChild->setSize(w, h);

		}
	}
//protected:
	LRESULT CALLBACK Window::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		//Asi sabremos de que ventana viene el mensaje
		Window *ventana = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//ventana = GetProp(hwnd,"this");
		if (ventana) {
			switch (message) {
				case WM_CLOSE: {
					if (ventana->mWindowListener) {
						ventana->mWindowListener->onWindowClose(ventana);
					}
					else {
						if (ventana->mCloseType == EXIT_ON_CLOSE) {
							PostQuitMessage(0);
						}
						else if (ventana->mCloseType == HIDE_ON_CLOSE) {
							ventana->setVisible(false);
						}
					}
					return 0;
					break;
				}
				case WM_DESTROY: {
					if (ventana->mWindowListener) {
						ventana->mWindowListener->onWindowDestroy(ventana);
					}
					break;
				}
				case WM_GETMINMAXINFO: {
					LPMINMAXINFO info = (LPMINMAXINFO) lParam;
					int minW, minH, maxW, maxH;
					ventana->getMinimumSize(&minW, &minH);
					ventana->getMaximumSize(&maxW, &maxH);
					info->ptMaxTrackSize.x = maxW <= 0 ? GetSystemMetrics(SM_CXMAXTRACK) : maxW;
					info->ptMaxTrackSize.y = maxH <= 0 ? GetSystemMetrics(SM_CYMAXTRACK) : maxH;
					info->ptMinTrackSize.x = minW <= 0 ? GetSystemMetrics(SM_CXMINTRACK) : minW;
					info->ptMinTrackSize.y = minH <= 0 ? GetSystemMetrics(SM_CYMINTRACK) : minH;
					return 0;
					break;
				}
				case WM_ACTIVATE: {
					if (wParam != WA_INACTIVE) {
						Window::activeWindow = hwnd;
					}
					else {
						//DEACTIVE
						Window::activeWindow = NULL;
					}
					break;
				}
				case WM_PAINT: {
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hwnd, &ps);
					RECT rect;

					int h, w;

					ventana->getClientSize(&w, &h);
					SetRect(&rect, 0, 0, w, h);
					HBRUSH brush = CreateSolidBrush(ventana->getBackgroundColor());
					FillRect(hdc, &rect, brush);
					DeleteObject(brush);
					SetBkMode(hdc, TRANSPARENT);
					//DrawTextExA(hdc, "Hola Mundo", -1, &rect, DT_CENTER, 0);
					EndPaint(hwnd, &ps);
					return 1;

					break;
				}
				case WM_ERASEBKGND: {
					return 1;
					break;
				}
				case WM_SIZE: {
					ventana->updateContainer();
					break;
				}
				default: {
					return Widget::WidgetProcedure(hwnd, message, wParam, lParam);
				}
			}
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

//Static Members
	LinkedList<Window*> Window::ventanas;
	HWND Window::mainWindow = 0;
	int Window::topWindowsCount = 0;
	HWND Window::activeWindow = 0;
	const wchar_t Window::CLASS_NAME[] = TEXT("XClassForm");
	const int Window::EXIT_ON_CLOSE = 1;
	const int Window::HIDE_ON_CLOSE = 2;
	const int Window::NONE_ON_CLOSE = 0;

} /* namespace XmToolKit */
