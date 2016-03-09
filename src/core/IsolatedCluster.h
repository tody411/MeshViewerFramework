
/*!
  \file     IsolatedCluster.h
  \author   Tody
  IsolatedCluster definition.
  \date     2016/03/07
*/

#ifndef ISOLATEDCLUSTER_H
#define ISOLATEDCLUSTER_H

#include "Eigen/Dense"

#include "MeshData.h"

//! IsolatedCluster implementation.
class IsolatedCluster
{
public :
    //! Constructor.
    IsolatedCluster ( MeshData* mesh )
        : _mesh ( mesh )
    {
    }

    //! Destructor.
    virtual ~IsolatedCluster() {}

    void compute ( Eigen::VectorXi& clusterIDs );

private:
    MeshData*    _mesh;
};

#endif

