
/*!
  \file     PositionColorCommand.cpp
  \author       Tody
  PositionColorCommand definition.
  date      2015/12/18
*/

#include "PositionColorCommand.h"


void PositionColorCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::MatrixXd C  =  Eigen::MatrixXd::Ones ( V.rows(), 3 );

    Eigen::Vector3d V_min = V.colwise().minCoeff();

    Eigen::Vector3d V_max = V.colwise().maxCoeff();

    for ( int vi = 0; vi < V.rows(); vi++ )
    {
        for ( int ci = 0; ci < 3; ci++ )
        {
            C ( vi, ci ) = ( V ( vi, ci ) - V_min ( ci ) ) / ( V_max ( ci ) - V_min ( ci ) );
        }
    }

    mesh->setVertexColors ( C );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::VERTEX_COLOR );
}