
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

    //! Render screen shot of the current view.
    void renderScreenShot ( const QString& filePath );

private:

    void createMenue();

    void createUI();

    //! Support drag & drop for the mesh file.
    void dragEnterEvent ( QDragEnterEvent* event );

    //! Support drag & drop for the mesh file.
    void dropEvent ( QDropEvent* event );

    //! Close all sub windows.
    void closeEvent ( QCloseEvent* event );

private:
    //! Scene data.
    Scene* _scene;

    //! 3D model view.
    ModelView*   _view;

    //! Tool UI.
    QDockWidget* _toolDock;

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

