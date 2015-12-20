
/*!
  \file     PointOnMesh.h
  \author   Tody
  PointOnMesh definition.
  \date     2015/12/18
*/

#ifndef POINTONMESH_H
#define POINTONMESH_H

#include <Eigen/Dense>

#include "MeshData.h"

//! PointOnMesh implementation.
class PointOnFace
{
public :
    //! Constructor.
    PointOnFace()
        : mesh ( nullptr )
    {}

    //! Destructor.
    virtual ~PointOnFace() {}

    bool isValid() const;

    const Eigen::Vector3f point() const;

    const Eigen::Vector3f normal() const;

    const Eigen::Vector2f uv() const;

    int index() const;

    void points ( Eigen::Matrix3f& V );

    const std::string str() const;

public:
    float w1;
    float w2;
    MeshData::FaceHandle fh;
    MeshData*    mesh;

};

#endif

