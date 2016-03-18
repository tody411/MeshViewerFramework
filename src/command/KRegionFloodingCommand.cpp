
//! KRegionFloodingCommand definition.
/*!
  \file     KRegionFloodingCommand.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "KRegionFloodingCommand.h"


#include "KRegionFlooding.h"

void KRegionFloodingCommand::setupImp()
{
    smoothing.setMesh ( _scene->mesh() );
}

void KRegionFloodingCommand::doImp ()
{
    KRegionFlooding regionFlooding ( _scene->mesh(), _numCenters.value() );

    Eigen::VectorXi clusterIDs;

    regionFlooding.flood ( clusterIDs );
    regionFlooding.flood ( clusterIDs );

    regionFlooding.setNorm ( _norm.value() );

    for ( int i = 0; i < _numIterations.value(); i++ )
    {
        regionFlooding.flood ( clusterIDs );
    }

    smoothing.setLambda ( _postFileter.value() );
    smoothing.smoothingClusters ( clusterIDs );

    _scene->labelData()->setFaceLabelData ( clusterIDs );
}