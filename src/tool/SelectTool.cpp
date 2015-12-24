
/*!
  \file     SelectTool.cpp
  \author       Tody
  SelectTool definition.
  date      2015/12/18
*/

#include "SelectTool.h"

#include "Eigen/Dense"

#include <QtOpenGL>

#include "PointOnMesh.h"
#include "RayCasting.h"
#include "Scene.h"

void SelectTool::mousePressEvent ( QMouseEvent* event )
{
    Eigen::Vector3d pNear, ray;
    unproject ( mousePosition ( event ), pNear, ray );

    RayCasting rayCasting ( _scene->mesh()->openMeshData() );

    QString message = "Select Tool: ";

    if ( rayCasting.closestIntersection ( pNear, ray, _intersectedPoint ) )
    {
        message += "intersected";
        message += QString::fromStdString ( _intersectedPoint.str() );

        if ( ! ( event->modifiers() & Qt::ShiftModifier ) )
        {
            _scene->selectionInfo()->clearFaceSelection();
        }

        _scene->selectionInfo()->addFaceSelection ( _intersectedPoint.index() );
    }
    else
    {
        message += "no intersection";
        _scene->showMessage ( message );
        _scene->selectionInfo()->clearFaceSelection();
    }

    _scene->showMessage ( message );
}

void SelectTool::renderSceneOverlay()
{
    if ( _intersectedPoint.isValid() )
    {
        Eigen::Matrix3f V;
        _intersectedPoint.points ( V );

        glDisable ( GL_LIGHTING );
        glDisable ( GL_DEPTH_TEST );

        glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );

        glColor4f ( 0.5f, 0.2f, 1.0f, 0.5f );
        glBegin ( GL_POINTS );
        glVertex3fv ( _intersectedPoint.point().data() );
        glEnd();

        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    }
}