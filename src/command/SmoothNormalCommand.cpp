
/*!
  \file     SmoothNormalCommand.cpp
  \author       Tody
  SmoothNormalCommand definition.
  date      2015/12/21
*/

#include "SmoothNormalCommand.h"

#include "NormalColor.h"

void SmoothNormalCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();
    mesh->faceNormals ( _N );

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L );
    _M = L.transpose() * L;
}

void SmoothNormalCommand::doImp ()
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

    Eigen::MatrixXd N_new = solver.solve ( _N );

    Eigen::MatrixXd C;
    NormalColor::normalToColor ( N_new, C );

    Mesh* mesh = _scene->mesh();
    mesh->setFaceColors ( C );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}