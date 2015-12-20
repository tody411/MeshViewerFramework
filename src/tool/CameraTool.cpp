
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

#include "Scene.h"

void CameraTool::reset()
{
    _scalingFactor = 0.001;

    _rotationFactor = 0.2;

    _translateFactor = 0.01;

    camera()->focus();

    _presPos = Eigen::Vector2d ( 0, 0 );
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

void CameraTool::wheelEvent ( QWheelEvent* event )
{
    float scale = camera()->scale() [0];

    double factor = pow ( 2.0, event->delta() / 240.0 );

    if ( scale < 0.5 && factor < 1 )
    {
        return;
    }

    if ( scale > 100 && factor > 1 )
    {
        return;
    }

    scale *= factor;

    camera()->setScale ( Eigen::Vector3f ( scale, scale, scale ) );
}

void CameraTool::keyPressEvent ( QKeyEvent* event )
{
    if ( event->text() == "f" )
    {
        reset();
    }
}

void CameraTool::animate()
{

}

Camera* CameraTool::camera()
{
    return _scene->camera();
}


const Eigen::Vector2d CameraTool::mouseMovement ( QMouseEvent* event )
{
    return mousePosition ( event ) - _presPos;
}

void CameraTool::translateDrag ( QMouseEvent* event )
{
    Eigen::Vector2d dxy = mouseMovement ( event );

    Eigen::Vector3f tranlation = camera()->translation();
    tranlation[0] += _translateFactor * dxy[0];
    tranlation[1] += - _translateFactor * dxy[1];

    camera()->setTranslation ( tranlation );

    _presPos = mousePosition ( event );
}

void CameraTool::rotateDrag ( QMouseEvent* event )
{
    Eigen::Vector2d dxy = mouseMovement ( event );

    Eigen::Vector3f rotation = camera()->rotation();
    rotation[0] += _rotationFactor * dxy[1];
    rotation[1] += _rotationFactor * dxy[0];

    camera()->setRotation ( rotation );

    _presPos = mousePosition ( event );
}