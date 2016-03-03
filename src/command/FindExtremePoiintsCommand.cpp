
/*!
  \file     FindExtremePoiintsCommand.cpp
  \author       Tody
  FindExtremePoiintsCommand definition.
  date      2015/12/22
*/

#include "FindExtremePoiintsCommand.h"

#include <iostream>

#include "ColorMap.h"
#include "EigenUtil.h"

void FindExtremePoiintsCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 1.0, 0.2, 0.5 );
    _M = L.transpose() * L;
    //_M = _M.transpose() * _M;
}

void FindExtremePoiintsCommand::doImp ()
{
    double lambda = 1000.0;
    double w_r = 0.000001;

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::VectorXd b_cons;

    computeWeightConstraint ( A_cons, b_cons );

    Eigen::SparseMatrix<double> A = A_cons + lambda *  _M + w_r * I;
    Eigen::VectorXd b =  b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        std::cout <<  "Solver Fail" << std::endl;
        return;
    }

    Eigen::VectorXd W = solver.solve ( b );

    std::vector<int> iso_faces;
    Mesh* mesh = _scene->mesh();
    mesh->isolatedFaces ( iso_faces );

    double w_min = W.minCoeff();

    for ( int i = 0; i < iso_faces.size(); i++ )
    {
        W ( iso_faces[i] ) = w_min;
    }

    std::cout <<  EigenUtil::info ( W, "W" );

    Eigen::MatrixXd C;
    ColorMap::heatMap ( W, C );

    mesh->setFaceColors ( C );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}

void FindExtremePoiintsCommand::computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::VectorXd& b )
{
    std::vector<int> faceIDs;

    _scene->selectionInfo()->faceSelection ( faceIDs );

    if ( faceIDs.empty() )
    {
        faceIDs.push_back ( 0 );
    }

    int numFaces =  _scene->mesh()->numFaces();

    b = Eigen::VectorXd::Zero (  faceIDs.size() );

    MeshData* mesh = _scene->mesh()->openMeshData();

    MeshData::FaceIter f_it;
    MeshData::FaceFaceIter ff_it;

    Eigen::SparseMatrix<double> L ( faceIDs.size(), numFaces );

    double w_cons = 10.0;

    for ( int si = 0; si < faceIDs.size(); si++ )
    {
        int seed_face = faceIDs[si];

        int ff_faces = 0;

        for ( ff_it = mesh->ff_begin ( mesh->face_handle ( seed_face ) ); ff_it.is_valid(); ++ff_it )
        {
            int ffi = ff_it->idx();

            L.insert ( si, ffi ) = -1.0;
            ff_faces += 1;
        }

        L.insert ( si, seed_face ) = ff_faces;
        b ( si ) = -ff_faces;
    }

    L.makeCompressed();

    b = L.transpose() * b;
    A = L.transpose() * L;

    Eigen::SparseMatrix<double> A_cons ( faceIDs.size(), numFaces );
    for ( int si = 0; si < faceIDs.size(); si++ )
    {
        int seed_face = faceIDs[si];
        A_cons.insert ( si, seed_face ) = w_cons;
    }

    A = A + A_cons.transpose() * A_cons;
}