#include "Container.h"
namespace XmToolKit {

Container::Container(){
}

void Container::getPadding(Rect *padding) {
	*padding = mPadding;
}
void Container::setPadding(const Rect &padding) {
	mPadding = padding;
}

Rect Container::getPadding() {
	return mPadding;
}

int Container::getSpacing() {
	return mSpacing;
}

void Container::setSpacing(int space){
	mSpacing = space;
}

Container::~Container() {
}

}
