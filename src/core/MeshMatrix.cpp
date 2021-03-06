
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

    Eigen::SparseMatrix<double> A;
    Nadj_ff ( A, 1 );

    for ( int k = 0; k < A.outerSize(); ++k )
    {
        for ( Eigen::SparseMatrix<double>::InnerIterator it ( A, k ); it; ++it )
        {
            MeshData::FaceHandle f_p ( it.row() );
            MeshData::FaceHandle f_q ( it.col() );

            OpenMesh::Vec3f N_p = _mesh.normal ( f_p );
            OpenMesh::Vec3f N_q = _mesh.normal ( f_q );

            double d = 1.0 - OpenMesh::dot ( N_p, N_q );
            double w = exp ( - ( d * d ) / ( sigma * sigma ) );

            W.insert ( it.row(), it.col() ) = w;
        }
    }

    for ( int fi = 0; fi < numFaces(); fi++ )
    {
        W.insert ( fi, fi ) = 1.0;
    }

    /*MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
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
        }*/

    /*for ( ff_it = _mesh.ff_begin ( *f_it ); ff_it.is_valid(); ++ff_it )
    {
        OpenMesh::Vec3f N_q = _mesh.normal ( *ff_it );

        double d = 1.0 - OpenMesh::dot ( N_p, N_q );
        double w = exp ( - ( d * d ) / ( sigma * sigma ) ) / w_sum;
        W.insert ( f_it->idx(), ff_it->idx() ) = -w;
    }*/

    //W.insert ( f_it->idx(), f_it->idx() ) = w_sum;
    //}

    W.makeCompressed();
}

void MeshMatrix::Adj_ff ( Eigen::SparseMatrix<double>& A )
{
    int numRows = numFaces();
    int numCols = numRows;

    A.resize ( numRows, numCols );

    A.reserve ( Eigen::VectorXi::Constant ( numCols, 8 ) );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceFaceIter ff_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        for ( ff_it = _mesh.ff_begin ( *f_it ); ff_it.is_valid(); ++ff_it )
        {
            A.insert ( f_it->idx(), ff_it->idx() ) = 1.0;
        }
    }

    A.makeCompressed();
}

void MeshMatrix::Adj_ef ( Eigen::MatrixXi& A )
{
    int numRows = numEdges();
    int numCols = 2;

    A.resize ( numRows, numCols );

    A.fill ( - 1 );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceEdgeIter fe_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        int fID = f_it->idx();

        for ( fe_it = _mesh.fe_begin ( *f_it ); fe_it.is_valid(); ++fe_it )
        {
            int eID = fe_it->idx();

            if ( A ( eID, 0 ) == -1 )
            {
                A ( eID, 0 ) = fID;
            }
            else
            {
                A ( eID, 1 ) = fID;
            }
        }
    }
}

void MeshMatrix::Nadj_ff ( Eigen::SparseMatrix<double>& A,  int n  )
{
    Eigen::SparseMatrix<double> A0;
    Adj_ff ( A0 );
    A = A0;
    for ( int i = 1; i < n; i++ )
    {
        A = A * A0;
    }

    for ( int k = 0; k < A.outerSize(); ++k )
    {
        for ( Eigen::SparseMatrix<double>::InnerIterator it ( A, k ); it; ++it )
        {
            it.valueRef() = 1.0;
        }
    }
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