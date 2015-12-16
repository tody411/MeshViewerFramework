
/*!
  \file     MainWindow.cpp
  \author       Tody
  MainWindow definition.
  date      2015/09/11
*/

#include "MainWindow.h"

#include <QtWidgets>

#include "Scene.h"
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

    menuBar()->addMenu ( _fileMenus );
    //QMenu* fileMenu = new QMenu ( tr ( "&File" ), this );
    //fileMenu->addAction ( new LoadAction ( _scene ) );
    //fileMenu->addAction ( new SaveAction ( _scene ) );
    //fileMenu->addAction ( new MarchingCubesAction ( _scene ) );
    //menuBar()->addMenu ( fileMenu );

    //QMenu* commandMenu = new QMenu ( tr ( "&Volume Operations" ), this );
    //commandMenu->addAction ( new DownScaleAction ( _scene ) );
    //commandMenu->addAction ( new UpScaleAction ( _scene ) );
    //commandMenu->addAction ( new BoxFilterAction ( _scene ) );
    //commandMenu->addAction ( new GaussianFilterAction ( _scene )  );
    //commandMenu->addAction ( new GuidedFilterAction ( _scene )  );
    //commandMenu->addAction ( new DensityEstimationAction ( _scene ) );

    //menuBar()->addMenu ( commandMenu );

    ///* ShaderMenu* shaderMenu = new ShaderMenu();
    // menuBar()->addMenu ( shaderMenu->createMenue ( _scene, _imageView, this ) );
    //*/
    //QMenu* uiMenu = new QMenu ( tr ( "&UI" ), this );
    //uiMenu->addAction ( ( new FloatingWindow ( new MemoryMonitor(), this ) )->showAction() );

    //OperationView* operationView = new OperationView();
    //operationView->undoGroup()->setActiveStack ( _scene->operations() );
    //uiMenu->addAction ( ( new FloatingWindow ( operationView, this ) )->showAction() );
    //menuBar()->addMenu ( uiMenu );



    //HelpMenu* helpMenue = new HelpMenu ( this );
    //menuBar()->addMenu ( helpMenue->createMenue ( this ) );

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