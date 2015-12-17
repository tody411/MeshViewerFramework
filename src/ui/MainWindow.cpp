
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
    _operationMenus->addCommand ( new LaplacianSmoothingCommand ( _scene ) );

    menuBar()->addMenu ( _operationMenus );

    _renderMenus = new MenuGroup ( tr ( "&Render" ), this );
    _renderMenus->addCommand ( new RenderCommand ( _scene, _view ) );

    menuBar()->addMenu ( _renderMenus );

}

void MainWindow::createUI()
{
    _view = new ModelView ( this );
    _view->setScene ( _scene );

    //setCentralWidget ( _view );
    QDockWidget* leftDock = new QDockWidget ( "3D Model View", this );
    leftDock->setWidget ( _view );
    addDockWidget ( Qt::LeftDockWidgetArea, leftDock );

    //addDockWidget ( Qt::RightDockWidgetArea, rightDock );
    connect ( _scene, &Scene::messageUpdated, statusBar(), &QStatusBar::showMessage );

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