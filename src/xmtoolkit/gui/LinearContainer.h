/*
 * LinearContainer.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_LINEARCONTAINER_H_
#define XMTOOLKIT_GUI_LINEARCONTAINER_H_
#include "Container.h"
#include <xmtoolkit/algorithms/ArrayList.h>
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
        virtual void setSpace(int value);
        virtual ~LinearContainer();
    protected:
        virtual void onChangeParent();
    private:
        struct ControlProp{
            Widget*widget;
            float peso;
            stSize margin;
            bool operator==(const ControlProp &prop){
            	return widget == prop.widget;
            }
        };
        ArrayList<ControlProp*> mChildren;
        ControlProp mControls[10];
        int mSpace;
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
