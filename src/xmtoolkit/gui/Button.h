#ifndef BUTTON_H
#define BUTTON_H
#include "Widget.h"
class Button:public Widget
{
    public:
        Button(const char*text = NULL);
        virtual void setText(const char* text);
        virtual String getText();
        virtual void getMinimumSize(int *width, int *height);
        virtual void getPreferedSize(int *width, int *height);
        virtual ~Button();
    protected:
    private:
};

#endif // BUTTON_H
