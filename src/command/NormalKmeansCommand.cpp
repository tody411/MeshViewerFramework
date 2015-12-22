
/*!
  \file     NormalKmeansCommand.cpp
  \author       Tody
  NormalKmeansCommand definition.
  date      2015/12/20
*/

#include "NormalKmeansCommand.h"

#include <random>

#include "NormalColor.h"

void NormalKmeansCommand::doImp ()
{
    int numCenters = _numCenters.value();

    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    Eigen::VectorXd A_f;
    mesh->Area_f ( A_f );

    Eigen::MatrixXd N_centers;
    computeRandomCenters ( numCenters, N_centers );

    Eigen::VectorXi ID;

    Eigen::MatrixXd N_new;

    int numIterations = 20;

    for ( int i = 0; i < numIterations; i++ )
    {
        clustering ( N_centers, N, ID );
        project ( N_centers, ID, N_new );
        updateCenters ( N, ID, A_f, N_centers );
    }

    Eigen::MatrixXd C;
    NormalColor::normalToColor ( N_new, C );

    mesh->setFaceColors ( C );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
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