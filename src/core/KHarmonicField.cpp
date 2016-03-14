
//! KHarmonicField definition.
/*!
  \file     KHarmonicField.cpp
  \author       Tody
  \date     2016/03/14
*/

#include "KHarmonicField.h"

#include <random>
#include <iostream>

void KHarmonicField::compute()
{
    std::vector<int> seedFaces;
    seedFaces.push_back ( 0 );

    while ( seedFaces.size() < _numCenters )
    {
        optimizeWithIncremental ( seedFaces );
    }
    /*computeRandomCenters ( _numCenters, seedFaces );

    for ( int i = 0; i < 5; i++ )
    {
        optimize ( seedFaces );
    }*/
    updateClusterIDs ();
}

void KHarmonicField::optimize ( std::vector<int>& seedFaces )
{
    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    computeWeightConstraint ( seedFaces, A_cons, b_cons );
    double lambda = 100.0;
    double w_cons = 10.0 * lambda;
    double w_R = 0.000001;

    Eigen::SparseMatrix<double> A = w_cons * A_cons + lambda *  _M + w_R * I;
    Eigen::MatrixXd b = ( w_cons + w_R ) * b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    _W = solver.solve ( b );

    A = lambda *  _M + w_cons * I;
    b = w_cons * _W;

    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    _W = solver.solve ( b );

    updateCenter ( seedFaces );
}

void KHarmonicField::optimizeWithIncremental ( std::vector<int>& seedFaces )
{
    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    computeWeightConstraint ( seedFaces, A_cons, b_cons );
    double lambda = 100.0;
    double w_cons = 10.0 * lambda;
    double w_R = 0.000001;

    Eigen::SparseMatrix<double> A = w_cons * A_cons + lambda *  _M + w_R * I;
    Eigen::MatrixXd b = ( w_cons + w_R ) * b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    _W = solver.solve ( b );

    int numFaces = _M.rows();

    Eigen::VectorXd W_norm ( numFaces );

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        W_norm[fi] = _W.row ( fi ).norm();
    }

    int seedFace = 0;
    W_norm.minCoeff ( &seedFace );

    seedFaces.push_back ( seedFace );
}


void KHarmonicField::computeRandomCenters ( int numCenters, std::vector<int>& seedFaces )
{
    int numFaces = _M.rows();

    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_int_distribution<int> randCenter ( 0, numFaces - 1 );

    for ( int i = 0; i < numCenters; i++ )
    {
        seedFaces.push_back ( randCenter ( mt ) );
    }
}


void KHarmonicField::computeWeightConstraint ( const std::vector<int>& seedFaces, Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b )
{
    int numFaces = _M.rows();

    A.resize ( numFaces, numFaces );

    b = Eigen::MatrixXd::Zero ( numFaces, _numCenters );

    for ( int i = 0; i < seedFaces.size(); i++ )
    {
        int fi = seedFaces[i];
        A.insert ( fi, fi ) = 1.0;
        b ( fi, i ) = 1.0;
    }

    A.makeCompressed();
}

void KHarmonicField::updateCenter ( std::vector<int>& seedFaces )
{
    for ( int ci = 0; ci < _W.cols(); ci++ )
    {
        int seedFace;
        _W.col ( ci ).maxCoeff ( &seedFace );

        seedFaces[ci] = seedFace;
    }
}

void KHarmonicField::updateClusterIDs ()
{
    int numFaces = _M.rows();

    _clusterIDs.resize ( numFaces );

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        int clusterID = 0;
        _W.row ( fi ).maxCoeff ( &clusterID );

        if ( clusterID > -1 && clusterID < _numCenters )
        {
            _clusterIDs ( fi ) = clusterID;
        }
    }
}