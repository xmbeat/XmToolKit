#include "LinearContainer.h"

namespace XmToolKit {
//Constructor
LinearContainer::LinearContainer() {
	mOrientation = 0;
	mFixedHeight = 0;
	mTotalWeight = 0.0f;
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
	for (int i = 0; i < mChildren.size(); i++) {
		Widget::setParent(mChildren[i]->widget, mRawParent);
	}
}


void LinearContainer::add(Widget*widget, float weight) {
	this->add(widget, weight, true, true);
}

void LinearContainer::add(Widget *widget, float weight, bool verticalGrow, bool horizontalGrow){
	ControlProp *prop = new ControlProp;
	prop->weight = weight;
	prop->widget = widget;
	prop->hGrow = horizontalGrow;
	prop->vGrow = verticalGrow;
	int index = mChildren.indexOf(prop);

	if (index == -1) {
		mChildren.add(prop);
		Widget::setParent(widget, mRawParent);
	} else {
		*mChildren[index] = *prop;
		delete prop;
	}
}

void LinearContainer::calculateSizes(int requestedWidth, int requestedHeight) {
	int paddingX = mPadding.left + mPadding.right;
	mTotalWeight = 0.0f;
	mFixedHeight = mMinHeight = getSpacing() * (mChildren.size() - 1) + mPadding.top + mPadding.bottom;
	mMinWidth = 0;
	//Recorremos los controles hijos de este componente para
	//determinar el tamaño minimo que debe tener este componente
	for (int i = 0; i < mChildren.size(); i++) {
		Rect childMargin;
		int childHeight, childWidth;
		//El control debe expandirse y contraerse (Hasta su tamano minimo) de forma dinamica
		if (mChildren[i]->weight > 0.0f) {
			mTotalWeight += mChildren[i]->weight;
			mChildren[i]->widget->getMinimumSize(NULL, &childHeight);
		}
		//El control debe permanecer siempre del mismo tamano
		else {
			mChildren[i]->widget->getPreferedSize(NULL, &childHeight);
		}
		//Obtenemos el margen del componente hijo
		mChildren[i]->widget->getMargin(&childMargin);
		//Calculamos lo que minimamente debe medir de largo el componente hijo
		int requiredHeight = childHeight + childMargin.top + childMargin.bottom;
		mMinHeight += requiredHeight;
		if (mChildren[i]->weight == 0.0f) {
			mFixedHeight += requiredHeight;
		}
		//Calculamos lo que debe medir de ancho minimanente  el componente hijo
		if (mChildren[i]->hGrow) {
			mChildren[i]->widget->getMinimumSize(&childWidth, NULL);
		} else {
			mChildren[i]->widget->getPreferedSize(&childWidth, NULL);
		}
		int requiredWidth = childWidth + childMargin.left + childMargin.right
				+ paddingX;
		if (requiredWidth > mMinWidth) {
			mMinWidth = requiredWidth;
		}
	}
	if (requestedHeight < mMinHeight) {
		mHeight = mMinHeight;
	}
	else {
		mHeight = requestedHeight;
	}
	if (requestedWidth < mMinWidth) {
		mWidth = requestedWidth;
	}
	else{
		mWidth = requestedWidth;
	}
}
void LinearContainer::update() {
	if (mChildren.size() > 0) {
		//Vertical
		if (mOrientation == 0) {

			Rect box;
			box.left = mX + mPadding.left;
			box.top = mY + mPadding.top;
			box.right = mWidth - mPadding.left - mPadding.right;
			//Establecemos el espacio que puede almacenar objetos de tamaño dinamico
			int resizableHeight = mHeight - mFixedHeight;
			for (int i = 0; i < mChildren.size(); i++) {
				Rect childMargin;
				Rect childBox;
				mChildren[i]->widget->getMargin(&childMargin);
				mChildren[i]->widget->getPreferedSize(&childBox.right,
						&childBox.bottom);
				//El componente es de tamaño flexible (height)
				if (mChildren[i]->weight > 0.0f) {
					box.bottom = mChildren[i]->weight * resizableHeight
							/ mTotalWeight;
					//Si el componente debe adaptarse al largo (height) del box
					if (mChildren[i]->vGrow) {
						childBox.bottom = box.bottom - childMargin.top
								- childMargin.bottom;
						//TODO corroborar que el height es mayor o igual al minimo, si no es asi, colocarlo al minimo, actualizar mWeight, resizableHeight
						int height;
						mChildren[i]->widget->getMinimumSize(NULL, &height);
						if (height > childBox.bottom){
							childBox.bottom = height;
							mTotalWeight -= mChildren[i]->weight;
							resizableHeight -= height;
						}
					}
					//El componente debe usar el prefered height si es posible
					else {
						//NO se puede usar el prefered height, entonces se adapta al restante
						if (childBox.bottom + childMargin.top
								+ childMargin.bottom > box.bottom) {
							childBox.bottom = box.bottom - childMargin.top
									- childMargin.bottom;
						}

					}
				} else {
					box.bottom = childBox.bottom + childMargin.bottom
							+ childMargin.top;
				}
				//El componente debe adaptarse al width del contenedor
				if (mChildren[i]->hGrow) {
					childBox.right = box.right - childMargin.right
							- childMargin.left;
				}

				//TODO colocar el control dependiendo de su alineacion (CENTER, NORTH, NORTHEAST...)
				childBox.top = box.top + (box.bottom - childBox.bottom) / 2;
				childBox.left = box.left + (box.right - childBox.right) / 2;

				Widget::move(mChildren[i]->widget, childBox.left, childBox.top, childBox.right, childBox.bottom);
				box.top += box.bottom + getSpacing();
			}
		}
		//Horizontal
		else {

		}

	}
}

void LinearContainer::setPosition(int x, int y) {
	mX = x;
	mY = y;
}

void LinearContainer::setSize(int width, int height) {
	calculateSizes(width, height);
	update();
}


} /* namespace XmToolKit */
