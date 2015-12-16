
/*!
  \file     Geometry.h
  \author   Tody
  Geometry definition.
  \date     2015/12/15
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "MeshData.h"

//! Geometry implementation.
class Geometry
{
public :
    //! Constructor.
    Geometry() {}

    //! Destructor.
    virtual ~Geometry() {}

    void setMeshData ( MeshData& mesh );

    void gl();

private:
    std::vector<float> _points;
    std::vector<float> _normals;

    std::vector<unsigned int> indices;
};

#endif

