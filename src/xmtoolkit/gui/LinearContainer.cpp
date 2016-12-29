
#include "LinearContainer.h"

namespace XmToolKit {
//Constructor
LinearContainer::LinearContainer() {
	mSpace = 0;
	mOrientation = 0;
	mMinHeight = mMinWidth = mPreferedHeight = mPreferedWidth = 0;
	mEnsuredHeight = 0;
	mTotalWeight = 0.0f;
	mCount = 0;
	mX = mY = 0;
}

//Destructor
LinearContainer::~LinearContainer() {
	mChildren.clearAndDelete();
}
//Add method
void LinearContainer::add(Widget*widget) {
	this->add(widget, 1.0);
}
void LinearContainer::onChangeParent() {
	for (int i = 0; i < mCount; i++) {
		Widget::setParent(mControls[i].widget, mRawParent);
	}
}

void LinearContainer::setSpace(int space){
	mSpace = space;
}

void LinearContainer::add(Widget*widget, float peso) {
	ControlProp *prop = new ControlProp;
	prop->peso = peso;
	prop->widget = widget;
	if (!mChildren.contains(prop)){
		mChildren.add(prop);
	}

	mControls[mCount].peso = peso;
	mControls[mCount].widget = widget;
	Widget::setParent(widget, mRawParent);
	mCount++;
	int height, width;
	widget->getMinimumSize(&width, &height);
	mMinHeight += height;
	if (width > mMinWidth)
		mMinWidth = width;
	widget->getPreferedSize(&width, &height);
	mPreferedHeight += height;
	if (width > mPreferedWidth)
		mPreferedWidth = width;
	if (peso > 0.0f) {
		mTotalWeight += peso;
	} else {
		mEnsuredHeight += height;
	}
}
void LinearContainer::setPosition(int x, int y) {
	mX = x;
	mY = y;
}

void LinearContainer::setSize(int width, int height) {
	if (height < mMinHeight) {

	} else {
		int restante = height - mEnsuredHeight;
		int h = 0;
		int y = mY;
		for (int i = 0; i < mCount; i++) {
			if (mControls[i].peso > 0.0f) {
				h = mControls[i].peso * restante / mTotalWeight;
			} else {
				mControls[i].widget->getPreferedSize(0, &h);
			}
			mControls[i].widget->setSize(width, h);
			mControls[i].widget->setPosition(mX, y);
			y += h;
		}
	}
}

void LinearContainer::getMinimumSize(int *width, int *height) {
	if (height) {
		*height = mMinHeight;
	}
	if (width) {
		*width = mMinWidth;
	}
}

void LinearContainer::getPreferedSize(int *width, int*height) {
	if (height) {
		*height = mPreferedHeight;
	}
	if (width) {
		*width = mPreferedWidth;
	}
}

} /* namespace XmToolKit */
