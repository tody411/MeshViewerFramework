
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

    QFont font ( "Arial", 9, QFont::Bold );

    for ( int i = 0; i < 3; i++ )
    {
        xyzs[i] *= 1.3;
    }

    glColor3f ( 1.0, 0.0, 0.0 );
    _view->renderText ( xyzs[0][0], xyzs[0][1], xyzs[0][2], "x", font );

    glColor3f ( 0.0, 1.0, 0.0 );
    _view->renderText ( xyzs[1][0], xyzs[1][1], xyzs[1][2], "y" , font );

    glColor3f ( 0.0, 0.0, 1.0 );
    _view->renderText ( xyzs[2][0], xyzs[2][1], xyzs[2][2], "z", font );
}