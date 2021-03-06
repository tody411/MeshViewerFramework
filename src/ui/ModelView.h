/*!
\file     ModelView.h
\author   Tody

3D Model View implementation.

\date     2014/11/17
*/

#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>

#include <Eigen/Dense>

#include "BaseOverlay.h"

class Scene;
class CameraTool;
class BaseTool;

//! 3D Model View implementation.
class ModelView :  public QGLWidget
{
    Q_OBJECT
public :
    //! Constructor.
    ModelView ( QWidget* parent = 0 );

    //! Destructor.
    virtual ~ModelView() {}

    //! Set the scene to this view.
    void setScene ( Scene* scene );

    //! Set tool.
    void setTool ( BaseTool* tool = nullptr );

public slots:
    //! Render the current scene.
    void render();

public:
    const QImage screenShot();

    //! Render screen shot of the current view.
    void renderScreenShot ( const QString& filePath );

    //! Return the overlays.
    QVector<BaseOverlay*> overlays() const
    {
        return _overlays;
    }

    //! Return the current mouse position.
    const Eigen::Vector2d mousePosition ( QMouseEvent* event );

    //! Unproject the screen postion.
    void unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray );

private:
    //-----------------------
    //  Mouse events.
    //=======================
    void mousePressEvent ( QMouseEvent* event );

    void mouseMoveEvent ( QMouseEvent* event );

    void mouseReleaseEvent ( QMouseEvent* event );

    void wheelEvent ( QWheelEvent* event );

    //-----------------------
    //  Key events.
    //=======================
    void keyPressEvent ( QKeyEvent* event );

    void keyReleaseEvent ( QKeyEvent* event );

    //=======================

    //! Set up OpenGL definition.
    virtual void initializeGL();

    //! Paint method.
    virtual void paintEvent ( QPaintEvent* event );

    //! Resize function for OpenGL.
    virtual void resizeGL ( int width, int height );

    //! OpenGL calls for rendering.
    virtual void renderGL();

    //! Overlay rendering with for _overlays.
    virtual void renderOverlay();


private:
    //! Render bachground.
    void renderBackGround();

    void renderPainter ( QPainter* painter );

    void updateRenderBuffer();

private:
    //! Camera tool.
    CameraTool* _cameraTool;

    //! Activated tool.
    BaseTool* _tool;

    //! Scene data.
    Scene* _scene;

    //! Overlay renderers.
    QVector<BaseOverlay*> _overlays;

    QGLFramebufferObject* _renderBuffer;
};

#endif

