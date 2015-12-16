
/*!
  \file     MainWindow.cpp
  \author       Tody
  MainWindow definition.
  date      2015/09/11
*/

#include "MainWindow.h"

#include <QtWidgets>

#include "Scene.h"
#include "Commands.h"
#include "ModelView.h"


MainWindow::MainWindow ()
{
    _scene = new Scene ( this );

    setAcceptDrops ( true );
    createUI();
    createMenue();

    this->showMaximized();
}

void MainWindow::release()
{
}

void MainWindow::createMenue()
{
    _fileMenus = new MenuGroup ( tr ( "&File" ), this );
    _fileMenus->addCommand ( new LoadCommand ( _scene ) );
    _fileMenus->addCommand ( new SaveCommand ( _scene ) );

    menuBar()->addMenu ( _fileMenus );

    _operationMenus = new MenuGroup ( tr ( "&Opearations" ), this );

    menuBar()->addMenu ( _operationMenus );

    _renderMenus = new MenuGroup ( tr ( "&Render" ), this );

    menuBar()->addMenu ( _renderMenus );

}

void MainWindow::createUI()
{
    _view = new ModelView ( this );
    _view->setScene ( _scene );

    QDockWidget* leftDock = new QDockWidget ( "MainView", this );
    leftDock->setWidget ( _view );

    /* QDockWidget* rightDock = new QDockWidget ( "LSMPlotter", this );
     rightDock->setWidget ( _plotter );*/

    addDockWidget ( Qt::LeftDockWidgetArea, leftDock );
    //addDockWidget ( Qt::RightDockWidgetArea, rightDock );

    statusBar()->showMessage ( "Create UI" );

    this->setWindowTitle ( "Simple Mesh Viewer" );
}

void MainWindow::dragEnterEvent ( QDragEnterEvent* event )
{
    if ( event->mimeData()->hasUrls() )
    {
        event->acceptProposedAction();
    }

    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent ( QDropEvent* event )
{
    if ( event->mimeData()->hasUrls() )
    {
        if ( !event->mimeData()->urls().empty() )
        {
            QUrl url = event->mimeData()->urls().at ( 0 );
            QString filePath = url.path();
            filePath = filePath.mid ( 1 );

            _scene->loadMesh ( filePath );

            //( new LoadCommand ( _scene, filePath ) )->actionSlot();

            event->acceptProposedAction();
        }
        else
        {
            event->ignore();
        }
    }
}