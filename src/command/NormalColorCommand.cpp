
/*!
  \file     NormalColorCommand.cpp
  \author       Tody
  NormalColorCommand definition.
  date      2015/12/17
*/

#include "NormalColorCommand.h"


void NormalColorCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->vertexNormals ( N );

    Eigen::MatrixXd C  =  Eigen::MatrixXd::Ones ( N.rows(), 3 );

    for ( int i = 0; i < N.rows(); i++ )
    {
        Eigen::Vector3d n = N.row ( i ).normalized();

        for ( int j = 0; j < 3; j++ )
        {
            C ( i, j ) = 0.5 * N ( i, j ) + 0.5;
        }

    }

    mesh->setVertexColors ( C );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::VERTEX_COLOR );
}