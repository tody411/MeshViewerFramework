
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

void NormalKmeansCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 0.001, 1.0,  0.5 );

    _M = L.transpose() * L;
}

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

    smoothingWeights ( clusterIDs );

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

void NormalKmeansCommand::smoothingWeights ( Eigen::VectorXi& clusterIDs )
{
    int numData = clusterIDs.size();
    int numCenters = _numCenters.value();

    Eigen::MatrixXd W  = Eigen::MatrixXd::Zero ( numData, numCenters );

    for ( int di = 0; di < numData; di++ )
    {
        W ( di, clusterIDs ( di ) ) = 1.0;
    }

    double lambda = 1.0;
    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    double w_cons = 0.01 * lambda;
    double w_R = 0.000001;

    Eigen::SparseMatrix<double> A = w_cons * I + lambda *  _M;
    Eigen::MatrixXd b = w_cons * W;

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