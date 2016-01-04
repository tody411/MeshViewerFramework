
/*!
  \file     MeshMatrix.cpp
  \author       Tody
  MeshMatrix definition.
  date      2015/12/21
*/

#include "MeshMatrix.h"


void MeshMatrix::L_vv ( Eigen::SparseMatrix<double>& L )
{
    int numRows = numVertices();
    int numCols = numRows;

    L.resize ( numRows, numCols );

    L.reserve ( Eigen::VectorXi::Constant ( numCols, 8 ) );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );
    MeshData::VertexVertexIter vv_it;

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        double w_sum = 0.0;
        for ( vv_it = _mesh.vv_begin ( *v_it ); vv_it.is_valid(); ++vv_it )
        {
            double w = 1.0;
            L.insert ( v_it->idx(), vv_it->idx() ) = -w;
            w_sum += w;
        }

        L.insert ( v_it->idx(), v_it->idx() ) = w_sum;
    }

    L.makeCompressed();
}

void MeshMatrix::L_ff ( Eigen::SparseMatrix<double>& L, double w_u, double w_a, double sigma_a )
{
    int numRows = numFaces();
    int numCols = numRows;

    L.resize ( numRows, numCols );

    L.reserve ( Eigen::VectorXi::Constant ( numCols, 8 ) );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceFaceIter ff_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        double w_sum = 0.0;

        OpenMesh::Vec3f N_p = _mesh.normal ( *f_it );

        for ( ff_it = _mesh.ff_begin ( *f_it ); ff_it.is_valid(); ++ff_it )
        {
            OpenMesh::Vec3f N_q = _mesh.normal ( *ff_it );

            //double theta = acos ( OpenMesh::dot ( N_p, N_q ) );
            double theta = 1.0 - OpenMesh::dot ( N_p, N_q );

            double w = w_u + w_a * exp ( - ( theta * theta ) / ( sigma_a * sigma_a ) );

            L.insert ( f_it->idx(), ff_it->idx() ) = -w;
            w_sum += w;
        }

        L.insert ( f_it->idx(), f_it->idx() ) = w_sum;
    }

    L.makeCompressed();
}

void MeshMatrix::W_ff ( Eigen::SparseMatrix<double>& W, double sigma )
{
    int numRows = numFaces();
    int numCols = numRows;

    W.resize ( numRows, numCols );

    W.reserve ( Eigen::VectorXi::Constant ( numCols, 8 ) );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceFaceIter ff_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        double w_sum = 0.0;

        OpenMesh::Vec3f N_p = _mesh.normal ( *f_it );

        for ( ff_it = _mesh.ff_begin ( *f_it ); ff_it.is_valid(); ++ff_it )
        {
            OpenMesh::Vec3f N_q = _mesh.normal ( *ff_it );

            double d = 1.0 - OpenMesh::dot ( N_p, N_q );
            double w = exp ( - ( d * d ) / ( sigma * sigma ) );
            W.insert ( f_it->idx(), ff_it->idx() ) = w;
            w_sum += w;
        }

        /*for ( ff_it = _mesh.ff_begin ( *f_it ); ff_it.is_valid(); ++ff_it )
        {
            OpenMesh::Vec3f N_q = _mesh.normal ( *ff_it );

            double d = 1.0 - OpenMesh::dot ( N_p, N_q );
            double w = exp ( - ( d * d ) / ( sigma * sigma ) ) / w_sum;
            W.insert ( f_it->idx(), ff_it->idx() ) = -w;
        }*/

        //W.insert ( f_it->idx(), f_it->idx() ) = w_sum;
    }

    W.makeCompressed();
}

void MeshMatrix::Area_f ( Eigen::VectorXd& A )
{
    A.resize ( numFaces() );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceVertexIter fv_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        fv_it = _mesh.fv_begin ( *f_it );

        OpenMesh::Vec3f v1 = _mesh.point ( *fv_it );
        ++fv_it;
        OpenMesh::Vec3f v2 = _mesh.point ( *fv_it );
        ++fv_it;
        OpenMesh::Vec3f v3 = _mesh.point ( *fv_it );
        ++fv_it;

        A ( f_it->idx() ) = 0.5f * OpenMesh::cross ( v2 - v1, v3 - v1 ).norm();
    }
}