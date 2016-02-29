
/*!
  \file     NormalKmeansCommand.cpp
  \author       Tody
  NormalKmeansCommand definition.
  date      2015/12/20
*/

#include "NormalKmeansCommand.h"

#include <random>

#include "KMeans.h"
#include "NormalColor.h"

void NormalKmeansCommand::doImp ()
{
    int numCenters = _numCenters.value();

    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    int numFaces = mesh->numFaces();

    Eigen::MatrixXd X = N;

    if ( _withPosition.value() )
    {
        Eigen::MatrixXd V;
        mesh->faceCenters ( V );

        double V_max = V.array().abs().maxCoeff();

        X = Eigen::MatrixXd::Zero ( X.rows(), 6 );
        X.block ( 0, 0, numFaces, 3 ) = N;
        X.block ( 0, 3, numFaces, 3 ) = V / V_max / 3.0;
    }

    KMeans kmeans;

    kmeans.setNumCenters ( numCenters );
    kmeans.compute ( X );

    Eigen::VectorXi clusterIDs = kmeans.clusterIDs();

    std::vector<int> faceLabels ( clusterIDs.size() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        faceLabels[fi] = clusterIDs ( fi );
    }

    _scene->labelData()->setFaceLabelData ( faceLabels );
}

void NormalKmeansCommand::computeRandomCenters ( int numCenters, Eigen::MatrixXd& N_centers )
{
    N_centers.resize ( numCenters, 3 );

    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_real_distribution<double> randNormal ( -1.0, 1.0 );

    for ( int ci = 0; ci < numCenters; ci++ )
    {
        N_centers.row ( ci ) = Eigen::Vector3d ( randNormal ( mt ), randNormal ( mt ), randNormal ( mt ) ).normalized();
    }
}

void NormalKmeansCommand::clustering ( const Eigen::MatrixXd& N_centers, Eigen::MatrixXd& N, Eigen::VectorXi& ID )
{
    Eigen::MatrixXd W = N_centers * N.transpose();

    ID.resize ( N.rows() );

    for ( int vi = 0; vi < W.cols(); vi++ )
    {
        int cluster_id = 0;
        double w_max = 0.0;

        for ( int ci = 0; ci < W.rows(); ci++ )
        {
            if ( W ( ci,  vi ) > w_max )
            {
                w_max = W (  ci,  vi );
                cluster_id = ci;
            }
        }

        ID ( vi ) = cluster_id;
    }
}

void NormalKmeansCommand::project ( const Eigen::MatrixXd& N_centers, const Eigen::VectorXi& ID, Eigen::MatrixXd& N )
{
    N.resize ( ID.size(), 3 );

    for ( int vi = 0; vi < N.rows(); vi++ )
    {
        N.row ( vi ) = N_centers.row ( ID ( vi ) );
    }
}


void NormalKmeansCommand::updateCenters ( const Eigen::MatrixXd& N, const Eigen::VectorXi& ID, const Eigen::VectorXd& A_f, Eigen::MatrixXd& N_centers )
{
    N_centers = Eigen::MatrixXd::Zero ( N_centers.rows(), N_centers.cols() );

    for ( int vi = 0; vi < N.rows(); vi++ )
    {
        int ci = ID ( vi );

        N_centers.row ( ci ) += A_f ( vi ) * N.row ( vi );
    }

    N_centers.rowwise().normalize();
}