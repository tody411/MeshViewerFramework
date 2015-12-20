
/*!
  \file     BaseTool.cpp
  \author       Tody
  BaseTool definition.
  date      2015/12/18
*/

#include "BaseTool.h"

#include <QMouseEvent>

#include "Scene.h"
#include "ModelView.h"


void BaseTool::setScene ( Scene* scene )
{
    _scene = scene;
}


void BaseTool::setView ( ModelView* view )
{
    _view = view;
}

void BaseTool::activate()
{
    _view->setTool ( this );
}

void BaseTool::deactivate()
{
    _view->setTool ( nullptr );
}

void BaseTool::mousePressEvent ( QMouseEvent* event )
{
    if ( event->modifiers() & Qt::AltModifier )
    {
        return;
    }
}

const Eigen::Vector2d BaseTool::mousePosition ( QMouseEvent* event )
{
    return _view->mousePosition ( event );
}


void BaseTool::unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray )
{
    _view->unproject ( p, pNear, ray );
}