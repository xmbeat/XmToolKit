#ifndef LINEARCONTAINER_H
#define LINEARCONTAINER_H
#include "Container.h"
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
        }mControls[10];
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

#endif // LINEARCONTAINER_H
