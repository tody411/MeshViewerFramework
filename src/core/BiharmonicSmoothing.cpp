
/*!
  \file     BiharmonicSmoothing.cpp
  \author       Tody
  BiharmonicSmoothing definition.
  date      2016/03/17
*/

#include "BiharmonicSmoothing.h"

#include <iostream>

void BiharmonicSmoothing::setMesh ( Mesh* mesh )
{
    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, _w_u, _w_a, _sigma );
    _M = L.transpose() * L;
}

void BiharmonicSmoothing::setConstraints ( const Eigen::MatrixXd& b_cons )
{
    _b_cons = b_cons;

    _A_cons = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
}


const Eigen::MatrixXd BiharmonicSmoothing::smoothing ()
{
    double w_R = 0.00000001;
    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A = _A_cons + _lambda *  _M + w_R * I;
    Eigen::MatrixXd b = ( 1.0 + w_R ) * _b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    Eigen::MatrixXd W;

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return W;
    }

    W = solver.solve ( b );
    return W;
}

void BiharmonicSmoothing::smoothingClusters ( Eigen::VectorXi& clusterIDs )
{
    int numData = clusterIDs.size();
    int numCenters = clusterIDs.maxCoeff() + 1;

    _b_cons  = Eigen::MatrixXd::Zero ( numData, numCenters );

    for ( int di = 0; di < numData; di++ )
    {
        int clusterID = clusterIDs ( di );

        if ( clusterID == -1 ) continue;

        _b_cons ( di, clusterIDs ( di ) ) = 1.0;
    }

    setConstraints ( _b_cons );

    Eigen::MatrixXd W = smoothing();

    for ( int di = 0; di < numData; di++ )
    {
        W.row ( di ).maxCoeff ( &clusterIDs ( di ) );
    }
}