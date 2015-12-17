
/*!
  \file     CoordinateSystemOverlay.cpp
  \author       Tody
  CoordinateSystemOverlay definition.
  date      2015/12/17
*/

#include "CoordinateSystemOverlay.h"

#include <QtOpenGL>

#include <Eigen/Dense>

using namespace Eigen;

void CoordinateSystemOverlay::renderViewOverlayImp()
{

    float axisLength = 0.1f;

    Vector3f xyzs[3] = {Vector3f ( axisLength, 0, 0 ),
                        Vector3f ( 0, axisLength, 0 ),
                        Vector3f ( 0, 0, axisLength )
                       };

    Eigen::Vector2f rotation = _cameraTool->rotation();
    double aspect = _cameraTool->aspect();

    Vector3f center ( - aspect * 0.8, -0.8, 0.0 );

    glTranslatef ( center[0], center[1], center[2] );

    glRotatef ( rotation[0], 1.0f, 0.0f, 0.0f );
    glRotatef ( rotation[1], 0.0f, 1.0f, 0.0f );

    glDisable ( GL_LIGHTING );
    glBegin ( GL_LINES );

    glColor3f ( 1.0, 0.0, 0.0 );
    glVertex3f ( 0, 0, 0 );
    glVertex3fv ( xyzs[0].data() );

    glColor3f ( 0.0, 1.0, 0.0 );
    glVertex3f ( 0, 0, 0 );
    glVertex3fv ( xyzs[1].data() );

    glColor3f ( 0.0, 0.0, 1.0 );
    glVertex3f ( 0, 0, 0 );
    glVertex3fv ( xyzs[2].data() );

    glEnd();
}