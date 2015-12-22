
/*!
  \file     ModelView.cpp
  \author       Tody
  ModelView definition.
  date      2014/11/17
*/

#include "ModelView.h"
#include <QtWidgets>
#include <QtOpenGL>
#include <GL/GLU.h>

#include "Scene.h"
#include "BaseTool.h"
#include "SelectTool.h"
#include "Overlays.h"
#include "CameraTool.h"
#include "Logger.h"

#include <iostream>

ModelView::ModelView ( QWidget* parent )
    : QGLWidget ( QGLFormat ( QGL::SampleBuffers | QGL::AlphaChannel ), parent ), _scene ( nullptr ), _tool ( nullptr ), _renderBuffer ( nullptr )
{
    setMouseTracking ( true );
    setFocusPolicy ( Qt::StrongFocus );
    setAutoFillBackground ( false );
}

void ModelView::setScene ( Scene* scene )
{
    _scene = scene;
    connect ( _scene, &Scene::updated, this, &ModelView::render );

    _overlays.append ( new SceneInfoOverlay ( scene ) );
    _overlays.append ( new CoordinateSystemOverlay ( scene, _cameraTool, this ) );
    _overlays.append ( new WireframeOverlay ( scene ) );
    _overlays.append ( new PointsOverlay ( scene ) );
    _overlays.append ( new NormalVectorOverlay ( scene ) );

    _cameraTool = new CameraTool ( _scene, this );

    setTool ( new SelectTool ( _scene, this ) );
}

void ModelView::setTool ( BaseTool* tool )
{
    _tool = tool;
}

void ModelView::render()
{
    update();
}

const QImage ModelView::screenShot()
{
    QImage image = grabFrameBuffer ( true );
    image = image.convertToFormat ( QImage::Format_ARGB32 );
    return image;
}

void ModelView::renderScreenShot ( const QString& filePath )
{
    /*update();
    QImage image = screenShot();
    image.save ( filePath );*/

    makeCurrent();

    updateRenderBuffer();

    _renderBuffer->bind();

    glPushAttrib ( GL_ALL_ATTRIB_BITS );
    glViewport ( 0, 0, width(), height() );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    float aspect = width() / ( float )  height();

    glOrtho ( -aspect , aspect , -1 , 1 , -10.0 , 10.0 );

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor ( 0.0, 0.0, 0.0, 0.0 );
    glColorMask ( TRUE, TRUE, TRUE, TRUE );
    glClear ( GL_COLOR_BUFFER_BIT );
    renderBackGround();
    renderGL();
    glPopAttrib();

    renderOverlay();

    QPainter painter ( _renderBuffer );

    renderPainter ( &painter );
    painter.end();

    _renderBuffer->release();

    QImage image = _renderBuffer->toImage();

    image.save ( filePath );
}

void ModelView::initializeGL()
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

    if ( _scene )
    {
        _scene->shader()->linkShaders ( "SimpleTransform.vert", "LambertShader.frag" );
    }
}

void ModelView::paintEvent ( QPaintEvent* event )
{
    makeCurrent();

    glPushAttrib ( GL_ALL_ATTRIB_BITS );
    renderBackGround();
    renderGL();
    glPopAttrib();

    renderOverlay();
}

void ModelView::renderGL()
{
    if ( _scene == nullptr ) return;

    glEnable ( GL_BLEND );
    glEnable ( GL_DEPTH_TEST );
    glDisable ( GL_CULL_FACE );

    _scene->light()->gl();
    _scene->material()->gl();

    _scene->glCamera();
    _scene->glFocus();

    _scene->render();

    _tool->renderSceneOverlay();

    foreach ( BaseOverlay* overlay, _overlays )
    {
        overlay->renderSceneOverlay();
    }

    glFlush();

    glDisable ( GL_DEPTH_TEST );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void ModelView::renderOverlay()
{
    glPushAttrib ( GL_ALL_ATTRIB_BITS );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    foreach ( BaseOverlay* overlay, _overlays )
    {
        overlay->renderViewOverlay();
    }
    _tool->renderViewOverlay();
    glPopAttrib();

    QPainter painter ( this );

    renderPainter ( &painter );
    painter.end();
}

void ModelView::resizeGL ( int width, int height )
{
    glViewport ( 0, 0, width, height );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    float aspect = width / ( float )  height;

    glOrtho ( -aspect , aspect , -1 , 1 , -10.0 , 10.0 );

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    _scene->camera()->setAspect ( aspect );
}


void ModelView::mousePressEvent ( QMouseEvent* event )
{
    if ( ! ( event->modifiers() & Qt::AltModifier ) )
    {
        if ( _tool ) _tool->mousePressEvent ( event );
    }


    _cameraTool->mousePressEvent ( event );
}
void ModelView::mouseMoveEvent ( QMouseEvent* event )
{
    if ( ! ( event->modifiers() & Qt::AltModifier ) )
    {
        if ( _tool ) _tool->mouseMoveEvent ( event );
    }

    _cameraTool->mouseMoveEvent ( event );
    update();


}
void ModelView::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( ! ( event->modifiers() & Qt::AltModifier ) )
    {
        if ( _tool ) _tool->mouseReleaseEvent ( event );
    }

    _cameraTool->mouseReleaseEvent ( event );
}
void ModelView::wheelEvent ( QWheelEvent* event )
{
    if ( _tool ) _tool->wheelEvent ( event );

    _cameraTool->wheelEvent ( event );
    update();
}

void ModelView::keyPressEvent ( QKeyEvent* event )
{
    if ( _tool ) _tool->keyPressEvent ( event );

    _cameraTool->keyPressEvent ( event );
    update();
}
void ModelView::keyReleaseEvent ( QKeyEvent* event )
{
    if ( _tool ) _tool->keyReleaseEvent ( event );

    _cameraTool->keyReleaseEvent ( event );
}

const Eigen::Vector2d ModelView::mousePosition ( QMouseEvent* event )
{
    QPoint p = event->pos();
    return Eigen::Vector2d ( p.x(), p.y() );
}

void ModelView::unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray )
{
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    _scene->glCamera();
    _scene->glFocus();

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

void ModelView::renderBackGround()
{
    float aspect = width() / ( float )  height();

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_LIGHTING );

    glBegin ( GL_QUADS );
    glColor3f ( 0.1f, 0.1f, 0.1f );
    glVertex2f ( -aspect, -1.0f );

    glColor3f ( 0.1f, 0.1f, 0.1f );
    glVertex2f ( aspect, -1.0f );

    glColor3f ( 0.5f, 0.6f, 0.7f );
    glVertex2f ( aspect, 1.0f );

    glColor3f ( 0.5f, 0.6f, 0.7f );
    glVertex2f ( -aspect, 1.0f );
    glEnd();
}

void ModelView::renderPainter ( QPainter* painter )
{
    foreach ( BaseOverlay* overlay, _overlays )
    {
        overlay->renderPainter ( painter );
    }

    _tool->renderPainter ( painter );
}

void ModelView::updateRenderBuffer()
{
    if ( _renderBuffer == nullptr )
    {
        _renderBuffer = new QGLFramebufferObject ( size(), QGLFramebufferObject::Depth );
    }

    if ( _renderBuffer != nullptr )
    {
        if ( _renderBuffer->size() != size() )
        {
            delete _renderBuffer;
            _renderBuffer = new QGLFramebufferObject ( size(), QGLFramebufferObject::Depth );
        }
    }
}
