
//! GreedyFloodingCommand definition.
/*!
  \file     GreedyFloodingCommand.cpp
  \author       Tody
  \date     2016/03/10
*/

#include "GreedyFloodingCommand.h"

#include "GreedyFlooding.h"

void GreedyFloodingCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    Eigen::VectorXi clusterIDs ( mesh->numFaces() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        clusterIDs[fi] = -1;
    }

    GreedyFlooding flooding ( mesh );
    flooding.setTolerance ( _tolerance.value() );

    flooding.flood ( clusterIDs );

    std::vector<int> faceLabels ( clusterIDs.size() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        faceLabels[fi] = clusterIDs ( fi );
    }

    _scene->labelData()->setFaceLabelData ( faceLabels );
}