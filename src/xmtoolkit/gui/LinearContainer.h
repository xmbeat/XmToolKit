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
        virtual void add(Widget*widget, float weight);
        virtual void add(Widget*widget, float weight, bool verticalGrow, bool horizontalGrow);
        virtual void setSize(int width,int height);
        virtual void setPosition(int x, int y);
        virtual ~LinearContainer();
    protected:
        virtual void onChangeParent();
    private:
        struct ControlProp{
            Widget*widget;
            float weight;
            bool vGrow;
            bool hGrow;
            int alignment;
            ControlProp(){
            	widget = 0;
            	weight = 0.0f;
            	vGrow = false;
            	hGrow = false;
            	alignment = 0;
            }
            bool operator==(const ControlProp &prop){
            	return widget == prop.widget;
            }
        };
        void calculateSizes(int, int);
        void update();
        ArrayList<ControlProp*> mChildren;
        ControlProp mControls[10];
        //TODO move setMargin to Widget class
        Rect mMargin;
        int mOrientation;
        float mTotalWeight;
        int mFixedHeight;
};
} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_LINEARCONTAINER_H_ */
