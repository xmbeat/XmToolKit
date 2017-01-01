/*
 * Container.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_CONTAINER_H_
#define XMTOOLKIT_GUI_CONTAINER_H_
#include "Widget.h"
namespace XmToolKit {

class Container: public Widget {
public:
	Container();
	virtual void add(Widget* widget) = 0;
	virtual void setPadding(const Rect &rect);
	virtual void getPadding(Rect *rect);
	virtual Rect getPadding();
	virtual void setSpacing(int space);
	virtual int getSpacing();
	virtual ~Container();
protected:
	Rect mPadding;
	int mSpacing;
};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_CONTAINER_H_ */
