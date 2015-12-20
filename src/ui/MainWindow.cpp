
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
#include "BaseOverlay.h"


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

//! Render screen shot of the current view.
void MainWindow::renderScreenShot ( const QString& filePath )
{
    QPixmap image = grab();
    QRect viewRect = _view->geometry();
    QRect winRect = geometry();

    QImage viewImage = _view->screenShot();

    QPoint p_view = _view->mapTo ( this, _view->pos() );
    QPoint p_win = geometry().topLeft();

    qDebug() << "viewImage.size()" << viewImage.size();
    qDebug() << "viewRect" << viewRect;
    qDebug() << "winRect" << winRect;

    qDebug() << "view pos" << p_view;
    qDebug() << "win pos" << p_win;

    QPainter painter ( &image );
    painter.drawImage ( p_view - p_win, viewImage );

    image.save ( filePath );
}

void MainWindow::createMenue()
{
    _fileMenus = new MenuGroup ( tr ( "&File" ), this );
    _fileMenus->addCommand ( new LoadCommand ( _scene ) );
    _fileMenus->addCommand ( new SaveCommand ( _scene ) );

    menuBar()->addMenu ( _fileMenus );

    _operationMenus = new MenuGroup ( tr ( "&Operations" ), this );
    _operationMenus->addCommand ( new NoiseCommand ( _scene ) );
    _operationMenus->addCommand ( new LaplacianSmoothingCommand ( _scene ) );
    _operationMenus->addCommand ( new FlipNormalCommand ( _scene ) );
    _operationMenus->addCommand ( new NormalizeMeshCommand ( _scene ) );
    menuBar()->addMenu ( _operationMenus );

    MenuGroup* coloringMenus = new MenuGroup ( tr ( "&Coloring" ), this );
    coloringMenus->addCommand ( new DefaultShadingCommand ( _scene ) );
    coloringMenus->addCommand ( new NormalColorCommand ( _scene ) );
    coloringMenus->addCommand ( new PositionColorCommand ( _scene ) );
    menuBar()->addMenu ( coloringMenus );

    MenuGroup* shaderMenus = new MenuGroup ( tr ( "&Shader" ), this );
    shaderMenus->addCommand ( new NormalShaderCommand ( _scene ) );
    shaderMenus->addCommand ( new ToonShaderCommand ( _scene ) );
    menuBar()->addMenu ( shaderMenus );

    _overlayMenus = new MenuGroup ( tr ( "&Overlay" ), this );

    foreach ( BaseOverlay* overlay, _view->overlays() )
    {
        _overlayMenus->addOverlayCommand ( new OverlayCommand ( overlay ) );
    }

    menuBar()->addMenu ( _overlayMenus );

    _renderMenus = new MenuGroup ( tr ( "&Render" ), this );
    _renderMenus->addCommand ( new RenderCommand ( _scene, _view ) );
    _renderMenus->addCommand ( new RenderWindowCommand ( _scene, this ) );

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

    this->setWindowTitle ( "Mesh Viewer" );
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