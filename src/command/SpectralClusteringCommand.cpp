
/*!
  \file     SpectralClusteringCommand.cpp
  \author       Tody
  SpectralClusteringCommand definition.
  date      2015/12/20
*/

#include "SpectralClusteringCommand.h"

#include "RedSVD.h"

#include <iostream>

void SpectralClusteringCommand::setupImp()
{
    int numCenters = _numCenters.value();

    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->W_ff ( L, 2.0 );


    RedSVD::RedSymEigen<Eigen::SparseMatrix<double>> solver ( L, numCenters );

    _U = solver.eigenvectors().transpose();

    Eigen::VectorXd l = solver.eigenvalues();

    std::cout << "Eigen Vector Shape: " << _U.rows() << "," << _U.cols() << std::endl;
    std::cout << "Eigen Values: " << l << std::endl;
}

void SpectralClusteringCommand::doImp ()
{
    int numCenters = _numCenters.value();

    if ( numCenters != _U.rows() ) setupImp();

    int clusderID = _clusterID.value();

    clusderID = std::min<int> ( clusderID, numCenters - 1 );

    Eigen::VectorXd U = _U.row ( clusderID );


    Eigen::MatrixXd C ( U.size(), 3 );

    double U_max = fabs ( U.maxCoeff() );
    double U_min = U.minCoeff();
    double U_mean = U.mean();

    double U_range = U_max - U_min;

    std::cout << "U range: " << U_min << "," << U_max << std::endl;


    for ( int fi = 0; fi < C.rows(); fi++ )
    {
        //double w = ( U ( fi ) - U_min ) / U_range;
        double w = fabs ( U ( fi ) ) / U_max;

        C.row ( fi ) = Eigen::Vector3d ( w, w, w );
        /*if ( U ( fi ) > U_mean )
        {
            C.row ( fi ) = Eigen::Vector3d::Ones();
        }*/
    }

    Mesh* mesh = _scene->mesh();
    mesh->setFaceColors ( C );
    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}