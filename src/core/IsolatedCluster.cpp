
/*!
  \file     IsolatedCluster.cpp
  \author       Tody
  IsolatedCluster definition.
  date      2016/03/07
*/

#include "IsolatedCluster.h"

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#include "ListUtil.h"

void cleanClusterIDs ( Eigen::VectorXi& clusterIDs )
{
    std::set<int> labelSet;

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        labelSet.insert ( clusterIDs ( fi ) );
    }

    std::vector<int> labelVector ( labelSet.begin(), labelSet.end() );
    std::map<int, int> labelMap;

    for ( int li = 0; li < labelVector.size(); li++ )
    {
        labelMap[labelVector[li]] = li;
    }

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        int label = clusterIDs ( fi );
        int labelNew = labelMap[label];

        clusterIDs ( fi ) = labelNew;
    }
}

void IsolatedCluster::compute ( Eigen::VectorXi& clusterIDs )
{
    std::vector <bool> visited ( clusterIDs.size() );

    ListUtil::fill ( visited, false );

    MeshData::FaceIter f_it, f_end ( _mesh->faces_end() );
    MeshData::FaceFaceIter ff_it;

    int numClusters = clusterIDs.maxCoeff() + 1;

    int numClustersNew = numClusters;

    for ( int label = 0; label < numClusters; label++ )
    {
        int label_new = label;

        bool hasSeed = true;
        while ( hasSeed )
        {
            int seedFaceID = -1;
            for ( f_it = _mesh->faces_begin(); f_it != f_end; ++f_it )
            {
                int label_f = clusterIDs ( f_it->idx() );

                if ( label == label_f && visited[f_it->idx() ] == false )
                {
                    seedFaceID = f_it->idx();
                    visited[seedFaceID] = true;
                    clusterIDs ( seedFaceID ) = label_new;
                    break;
                }
            }

            if ( f_it == f_end ) break;
            if ( seedFaceID == -1 ) break;

            std::cout << "SeedFace:" << seedFaceID << ", " << label << ", " << label_new << std::endl;

            std::queue < int > faceIDQueue;
            faceIDQueue.push ( seedFaceID );

            while ( !faceIDQueue.empty() )
            {
                int faceID = faceIDQueue.front();
                faceIDQueue.pop();

                for ( ff_it = _mesh->ff_begin ( MeshData::FaceHandle ( faceID ) ); ff_it.is_valid(); ++ff_it )
                {
                    int label_f = clusterIDs ( ff_it->idx() );

                    if ( label == label_f && visited[ff_it->idx() ] == false )
                    {
                        faceIDQueue.push ( ff_it->idx() );
                        visited[ff_it->idx() ] = true;
                        clusterIDs ( ff_it->idx()  ) = label_new;
                    }
                }
            }

            label_new = numClustersNew;
            numClustersNew++;
        }
    }

    cleanClusterIDs ( clusterIDs );
}