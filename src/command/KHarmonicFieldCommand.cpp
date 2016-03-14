
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
    mesh->faceLaplacian ( L, 1.0, 1.0,  0.5 );

    _M = L.transpose() * L;
}

void KHarmonicFieldCommand::doImp ()
{
    KHarmonicField harmonicField ( _M, _numCenters.value() );

    Eigen::VectorXi clusterIDs = harmonicField.clusterIDs();

    std::vector<int> faceLabels ( clusterIDs.size() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        faceLabels[fi] = clusterIDs ( fi );
    }

    _scene->labelData()->setFaceLabelData ( faceLabels );
}