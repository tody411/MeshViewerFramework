
/*!
  \file     LaplacianSmoothingCommand.cpp
  \author       Tody
  LaplacianSmoothingCommand definition.
  date      2015/12/16
*/

#include "LaplacianSmoothingCommand.h"

void LaplacianSmoothingCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();
    mesh->points ( _V );

    Eigen::SparseMatrix<double> L;
    mesh->vertexLaplacian ( L );
    _M = L.transpose() * L;
}

void LaplacianSmoothingCommand::doImp ()
{
    double lambda = _lambda.value();

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();

    Eigen::SparseMatrix<double> A = I + lambda *  _M;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        return;
    }

    Eigen::MatrixXd V_new = solver.solve ( _V );

    Mesh* mesh = _scene->mesh();
    mesh->setPoints ( V_new );
}