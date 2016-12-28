/*
 * LinearContainer.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_LINEARCONTAINER_H_
#define XMTOOLKIT_GUI_LINEARCONTAINER_H_
#include "Container.h"
namespace XmToolKit {

class LinearContainer:public Container
{
    public:
        LinearContainer();
        virtual void add(Widget*widget);
        virtual void add(Widget*widget, float peso);
        virtual void setSize(int width,int height);
        virtual void getMinimumSize(int *width, int *height);
        virtual void getPreferedSize(int *width, int*height);
        virtual void setPosition(int x, int y);
        virtual ~LinearContainer();
    protected:
        virtual void onChangeParent();
    private:
        struct ControlProp{
            Widget*widget;
            float peso;
        };
        ControlProp mControls[10];
        int mOrientation;
        int mCount;
        float mTotalWeight;
        int mMinHeight;
        int mMinWidth;
        int mEnsuredHeight;
        int mPreferedHeight;
        int mPreferedWidth;
        int mX,mY;
};
} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_LINEARCONTAINER_H_ */
