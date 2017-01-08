/*
 * CheckBox.h
 *
 *  Created on: 1 ene. 2017
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_CHECKBOX_H_
#define XMTOOLKIT_GUI_CHECKBOX_H_

#include <gui/Button.h>

namespace XmToolKit {

class CheckBox: public Button {
public:
	CheckBox(const char *text = 0);
	virtual ~CheckBox();
};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_CHECKBOX_H_ */
