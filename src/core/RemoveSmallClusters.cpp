
/*!
  \file     RemoveSmallClusters.cpp
  \author       Tody
  RemoveSmallClusters definition.
  date      2016/03/07
*/

#include "RemoveSmallClusters.h"

#include <iostream>

#include "LabelData.h"
#include "ListUtil.h"
#include "EigenUtil.h"

void RemoveSmallClusters::compute()
{
    Eigen::VectorXd Area_c;

    computeClusterAreas ( Area_c );
    removeSmallClusters ( Area_c );

    double lambda = 100.0;

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    computeWeightConstraint ( A_cons, b_cons );
    double w_cons = 10.0 * lambda;
    double w_R = 0.000001;

    Eigen::SparseMatrix<double> A = w_cons * A_cons + lambda *  _M + w_R * I;
    Eigen::MatrixXd b = ( w_cons + w_R ) * b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cerr << "Solver Fail" << std::endl;
        return;
    }

    Eigen::MatrixXd W = solver.solve ( b );

    for ( int i = 0; i < W.rows(); i++ )
    {
        int clusterID = 0;
        W.row ( i ).maxCoeff ( &clusterID );

        _clusterIDs ( i ) = clusterID;
    }
}

void RemoveSmallClusters::computeClusterAreas ( Eigen::VectorXd& Area_c )
{
    int numClusters = _clusterIDs.maxCoeff() + 1;
    Area_c = Eigen::VectorXd::Zero ( numClusters );

    for ( int fi = 0; fi < _clusterIDs.size(); fi++ )
    {
        int clusterID = _clusterIDs ( fi );

        Area_c ( clusterID ) += _Area_f ( fi );
    }
}


void RemoveSmallClusters::removeSmallClusters ( const Eigen::VectorXd& Area_c )
{
    double area_sum = Area_c.sum();

    std::vector<bool> removed ( Area_c.size() );
    ListUtil::fill ( removed, false );

    for ( int ci = 0; ci < Area_c.size(); ci++ )
    {
        if ( Area_c[ci] < 0.005 * area_sum )
        {
            removed[ci] = true;
        }
    }

    for ( int fi = 0; fi < _clusterIDs.size(); fi++ )
    {
        int clusterID = _clusterIDs[fi];

        if ( removed[clusterID] )
        {
            _clusterIDs[fi] = -1;
        }
    }
}

void RemoveSmallClusters::computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b )
{
    int numFaces =  _clusterIDs.size();

    int numConstraints = _clusterIDs.maxCoeff() + 1;

    b = Eigen::MatrixXd::Zero ( numFaces, numConstraints );

    A.resize ( numFaces, numFaces );

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        int faceLabel = _clusterIDs ( fi );
        double w = 1.0;

        if ( faceLabel == -1 ) continue;

        A.insert ( fi, fi ) = w;
        b ( fi, faceLabel ) = w;
    }

    A.makeCompressed();
}