
/*!
  \file     UnfoldCommand.cpp
  \author       Tody
  UnfoldCommand definition.
  date      2016/03/03
*/

#include "UnfoldCommand.h"

void UnfoldCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();
    if ( !mesh->hasUVs() ) return;

    mesh->UVs ( _UVs );

    if ( !mesh->hasUVIDs() )
    {
        Eigen::SparseMatrix<double> L;
        mesh->vertexLaplacian ( L );
        _M = L.transpose() * L;
        return;
    }

    Eigen::MatrixXi A_fv;
    mesh->Adj_fv ( A_fv );

    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::MatrixXi UVIDs;
    mesh->UVIDs ( UVIDs );

    int numUVs = mesh->numUVs();

    Eigen::SparseMatrix<double> L_uv ( numUVs, numUVs );
    L_uv.reserve ( Eigen::VectorXi::Constant ( numUVs, 8 ) );

    double e_max  = 0.0;

    for ( int fi = 0; fi < UVIDs.rows(); fi++ )
    {
        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            int v0 = A_fv ( fi, fvi );
            int uv0 = UVIDs ( fi, fvi );

            int fv1 = ( fvi + 1 ) % 3;
            int uv1 = UVIDs ( fi, fv1 );
            int v1 =  A_fv ( fi, fv1 );

            double e = ( V.row ( v0 ) - V.row ( v1 ) ).norm();

            e_max = std::max ( e, e_max );

            L_uv.coeffRef ( uv0, uv1 ) = - e;
            L_uv.coeffRef  ( uv1, uv0 ) = - e;
        }
    }

    L_uv = ( 1.0 / e_max ) * L_uv;

    Eigen::VectorXd w_sum = Eigen::VectorXd::Zero ( numUVs );

    for ( int k = 0; k < L_uv.outerSize(); ++k )
    {
        for ( Eigen::SparseMatrix<double>::InnerIterator it ( L_uv, k ); it; ++it )
        {
            w_sum ( it.row() ) += -it.value();
        }
    }

    for ( int uvi = 0; uvi < numUVs; uvi++ )
    {
        L_uv.coeffRef ( uvi, uvi ) = w_sum ( uvi );
    }

    L_uv.makeCompressed();

    _M = L_uv.transpose() * L_uv;
}

void UnfoldCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();
    if ( !mesh->hasUVs() ) return;

    double lambda = _lambda.value();

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();

    Eigen::SparseMatrix<double> A = I + lambda *  _M;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        return;
    }

    Eigen::MatrixXd UVs = solver.solve ( _UVs );

    mesh->setUVs ( UVs );
}