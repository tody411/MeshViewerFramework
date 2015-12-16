
/*!
\file     GLView.h
\author   Tody
GLView definition.
\date     2014/11/17
*/

#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>

#include <Eigen/Dense>

class Scene;
class CameraTool;

//! GLView implementation.
class GLView :  public QGLWidget
{
    Q_OBJECT
public :
    //! Constructor.
    GLView ( QWidget* parent = 0 );

    //! Destructor.
    virtual ~GLView() {}

    void setScene ( Scene* scene );

public slots:
    void render();

private:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL ( int width, int height );

    void mousePressEvent ( QMouseEvent* event );
    void mouseMoveEvent ( QMouseEvent* event );
    void mouseReleaseEvent ( QMouseEvent* event );
    void wheelEvent ( QWheelEvent* event );

    void keyPressEvent ( QKeyEvent* event );
    void keyReleaseEvent ( QKeyEvent* event );

    const Eigen::Vector2d mousePosition ( QMouseEvent* event );

    void unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray );

private:
    CameraTool* _cameraTool;
    Scene* _scene;
};

#endif

