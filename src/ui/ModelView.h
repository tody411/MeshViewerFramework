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

//! 3D Model View implementation.
class ModelView :  public QGLWidget
{
    Q_OBJECT
public :
    //! Constructor.
    ModelView ( QWidget* parent = 0 );

    //! Destructor.
    virtual ~ModelView() {}

    void setScene ( Scene* scene );

public slots:
    void render();

private:
    virtual void initializeGL();

    virtual void paintEvent ( QPaintEvent* event );

    virtual void renderGL();

    virtual void renderOverlay();

    virtual void resizeGL ( int width, int height );

    void mousePressEvent ( QMouseEvent* event );
    void mouseMoveEvent ( QMouseEvent* event );
    void mouseReleaseEvent ( QMouseEvent* event );
    void wheelEvent ( QWheelEvent* event );

    void keyPressEvent ( QKeyEvent* event );
    void keyReleaseEvent ( QKeyEvent* event );

    const Eigen::Vector2d mousePosition ( QMouseEvent* event );

    void unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray );

    void renderColorBuffer();

private:
    void renderBackGround();

private:
    CameraTool* _cameraTool;
    Scene* _scene;

    QVector<BaseOverlay*> _overlays;

};

#endif

