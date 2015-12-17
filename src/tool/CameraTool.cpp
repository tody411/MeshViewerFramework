
/*!
  \file     CameraTool.cpp
  \author       Tody
  CameraTool definition.
  date      2015/12/15
*/

#include "CameraTool.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QtOpenGL>

#include <QDebug>
#include <QTimer>

void CameraTool::reset()
{
    _scalingFactor = 0.001;
    _scale = 1.0;

    _rotationFactor = 0.2;
    _rotation = Eigen::Vector2f ( 0, 0 );

    _translateFactor = 0.01;
    _translation = Eigen::Vector2f ( 0, 0 );
    _presPos = Eigen::Vector2f ( 0, 0 );
}

void CameraTool::gl()
{
    glTranslatef ( _translation[0], _translation[1], 0.0f );
    glScalef ( _scale, _scale, _scale );
    glRotatef ( _rotation[0], 1.0f, 0.0f, 0.0f );
    glRotatef ( _rotation[1], 0.0f, 1.0f, 0.0f );
}

void CameraTool::mousePressEvent ( QMouseEvent* event )
{
    if ( event->modifiers() & Qt::AltModifier )
    {
        _presPos = mousePosition ( event );
    }
}

void  CameraTool::mouseMoveEvent ( QMouseEvent* event )
{
    if ( event->buttons() == Qt::MiddleButton && event->modifiers() & Qt::AltModifier )
    {
        translateDrag ( event );
    }

    if ( event->buttons() & Qt::LeftButton && event->modifiers() & Qt::AltModifier )
    {
        rotateDrag ( event );
    }
}

void CameraTool::mouseReleaseEvent ( QMouseEvent* event )
{
}

void CameraTool::wheelEvent ( QWheelEvent* event )
{
    double factor = pow ( 2.0, event->delta() / 240.0 );

    if ( _scale < 0.5 && factor < 1 )
    {
        return;
    }

    if ( _scale > 100 && factor > 1 )
    {
        return;
    }

    _scale *= factor;
}

void CameraTool::keyPressEvent ( QKeyEvent* event )
{
    if ( event->text() == "f" )
    {
        reset();
    }
}

void CameraTool::keyReleaseEvent ( QKeyEvent* event )
{
}

const Eigen::Vector2f CameraTool::mousePosition ( QMouseEvent* event )
{
    QPoint p = event->pos();
    return Eigen::Vector2f ( p.x(), p.y() );
}

const Eigen::Vector2f CameraTool::mouseMovement ( QMouseEvent* event )
{
    return mousePosition ( event ) - _presPos;
}

void CameraTool::translateDrag ( QMouseEvent* event )
{
    Eigen::Vector2f dxy = mouseMovement ( event );

    _translation[0] += _translateFactor * dxy[0];
    _translation[1] += - _translateFactor * dxy[1];

    _presPos = mousePosition ( event );
}

void CameraTool::rotateDrag ( QMouseEvent* event )
{
    Eigen::Vector2f dxy = mouseMovement ( event );

    _rotation[0] += _rotationFactor * dxy[1];
    _rotation[1] += _rotationFactor * dxy[0];

    _presPos = mousePosition ( event );
}