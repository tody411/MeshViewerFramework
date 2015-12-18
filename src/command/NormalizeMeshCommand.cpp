
/*!
  \file     NormalizeMeshCommand.cpp
  \author       Tody
  NormalizeMeshCommand definition.
  date      2015/12/17
*/

#include "NormalizeMeshCommand.h"


void NormalizeMeshCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    int numVertices = mesh->numVertices();

    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::Vector3d V_min = V.colwise().minCoeff();

    Eigen::Vector3d V_max = V.colwise().maxCoeff();

    Eigen::MatrixXd V_new = V;

    for ( int vi = 0; vi < numVertices; vi++ )
    {
        for ( int ci = 0; ci < 3; ci++ )
        {
            V_new ( vi, ci ) = ( V_new ( vi, ci ) - V_min ( ci ) ) / ( V_max ( ci ) - V_min ( ci ) );
        }
    }

    mesh->setPoints ( V_new );
}