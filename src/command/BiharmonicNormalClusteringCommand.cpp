
//! BiharmonicNormalClusteringCommand definition.
/*!
  \file     BiharmonicNormalClusteringCommand.cpp
  \author       Tody
  \date     2015/12/22
*/

#include "BiharmonicNormalClusteringCommand.h"

#include "ColorMap.h"

#include <iostream>

void BiharmonicNormalClusteringCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 0.0001, 1.0,  0.3 );
    //mesh->faceLaplacian ( L, 1.0, 0.0,  0.5 );

    _M = L.transpose() * L;
}

void BiharmonicNormalClusteringCommand::doImp ()
{
    LabelData* labelData = _scene->labelData();

    if ( labelData->empty() ) return;

    Mesh* mesh = _scene->mesh();

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
        std::cout << "Solver Fail" << std::endl;
        return;
    }

    Eigen::MatrixXd W = solver.solve ( b );

    /*   w_R = lambda;
       A = lambda *  _M + w_R * I;
       b = w_R * W;

       solver.compute ( A );

       if ( solver.info() != Eigen::Success )
       {
           std::cout << "Solver Fail" << std::endl;
           return;
       }

       W = solver.solve ( b );*/

    for ( int i = 0; i < W.rows(); i++ )
    {
        double w_sum = 0.00000001;

        //double w_min = W.row ( i ).minCoeff();

        for ( int j = 0; j < W.cols(); j++ )
        {
            double w = W ( i, j );
            if ( w < 0.0 )
            {
                w = 0.0;
            }

            if ( w > 1.0 )
            {
                w = 1.0;
            }

            W ( i, j ) = w;
            w_sum += w;
        }

        W.row ( i ) = W.row ( i ) / w_sum;
    }

    std::vector<int> faceLabels ( W.rows() );

    for ( int i = 0; i < W.rows(); i++ )
    {
        int maxID = LabelData::UNLABELED;
        double w_max = 0.0;
        for ( int j = 0; j < W.cols(); j++ )
        {
            if ( W ( i, j ) > w_max )
            {
                w_max = W ( i, j );
                maxID = j;
            }
        }

        faceLabels[i] = maxID;
    }

    labelData->setFaceLabelData ( faceLabels );

    Eigen::MatrixXd C ( _scene->mesh()->numFaces(), 3 );

    Eigen::MatrixXd Cid;
    ColorMap::generateIDColors ( W.cols(), Cid );

    if ( _showSmoothColor.value() )
    {
        C = W * Cid;
    }

    else
    {
        for ( int i = 0; i < W.rows(); i++ )
        {
            int maxID = 0;
            double w_max = 0.0;
            for ( int j = 0; j < W.cols(); j++ )
            {
                if ( W ( i, j ) > w_max )
                {
                    w_max = W ( i, j );
                    maxID = j;
                }
            }

            C.row ( i ) = Cid.row ( maxID );
        }
    }

    //mesh->setFaceColors (  C );

    //_scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}

void BiharmonicNormalClusteringCommand::computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b )
{
    LabelData* labelData = _scene->labelData();

    if ( labelData->empty() ) return;

    std::vector<int> faceLabels;
    labelData->faceLabelData ( faceLabels );

    std::vector<double> faceLabelConfidents;
    labelData->faceLabelConfidentsData ( faceLabelConfidents );

    int numFaces =  _scene->mesh()->numFaces();

    int numConstraints = labelData->numLabels();

    b = Eigen::MatrixXd::Zero ( numFaces, numConstraints );

    MeshData* mesh = _scene->mesh()->openMeshData();

    MeshData::FaceIter f_it;
    MeshData::FaceFaceIter ff_it;

    A.resize ( numFaces, numFaces );

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        int faceLabel = faceLabels[fi];
        double w = faceLabelConfidents[fi];

        if ( faceLabel == LabelData::UNLABELED ) continue;

        A.insert ( fi, fi ) = w;
        b ( fi, faceLabel ) = w;
    }

    A.makeCompressed();
}