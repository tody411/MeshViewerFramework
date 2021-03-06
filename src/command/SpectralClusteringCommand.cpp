
/*!
  \file     SpectralClusteringCommand.cpp
  \author       Tody
  SpectralClusteringCommand definition.
  date      2015/12/20
*/

#include "SpectralClusteringCommand.h"

#include "RedSVD.h"
#include "EigenSolver.h"
#include "SpectralWeightSolver.h"

#include <iostream>

void SpectralClusteringCommand::setupImp()
{
    int numCenters = _numCenters.value();

    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    Eigen::SparseMatrix<double> L;
    mesh->W_ff ( L, 0.5 );

    if ( _isSparse.value() )
    {
        computeSpectralWeightSolver ( L, numCenters );
    }

    else
    {
        computeDense ( L, numCenters );
    }
    _isSparseOld = _isSparse.value();
}

void SpectralClusteringCommand::doImp ()
{
    int numCenters = _numCenters.value();

    if ( _isSparseOld != _isSparse.value() )
    {
        setupImp();
    }

    //if ( numCenters != _U.rows() ) setupImp();

    int clusderID = _clusterID.value();

    clusderID = std::min<int> ( clusderID, _U.rows() - 1 );

    Eigen::VectorXd U = _U.row ( clusderID );


    Eigen::MatrixXd C ( U.size(), 3 );

    double U_max = U.maxCoeff();
    double U_min = U.minCoeff();
    double U_mean = U.mean();

    double U_range = U_max - U_min;

    std::cout << "U range: " << U_min << "," << U_max << std::endl;


    for ( int fi = 0; fi < C.rows(); fi++ )
    {
        double r = ( U ( fi ) - U_mean ) / ( U_max - U_mean ) ;
        r = std::min ( 1.0, std::max ( 0.0, r ) );
        double b = 1.0 - ( U ( fi ) - U_min ) / ( U_mean - U_min );
        b = std::min ( 1.0, std::max ( 0.0, b ) );

        double g = 1.0 - ( r + b );

        C.row ( fi ) = Eigen::Vector3d ( r, g, b );

    }

    Mesh* mesh = _scene->mesh();
    mesh->setFaceColors ( C );
    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}

void SpectralClusteringCommand::computeDense ( const Eigen::SparseMatrix<double>& L, int numCenters )
{
    Eigen::MatrixXd L_dens = L;

    Eigen::EigenSolver<Eigen::MatrixXd> solver ( L_dens );

    _U = solver.eigenvectors().real().transpose();

    //Eigen::VectorXd l = solver.eigenvalues();

    std::cout << "Eigen Vector Shape: " << _U.rows() << "," << _U.cols() << std::endl;
    //std::cout << "Eigen Values: " << l << std::endl;
}

void SpectralClusteringCommand::computeSparse ( const Eigen::SparseMatrix<double>& L, int numCenters )
{
    std::cout << "L.norm: "  << L.norm() << std::endl;
    EigenSolver<Eigen::SparseMatrix<double>> solver ( L, numCenters );

    _U = solver.eigenvectors().transpose();
    _U = Eigen::abs ( _U.array() );

    Eigen::VectorXd l = solver.eigenvalues();

    std::cout << "Eigen Vector Shape: " << _U.rows() << "," << _U.cols() << std::endl;
    std::cout << "Eigen Values: " << l << std::endl;
}

void SpectralClusteringCommand::computeSpectralWeightSolver ( const Eigen::SparseMatrix<double>& L, int numCenters )
{
    SpectralWeightSolver<Eigen::SparseMatrix<double>> solver ( L );
    _U = solver.weights().transpose();
}

void SpectralClusteringCommand::computeSparseRedSVD ( const Eigen::SparseMatrix<double>& L, int numCenters )
{
    std::cout << "L.norm: "  << L.norm() << std::endl;
    RedSVD::RedSymEigen<Eigen::SparseMatrix<double>> solver ( L, numCenters );

    _U = solver.eigenvectors().transpose();

    Eigen::VectorXd l = solver.eigenvalues();

    std::cout << "Eigen Vector Shape: " << _U.rows() << "," << _U.cols() << std::endl;
    std::cout << "Eigen Values: " << l << std::endl;

    RedSVD::RedSVD<Eigen::SparseMatrix<double>> svdSolver ( L, numCenters );

    Eigen::MatrixXd U_svd = svdSolver.matrixU().transpose();
    Eigen::MatrixXd V_svd = svdSolver.matrixV().transpose();

    std::cout << "U_svd: " << U_svd.rows() << "," << U_svd.cols() << std::endl;
    std::cout << "V_svd: " << V_svd.rows() << "," << V_svd.cols() << std::endl;
}

void SpectralClusteringCommand::fullWeightMatrix ( const  Eigen::MatrixXd& N, Eigen::MatrixXd& W )
{
    Eigen::MatrixXd D = N * N.transpose();
    D = Eigen::MatrixXd::Ones ( D.rows(), D.cols() ) - D;

    std::cout << "D: " << D.rows() << "," << D.cols() << std::endl;

    double sigma = 0.5;

    D = - ( 1.0 / ( sigma * sigma ) ) * D;

    W = Eigen::exp ( D.array() );

    for ( int i = 0; i < W.rows(); i++ )
    {
        W ( i, i ) = 0.0;
    }

    Eigen::EigenSolver<Eigen::MatrixXd> solver ( W );

    _U = solver.eigenvectors().real().transpose();
}