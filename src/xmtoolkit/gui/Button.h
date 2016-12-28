/*
 * Button.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_BUTTON_H_
#define XMTOOLKIT_GUI_BUTTON_H_
#include <xmtoolkit/utils/String.h>
#include "Widget.h"
namespace XmToolKit {

class Button: public Widget
{
    public:
        Button(const char*text = 0);
        virtual void setText(const char* text);
        virtual String getText();
        virtual void getMinimumSize(int *width, int *height);
        virtual void getPreferedSize(int *width, int *height);
        virtual ~Button();
    protected:
    private:
};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_BUTTON_H_ */
