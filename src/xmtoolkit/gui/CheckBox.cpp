/*
 * CheckBox.cpp
 *
 *  Created on: 1 ene. 2017
 *      Author: xmbeat
 */

#include <gui/CheckBox.h>

namespace XmToolKit {

CheckBox::CheckBox(const char *text):Button(text) {
	this->setStyle(BS_PUSHBUTTON | BS_TEXT | BS_DEFPUSHBUTTON | BS_CHECKBOX | BS_AUTOCHECKBOX | WS_CHILD | WS_OVERLAPPED | WS_TABSTOP);
	this->setPreferedSize(80, 14);
}

CheckBox::~CheckBox() {
	// TODO Auto-generated destructor stub
}

} /* namespace XmToolKit */
