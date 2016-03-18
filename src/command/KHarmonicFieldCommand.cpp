
//! KHarmonicFieldCommand definition.
/*!
  \file     KHarmonicFieldCommand.cpp
  \author       Tody
  \date     2016/03/14
*/

#include "KHarmonicFieldCommand.h"

#include "KHarmonicField.h"

void KHarmonicFieldCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();

    Eigen::SparseMatrix<double> L;
    mesh->faceLaplacian ( L, 0.0001, 1.0,  0.3 );

    _M = L.transpose() * L;
}

void KHarmonicFieldCommand::doImp ()
{
    KHarmonicField harmonicField ( _M, _numCenters.value() );

    Eigen::VectorXi clusterIDs = harmonicField.clusterIDs();

    _scene->labelData()->setFaceLabelData ( clusterIDs );
}