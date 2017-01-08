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
        virtual ~Button();
    protected:
        static LRESULT CALLBACK ButtonProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    private:
};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_BUTTON_H_ */
