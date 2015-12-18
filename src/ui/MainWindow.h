
/*!
  \file     MainWindow.h
  \author   Tody
  MainWindow definition.
  \date     2015/09/11
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "MenuGroup.h"

class ModelView;
class Scene;

//! MainWindow implementation.
class MainWindow : public QMainWindow
{
    Q_OBJECT
public :
    //! Constructor.
    MainWindow ();

    //! Destructor.
    virtual ~MainWindow() {}

    void release();

private:

    void createMenue();

    void createUI();

    //! Support drag & drop for the mesh file.
    void dragEnterEvent ( QDragEnterEvent* event );

    //! Support drag & drop for the mesh file.
    void dropEvent ( QDropEvent* event );

private:
    //! Scene data.
    Scene* _scene;

    //! 3D model view.
    ModelView*   _view;

    //! File menus.
    MenuGroup* _fileMenus;

    //! Opeartion menus.
    MenuGroup* _operationMenus;

    //! Overlay menus.
    MenuGroup* _overlayMenus;

    //! Render menus.
    MenuGroup* _renderMenus;
};

#endif

