
/*!
  \file     FindExtremePoiintsCommand.cpp
  \author       Tody
  FindExtremePoiintsCommand definition.
  date      2015/12/22
*/

#include "FindExtremePoiintsCommand.h"

#include <iostream>

#include "EigenUtil.h"

void FindExtremePoiintsCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 1.0, 0.0 );
    _M = L.transpose() * L;
}

void FindExtremePoiintsCommand::doImp ()
{
    double lambda = 100.0;

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity (  _M.rows(),  _M.cols() ).sparseView();
    Eigen::SparseMatrix<double> A_cons;
    Eigen::MatrixXd b_cons;

    computeWeightConstraint ( A_cons, b_cons );
    double w_cons = lambda * 10.0;
    double w_R = 0.001;

    Eigen::SparseMatrix<double> A = w_cons * A_cons + lambda *  _M + w_R * I;
    Eigen::MatrixXd b = ( w_cons + w_R ) * b_cons;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        return;
    }

    Eigen::MatrixXd W = solver.solve ( b );

    std::cout <<  EigenUtil::info ( W, "W" );
    /* Mesh* mesh = _scene->mesh();
     mesh->setFaceColors (  C );*/

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::FACE_COLOR );
}

void FindExtremePoiintsCommand::computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b )
{
    std::vector<int> faceIDs;

    _scene->selectionInfo()->faceSelection ( faceIDs );

    if ( faceIDs.empty() )
    {
        return;
    }

    int numFaces =  _scene->mesh()->numFaces();
    int numConstraints = 1;

    b = Eigen::MatrixXd::Zero ( numFaces, numConstraints );

    MeshData* mesh = _scene->mesh()->openMeshData();

    MeshData::FaceIter f_it;
    MeshData::FaceFaceIter ff_it;

    A.resize ( numFaces, numFaces );

    for ( int ci = 0; ci < numConstraints; ci++ )
    {
        int fID = faceIDs[ci];
        A.insert ( fID, fID ) = 1.0;
        b ( fID, ci ) = 0.0;

        for ( ff_it = mesh->ff_begin ( mesh->face_handle ( fID ) ); ff_it.is_valid(); ++ff_it )
        {
            int ffID = ff_it->idx();

            A.insert ( ffID, ffID ) = 1.0;
            b ( ffID, ci ) = 1.0;
        }
    }

    A.makeCompressed();


}