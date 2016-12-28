/*
 * Window.h
 *
 *  Created on: 28 dic. 2016
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_WINDOW_H_
#define XMTOOLKIT_GUI_WINDOW_H_
#include "Container.h"
#include <xmtoolkit/algorithms/LinkedList.h>
#include <xmtoolkit/utils/String.h>

namespace XmToolKit {

class Window: public Container{
private:
    static const wchar_t CLASS_NAME[];
    //La ventana padre de todas, necesaria para admitir la propiedad VisibleInTaskbar
    static HWND mainWindow;
    //La cantidad de ventanas creadas
    static int topWindowsCount;
    //Lista de las ventanas creadas
    static LinkedList<Window*> ventanas;
    //Variable que indica que ventana es duena de esta cuando se muestra de manera modal
    Window* mParent;
    //Variable que indica el Widget hijo de esta ventana
    Widget* mChild;
    //Variable que indica si un formulario es modal
    bool mIsModal;
    //Variable que indica el tipo de cierre para la ventana
    int mCloseType;
    //Variable que indica cuantas veces se ha pretendido bloquear la ventana,
    //este es para el buen funcionamiento de formularios modales
    int mLocks;
    //Lista que indica las ventanas que esta ha bloqueado al ser modal
    LinkedList<Window*> mParents;
    //Variable donde se almacena el escuchador de los eventos de la ventana
    WindowEventListener *mWindowListener;
    //Propiedades para restringir el tamano de la ventana
    int mMaximumSizeW,mMaximumSizeH,mMinimumSizeW,mMinimumSizeH;
    //Propiedades
    bool mIsDeleteable,mIsVisibleInTaskBar,mIsFullScreen;
    //Sirve para aplicar un bloqueo a las ventanas padres de esta, para cuando es modal
    void unLockParent(Window* parent=NULL);
    //Sirve para desbloquear las ventanas padres de esta, para cuando es modal
    void lockParent();
    void lock();
    void unLock();
    bool isLocked();
    void setOwner(HWND hwnd);
    void updateContainer();
public:
    //La ventana que indica la ventana activa
    static HWND activeWindow;
    //DA POR TEMINADO EL BUCLE DE MENSAJES, TERMINANDO LA PARTE GRAFICA.
    static const int EXIT_ON_CLOSE;
    //Simplemente oculta la ventana
    static const int HIDE_ON_CLOSE;
    //No hace nada en el cierre
    static const int NONE_ON_CLOSE;
    Window(const char* title = NULL);
    virtual ~Window();
    virtual void setPosition(int x, int y);
    virtual void getPosition(int *x, int*y);
    virtual void setDefaultCloseOperation(int mode);
    virtual bool isModal();
    virtual void setModal(bool value, Window* modalParent = 0);
    virtual void setVisible(bool value);
    virtual void setVisibleInTaskBar(bool value);
    virtual bool isVisibleInTaskBar();
    virtual void setIcon(/*GdkPixbuf *icon*/);
    virtual void setText(const char* text);
    virtual String getText();
    virtual void setMinimumSize(int width, int height);
    virtual void getMinimumSize(int *width, int *height);
    virtual void setMaximumSize(int width, int height);
    virtual void getMaximumSize(int *width, int *height);
    virtual void setDeleteable(bool value);
    virtual bool isDeleteable();
    virtual void setFullScreen(bool value);
    virtual bool isFullScreen();
    virtual void setIconFromFile(const char* path);
    virtual void setResizable(bool value);
    virtual bool isResizable();
    virtual void setMinButton(bool value);
    virtual bool hasMinButton();
    virtual void setMaxButton(bool value);
    virtual bool hasMaxButton();
    virtual void getClientSize(int *h, int *w);
    virtual void getPreferedSize(int* width, int* height);
    //From Container:
    virtual void add(Widget*widget);
protected:
    static LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};
} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_WINDOW_H_ */
