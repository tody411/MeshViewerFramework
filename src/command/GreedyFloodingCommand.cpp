
//! GreedyFloodingCommand definition.
/*!
  \file     GreedyFloodingCommand.cpp
  \author       Tody
  \date     2016/03/10
*/

#include "GreedyFloodingCommand.h"

#include "GreedyFlooding.h"
#include "IsolatedCluster.h"
#include "RemoveSmallClusters.h"

#include <iostream>

void GreedyFloodingCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 0.2, 1.0,  0.5 );

    _M = L.transpose() * L;
}

void GreedyFloodingCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    int numFaces = mesh->numFaces();

    prefilterNormal ( N, _prefilterNormal.value(), N );

    Eigen::VectorXi clusterIDs ( mesh->numFaces() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        clusterIDs[fi] = -1;
    }

    GreedyFlooding flooding ( mesh );
    flooding.setTolerance ( _tolerance.value() );
    flooding.setFaceNormal ( N );

    flooding.flood ( clusterIDs );

    /*Eigen::VectorXd Area_f;
    mesh->Area_f ( Area_f );
    RemoveSmallClusters removeSmallClusters ( clusterIDs, Area_f, _M );
    clusterIDs = removeSmallClusters.clusterIDs();

    IsolatedCluster isolatedCluster ( _scene->mesh()->openMeshData() );
    isolatedCluster.compute ( clusterIDs );*/

    //smoothingWeights ( 10.0, clusterIDs );

    std::vector<int> faceLabels ( clusterIDs.size() );



    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        faceLabels[fi] = clusterIDs ( fi );
    }

    _scene->labelData()->setFaceLabelData ( faceLabels );
}


void GreedyFloodingCommand::prefilterNormal ( const Eigen::MatrixXd& N, double lambda, Eigen::MatrixXd& N_smooth )
{
    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    Eigen::SparseMatrix<double> A = I + lambda *  _M;
    Eigen::MatrixXd b = N;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    N_smooth = solver.solve ( b );

    N_smooth.rowwise().normalize();
}

void GreedyFloodingCommand::smoothingWeights ( double lambda, Eigen::VectorXi& clusterIDs )
{
    int numData = clusterIDs.size();
    int numCenters = clusterIDs.maxCoeff();

    Eigen::MatrixXd W  = Eigen::MatrixXd::Zero ( numData, numCenters );

    for ( int di = 0; di < numData; di++ )
    {
        int clusterID = clusterIDs ( di );

        if ( clusterID == -1 ) continue;

        W ( di, clusterIDs ( di ) ) = 1.0;
    }

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    Eigen::SparseMatrix<double> A = I + lambda *  _M;
    Eigen::MatrixXd b = W;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    W = solver.solve ( b );

    for ( int di = 0; di < numData; di++ )
    {
        W.row ( di ).maxCoeff ( &clusterIDs ( di ) );
    }
}