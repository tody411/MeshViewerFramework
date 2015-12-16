
/*!
  \file     MainWindow.h
  \author   Tody
  MainWindow definition.
  \date     2015/09/11
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

class GLView;
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


signals:
    void fileDropped ( QString filePath );

private:

    void createMenue();

    void createUI();

    void dragEnterEvent ( QDragEnterEvent* event );
    void dropEvent ( QDropEvent* event );

private:
    Scene* _scene;
    GLView*   _view;

};

#endif

