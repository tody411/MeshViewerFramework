
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
#include "DemoCommand.h"

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
    _fileMenus = new MenuGroup ( tr ( "&File" ), this, _toolDock );
    _fileMenus->addCommand ( new LoadCommand ( _scene ) );
    _fileMenus->addCommand ( new SaveCommand ( _scene ) );
    _fileMenus->addCommand ( new ImportLabelDataCommand ( _scene ) );
    _fileMenus->addCommand ( new ExportLabelDataCommand ( _scene ) );
    _fileMenus->addCommand ( new ExportSeamDataCommand ( _scene ) );
    _fileMenus->addCommand ( new SetProjectCommand ( _scene ) );

    menuBar()->addMenu ( _fileMenus );

    _operationMenus = new MenuGroup ( tr ( "&Operations" ), this, _toolDock );
    _operationMenus->addCommand ( new NoiseCommand ( _scene ) );
    _operationMenus->addCommand ( new LaplacianSmoothingCommand ( _scene ) );
    _operationMenus->addCommand ( new SmoothNormalCommand ( _scene ) );
    _operationMenus->addCommand ( new FlipNormalCommand ( _scene ) );
    _operationMenus->addCommand ( new NormalizeMeshCommand ( _scene ) );
    menuBar()->addMenu ( _operationMenus );

    MenuGroup* clusteringMenus = new MenuGroup ( tr ( "&Clustering" ), this, _toolDock );
    clusteringMenus->addCommand ( new NormalKmeansCommand ( _scene ) );
    clusteringMenus->addCommand ( new KHarmonicFieldCommand ( _scene ) );
    clusteringMenus->addCommand ( new GreedyFloodingCommand ( _scene ) );
    //clusteringMenus->addCommand ( new FindExtremePoiintsCommand ( _scene ) );
    clusteringMenus->addCommand ( new BiharmonicNormalClusteringCommand ( _scene ) );
    clusteringMenus->addCommand ( new SpectralClusteringCommand ( _scene ) );
    menuBar()->addMenu ( clusteringMenus );

    MenuGroup* textureMenus = new MenuGroup ( tr ( "&Texture" ), this, _toolDock );
    textureMenus->addCommand ( new PlanarMappingCommand ( _scene ) );
    textureMenus->addCommand ( new UnfoldCommand ( _scene ) );

    menuBar()->addMenu ( textureMenus );

    MenuGroup* coloringMenus = new MenuGroup ( tr ( "&Coloring" ), this, _toolDock );
    coloringMenus->addCommand ( new DefaultShadingCommand ( _scene ) );
    coloringMenus->addCommand ( new NormalColorCommand ( _scene ) );
    coloringMenus->addCommand ( new PositionColorCommand ( _scene ) );
    menuBar()->addMenu ( coloringMenus );

    MenuGroup* shaderMenus = new MenuGroup ( tr ( "&Shader" ), this, _toolDock );
    shaderMenus->addCommand ( new LambertShaderCommand ( _scene ) );
    shaderMenus->addCommand ( new PhongShaderCommand ( _scene ) );
    shaderMenus->addCommand ( new NormalShaderCommand ( _scene ) );
    shaderMenus->addCommand ( new ToonShaderCommand ( _scene ) );
    menuBar()->addMenu ( shaderMenus );

    _overlayMenus = new MenuGroup ( tr ( "&Overlay" ), this, _toolDock );

    foreach ( BaseOverlay* overlay, _view->overlays() )
    {
        _overlayMenus->addOverlayCommand ( new OverlayCommand ( overlay ) );
    }

    menuBar()->addMenu ( _overlayMenus );

    _renderMenus = new MenuGroup ( tr ( "&Render" ), this, _toolDock );
    _renderMenus->addCommand ( new RenderCommand ( _scene, _view ) );
    _renderMenus->addCommand ( new RenderWindowCommand ( _scene, this ) );
    menuBar()->addMenu ( _renderMenus );

    /*MenuGroup* demoMenus = new MenuGroup ( tr ( "&Demo" ), this, _toolDock );
    demoMenus->addCommand ( new DemoCommand ( _scene, _view ) );
    menuBar()->addMenu ( demoMenus );*/
}

void MainWindow::createUI()
{
    _view = new ModelView ( this );
    _view->setScene ( _scene );

    _toolDock = new QDockWidget ( "Tool UI", this );
    addDockWidget ( Qt::LeftDockWidgetArea, _toolDock );
    _toolDock->setMaximumWidth ( 400 );
    _toolDock->setMinimumWidth ( 300 );

    QDockWidget* viewDock = new QDockWidget ( "3D Model View", this );
    viewDock->setWidget ( _view );
    this->setCentralWidget ( viewDock );
    //addDockWidget ( Qt::RightDockWidgetArea, viewDock );

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

            //_scene->loadMesh ( filePath );

            ( new LoadCommand ( _scene, filePath ) )->actionSlot();

            event->acceptProposedAction();
        }
        else
        {
            event->ignore();
        }
    }
}

void MainWindow::closeEvent ( QCloseEvent* event )
{
    QApplication::closeAllWindows();
}