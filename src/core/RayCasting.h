
/*!
  \file     RayCasting.h
  \author   Tody
  RayCasting definition.
  \date     2015/12/18
*/

#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <Eigen/Dense>

#include "MeshData.h"
#include "PointOnMesh.h"

//! RayCasting implementation.
class RayCasting
{
public :
    //! Constructor.
    RayCasting ( MeshData* mesh )
        : _mesh ( mesh )
    {}

    //! Destructor.
    virtual ~RayCasting() {}

    void setMeshData ( MeshData* mesh )
    {
        _mesh = mesh;
    }

    bool closestIntersection ( const Eigen::Vector3d& raySource, const  Eigen::Vector3d& rayDirection, PointOnFace& o_point );

private:
    //! OpenMesh data.
    MeshData*    _mesh;
};

#endif

