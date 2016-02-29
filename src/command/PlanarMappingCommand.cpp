
//! PlanarMappingCommand definition.
/*!
  \file     PlanarMappingCommand.cpp
  \author       Tody
  \date     2016/02/29
*/

#include "PlanarMappingCommand.h"


void PlanarMappingCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    MeshData* meshData = mesh->openMeshData();

    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::MatrixXd UV = V.block ( 0, 0, V.rows(), 2 );

    Eigen::VectorXd UV_min = UV.colwise().minCoeff();
    Eigen::VectorXd UV_max = UV.colwise().maxCoeff();

    //Eigen::VectorXd UV_min = Eigen::VectorXd::Zero ( 2 );

    UV.rowwise() -= UV_min.transpose();
    UV.block ( 0, 0, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 0 );
    UV.block ( 0, 1, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 1 );

    int numVertices = mesh->numVertices();

    for ( int vi = 0; vi < numVertices; vi++ )
    {
        OpenMesh::Vec2f uv ( UV ( vi, 0 ), UV ( vi, 1 ) );
        MeshData::VertexHandle v_h = meshData->vertex_handle ( vi );
        meshData->set_texcoord2D ( v_h, uv );
    }
}