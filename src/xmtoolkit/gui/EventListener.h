/*
 * EventListener.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_EVENTLISTENER_H_
#define XMTOOLKIT_GUI_EVENTLISTENER_H_
#include "XmToolKit.h"
namespace XmToolKit {

class MouseEventListener {
public:
	virtual void onMouseMove(Widget*, MouseEvent*)=0;
	virtual void onMouseEnter(Widget*, MouseEvent*)=0;
	virtual void onMouseLeave(Widget*, MouseEvent*)=0;
	virtual ~MouseEventListener() {
	}
};

class WindowEventListener {
public:
	virtual void onWindowDestroy(Widget*)=0;
	virtual void onWindowClose(Widget*)=0;
	virtual void onWindowActivate(Widget*) = 0;
	virtual ~WindowEventListener() {
	}
};

class ResizeEventListener {
public:
	virtual void onResize(Widget* widget, ResizeEvent *event)=0;
	virtual ~ResizeEventListener() {
	}
};

class ButtonEventListener {
public:
	virtual void onRelease(Widget*, ButtonEvent*)=0;
	virtual void onPress(Widget* widget, ButtonEvent *event)=0;
	virtual void onClick(Widget* widget, ButtonEvent *event) = 0;
	virtual ~ButtonEventListener() {
	}
};

class KeyEventListener {
public:
	virtual void onKeyPress(Widget* widget, KeyEvent *event) = 0;
	virtual void onKeyRelease(Widget* widget, KeyEvent *event) = 0;
	virtual ~KeyEventListener() {
	}
};

class EventListener: public MouseEventListener,
		public WindowEventListener,
		public ButtonEventListener,
		public ResizeEventListener,
		public KeyEventListener{
public:
	virtual void onResponse(Widget* dialog, int id) {
	}
	virtual void onFileSet(Widget* widget) {
	}
	virtual void onCursorChanged(Widget *widget) {
	}
	virtual void onActivate(Widget* menu) {
	}
	virtual void onChangeValue(Widget *spinbutton/*, GtkScrollType arg1*/) {
	}
	virtual void onChange(Widget *button) {
	}
	virtual void onToggled(Widget *button) {
	}
	virtual void onClick(Widget* widget, ButtonEvent*event) {
	}
	virtual void onMouseMove(Widget* widget, MouseEvent *event) {
	}
	virtual void onMouseEnter(Widget* widget, MouseEvent *event) {
	}
	virtual void onMouseLeave(Widget* widget, MouseEvent *event) {
	}
	virtual void onRelease(Widget* widget, ButtonEvent *event) {
	}
	virtual void onPress(Widget* widget, ButtonEvent *event) {
	}
	virtual void onKeyPress(Widget* widget, KeyEvent *event) {
	}
	virtual void onKeyRelease(Widget* widget, KeyEvent *event) {
	}
	virtual void onWindowDestroy(Widget* widget) {
	}
	virtual void onWindowClose(Widget *widget) {
	}
	virtual void onResize(Widget* widget, ResizeEvent *event) {
	}
	virtual void onChangePage(Widget*widget) {
	}

};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_EVENTLISTENER_H_ */
