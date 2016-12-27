#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include "Widget.h"


class Container : public Widget
{
    public:
        virtual void add(Widget* widget)=0;
        virtual ~Container() {}
    protected:
    private:
};

#endif // WIDGETCONTAINER_H
