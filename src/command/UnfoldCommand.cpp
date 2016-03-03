
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

    Eigen::MatrixXi UVIDs;
    mesh->UVIDs ( UVIDs );

    int numUVs = mesh->numUVs();

    Eigen::SparseMatrix<double> A_uv ( numUVs, numUVs );
    A_uv.reserve ( Eigen::VectorXi::Constant ( numUVs, 8 ) );

    for ( int fi = 0; fi < UVIDs.rows(); fi++ )
    {
        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            int uv0 = UVIDs ( fi, fvi );

            int fv1 = ( fvi + 1 ) % 3;
            int uv1 = UVIDs ( fi, fv1 );

            A_uv.insert ( uv0, uv1 ) = 1.0;
            A_uv.insert ( uv1, uv0 ) = 1.0;
        }
    }

    A_uv.makeCompressed();

    Eigen::SparseMatrix<double> W = A_uv.transpose() * A_uv;

    Eigen::SparseMatrix<double> L = W - A_uv;

    _M = L.transpose() * L;
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