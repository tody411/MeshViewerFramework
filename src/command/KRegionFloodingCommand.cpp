
//! KRegionFloodingCommand definition.
/*!
  \file     KRegionFloodingCommand.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "KRegionFloodingCommand.h"

#include "KRegionFlooding.h"
#include "Random.h"

void KRegionFloodingCommand::setupImp()
{
    smoothing.setMesh ( _scene->mesh() );

    _scene->mesh()->faceNormals ( _N_f );

    smoothing.setLambda ( 1.0 );
    smoothing.setConstraints ( _N_f );
    _N_f = smoothing.smoothing();
}

void KRegionFloodingCommand::doImp ()
{

    if ( !_scene->selectionInfo()->emptyFace() && !_scene->labelData()->empty() )
    {
        doSelection();
    }
    else
    {
        doAll();
    }
}

void KRegionFloodingCommand::doSelection()
{
    std::vector<int> selection;
    _scene->selectionInfo()->faceSelection ( selection );

    int selectedFace = selection[0];

    LabelData* labelData = _scene->labelData();

    Eigen::VectorXi clusterIDs;

    labelData->faceLabelData ( clusterIDs );

    int selectedLabel = clusterIDs[selectedFace];

    std::vector<int> shellFaces;

    labelData->labelShell ( selectedLabel, shellFaces );

    KRegionFlooding regionFlooding ( _scene->mesh(), _numCenters.value() );
    regionFlooding.setFaceNormals ( _N_f );
    regionFlooding.setTargetFaces ( shellFaces );

    if ( !shellFaces.empty() )
    {
        Eigen::VectorXi shellRandIDs;

        Random::randint (  _numCenters.value() - 1, shellRandIDs, 0, shellFaces.size() - 1 );

        int clusterID = clusterIDs.maxCoeff() + 1;
        for ( int i = 0; i < shellRandIDs.size(); i++ )
        {
            int fi = shellFaces[shellRandIDs[i]];
            clusterIDs[fi] = clusterID;
            clusterID ++;
        }
    }

    regionFlooding.setNorm ( _norm.value() );

    for ( int i = 0; i < _numIterations.value(); i++ )
    {
        regionFlooding.flood ( clusterIDs );
    }

    Eigen::VectorXi smoothedClusterIDs = clusterIDs;

    smoothing.setLambda ( _postFileter.value() );
    smoothing.smoothingClusters ( smoothedClusterIDs );

    for ( int i = 0; i < shellFaces.size(); i++ )
    {
        int fi = shellFaces[i];
        clusterIDs[fi] = smoothedClusterIDs[fi];
    }

    _scene->labelData()->setFaceLabelData ( clusterIDs );
}

void KRegionFloodingCommand::doAll()
{
    KRegionFlooding regionFlooding ( _scene->mesh(), _numCenters.value() );
    regionFlooding.setFaceNormals ( _N_f );

    Eigen::VectorXi clusterIDs;

    regionFlooding.setNorm ( _norm.value() );

    for ( int i = 0; i < _numIterations.value(); i++ )
    {
        regionFlooding.flood ( clusterIDs );
    }

    smoothing.setLambda ( _postFileter.value() );
    smoothing.smoothingClusters ( clusterIDs );

    _scene->labelData()->setFaceLabelData ( clusterIDs );
}