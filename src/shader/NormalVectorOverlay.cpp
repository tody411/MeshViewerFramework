
/*!
  \file     NormalVectorOverlay.cpp
  \author       Tody
  NormalVectorOverlay definition.
  date      2015/12/20
*/

#include "NormalVectorOverlay.h"


#include <QtOpenGL>

void NormalVectorOverlay::renderSceneOverlayImp()
{
    Mesh* mesh = _scene->mesh();

    double bb_size = mesh->boundingBox().size();
    double n_size = 0.01 * bb_size;

    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::MatrixXd N;
    mesh->vertexNormals ( N );

    N = V + n_size * N;

    glDisable ( GL_LIGHTING );
    glEnable ( GL_DEPTH_TEST );

    glColor3f ( 1.0f, 0.0f, 0.0f );

    glBegin ( GL_LINES );

    for ( int vi = 0; vi < V.rows(); vi++ )
    {
        Eigen::Vector3d v = V.row ( vi );
        Eigen::Vector3d n = N.row ( vi );

        glVertex3f ( v[0], v[1], v[2] );
        glVertex3f ( n[0], n[1], n[2] );
    }
    glEnd();
}