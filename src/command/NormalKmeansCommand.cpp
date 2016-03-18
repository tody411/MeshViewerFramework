
/*!
  \file     NormalKmeansCommand.cpp
  \author       Tody
  NormalKmeansCommand definition.
  date      2015/12/20
*/

#include "NormalKmeansCommand.h"

#include <random>
#include <iostream>

#include "PrimitiveFitting.h"
#include "KMeans.h"
#include "IsolatedCluster.h"
#include "RemoveSmallClusters.h"
#include "NormalColor.h"
#include "SuperFaces.h"
#include "EigenUtil.h"

void NormalKmeansCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 1.0, 1.0,  0.5 );

    _M = L.transpose() * L;
}

void NormalKmeansCommand::doImp ()
{
    LabelData* labelData = _scene->labelData();

    if ( !_scene->selectionInfo()->emptyFace() && !labelData->empty() )
    {
        doSelectedLabel();
    }

    else
    {
        doAll();
    }
}

void NormalKmeansCommand::doAll()
{
    int numCenters = _numCenters.value();

    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    int numFaces = mesh->numFaces();

    prefilterNormal ( N, _prefilterNormal.value(), N );

    Eigen::MatrixXd X = N;

    Eigen::MatrixXd V;
    mesh->faceCenters ( V );

    if ( _withPosition.value() )
    {
        double V_max = V.array().abs().maxCoeff();

        X = Eigen::MatrixXd::Zero ( X.rows(), 6 );
        X.block ( 0, 0, numFaces, 3 ) = N;
        X.block ( 0, 3, numFaces, 3 ) = 5.0 * V / V_max;
    }

    /* PrimitiveKMeans kmeans;
     kmeans.setNumCenters ( numCenters );
     kmeans.fit ( V, N );*/

    KMeans kmeans;

    kmeans.setNumCenters ( numCenters );
    kmeans.compute ( X );

    Eigen::VectorXi clusterIDs = kmeans.clusterIDs();

    /*SuperFaces superFaces;
    superFaces.compute ( N );
    Eigen::VectorXi clusterIDs = superFaces.clusterIDs();*/

    IsolatedCluster isolatedCluster ( _scene->mesh()->openMeshData() );
    isolatedCluster.compute ( clusterIDs );

    //Eigen::VectorXd Area_f;
    //mesh->Area_f ( Area_f );
    ////RemoveSmallClusters removeSmallClusters ( clusterIDs, Area_f, _M );
    ////clusterIDs = removeSmallClusters.clusterIDs();
    //isolatedCluster.compute ( clusterIDs );

    //smoothingWeights ( _postfilterWeight.value(), clusterIDs );

    _scene->labelData()->setFaceLabelData ( clusterIDs );
}

void NormalKmeansCommand::doSelectedLabel()
{
    std::vector<int> selection;
    _scene->selectionInfo()->faceSelection ( selection );

    int selectedFace = selection[0];

    LabelData* labelData = _scene->labelData();

    std::vector<int> faceLabels;
    labelData->faceLabelData ( faceLabels );

    int selectedLabel = faceLabels[selectedFace];

    std::vector<int> shellFaces;

    labelData->labelShell ( selectedLabel, shellFaces );

    Eigen::MatrixXd N_all;
    Mesh* mesh = _scene->mesh();
    mesh->faceNormals ( N_all );

    prefilterNormal ( N_all, _prefilterNormal.value(), N_all );

    int numFaces = mesh->numFaces();

    Eigen::MatrixXd X ( shellFaces.size(), 3 );

    for ( int si = 0; si < shellFaces.size(); si++ )
    {
        int fi = shellFaces[si];
        X.row ( si ) = N_all.row ( fi );
    }

    KMeans kmeans;
    int numCenters = _numCenters.value();
    kmeans.setNumCenters ( numCenters );
    kmeans.compute ( X );

    Eigen::VectorXi clusterIDs = kmeans.clusterIDs();

    int numLabels = labelData->numLabels();

    for ( int si = 0; si < shellFaces.size(); si++ )
    {
        int cid = clusterIDs ( si );

        if ( cid == 0 ) continue;

        int fi = shellFaces[si];

        faceLabels[fi] = numLabels + cid - 1;
    }

    labelData->setFaceLabelData ( faceLabels );
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

void NormalKmeansCommand::prefilterNormal ( const Eigen::MatrixXd& N, double lambda, Eigen::MatrixXd& N_smooth )
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

void NormalKmeansCommand::smoothingWeights ( double lambda, Eigen::VectorXi& clusterIDs )
{
    int numData = clusterIDs.size();
    int numCenters = _numCenters.value();

    Eigen::MatrixXd W  = Eigen::MatrixXd::Zero ( numData, numCenters );

    for ( int di = 0; di < numData; di++ )
    {
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