
/*!
  \file     GLView.cpp
  \author       Tody
  GLView definition.
  date      2014/11/17
*/

#include "GLView.h"
#include <QtWidgets>
#include <QtOpenGL>
#include <GL/GLU.h>

#include "Scene.h"
#include "CameraTool.h"
#include "Logger.h"

#include <iostream>

GLView::GLView ( QWidget* parent )
    : QGLWidget ( QGLFormat ( QGL::SampleBuffers | QGL::AlphaChannel ), parent ), _scene ( nullptr )
{
    setMouseTracking ( true );
    setFocusPolicy ( Qt::StrongFocus );

    _cameraTool = new CameraTool ( this );
}

void GLView::setScene ( Scene* scene )
{
    _scene = scene;
    connect ( _scene, &Scene::updated, this, &GLView::render );
}

void GLView::render()
{
    Logger::getLogger ( "GLView" )->info ( "render", "render" );
    updateGL();
}

void GLView::initializeGL()
{
    qglClearColor ( QColor ( 0.1, 0.1, 0.1 ) );
    glClearDepth ( 1.0 );

    glEnable ( GL_DEPTH_TEST );
    glDisable ( GL_CULL_FACE );

    glShadeModel ( GL_SMOOTH );
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    glEnable ( GL_LIGHTING );
    glEnable ( GL_LIGHT0 );
    glEnable ( GL_MULTISAMPLE );
}

void GLView::paintGL()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( _scene == nullptr ) return;

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    _cameraTool->gl();

    _scene->focusGL();

    glEnable ( GL_BLEND );
    glEnable ( GL_DEPTH_TEST );
    glDisable ( GL_CULL_FACE );
    //glColor3d ( 0.2, 0.8, 0.8 );
    _scene->render();

    glDisable ( GL_DEPTH_TEST );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


}

void GLView::resizeGL ( int width, int height )
{
    glViewport ( 0, 0, width, height );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    float aspect = width / ( float )  height;

    glOrtho ( -1 , 1 , -1 , 1 , -4.0 , 4.0 );

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

}


void GLView::mousePressEvent ( QMouseEvent* event )
{
    _cameraTool->mousePressEvent ( event );

    Eigen::Vector3d pNear, ray;
    unproject ( mousePosition ( event ), pNear, ray );

    std::cout << "pNear" << pNear << std::endl;
    std::cout << "ray" << ray << std::endl;
}
void GLView::mouseMoveEvent ( QMouseEvent* event )
{
    _cameraTool->mouseMoveEvent ( event );
    updateGL();
}
void GLView::mouseReleaseEvent ( QMouseEvent* event )
{
    _cameraTool->mouseReleaseEvent ( event );
}
void GLView::wheelEvent ( QWheelEvent* event )
{
    _cameraTool->wheelEvent ( event );
    updateGL();
}

void GLView::keyPressEvent ( QKeyEvent* event )
{
    _cameraTool->keyPressEvent ( event );
    updateGL();
}
void GLView::keyReleaseEvent ( QKeyEvent* event )
{
    _cameraTool->keyReleaseEvent ( event );
}

const Eigen::Vector2d GLView::mousePosition ( QMouseEvent* event )
{
    QPoint p = event->pos();
    return Eigen::Vector2d ( p.x(), p.y() );
}

void GLView::unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray )
{
    GLdouble projectionMat[16];
    GLdouble modelviewMat[16];
    glGetDoublev ( GL_PROJECTION_MATRIX, projectionMat );
    glGetDoublev ( GL_MODELVIEW_MATRIX, modelviewMat );

    GLint viewport[4];
    glGetIntegerv ( GL_VIEWPORT, viewport );

    double pNearX;
    double pNearY;
    double pNearZ;

    gluUnProject ( p ( 0 ),  viewport[3] - p ( 1 ), 0.0, modelviewMat, projectionMat, viewport,
                   &pNearX, &pNearY, &pNearZ ) ;

    double pFarX;
    double pFarY;
    double pFarZ;

    gluUnProject ( p ( 0 ),  viewport[3] - p ( 1 ), 1.0, modelviewMat, projectionMat, viewport,
                   &pFarX, &pFarY, &pFarZ );

    pNear =  Eigen::Vector3d ( pNearX, pNearY, pNearZ );
    ray =  Eigen::Vector3d ( pFarX, pFarY, pFarZ ) - pNear;
}