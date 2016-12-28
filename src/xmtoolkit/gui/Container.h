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
	virtual void add(Widget* widget) = 0;
	virtual ~Container();
};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_CONTAINER_H_ */
