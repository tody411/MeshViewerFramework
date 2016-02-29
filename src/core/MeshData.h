
/*!
  \file     MeshData.h
  \author   Tody
  MeshData definition.
  \date     2014/11/17
*/

#ifndef MESHDATA_H
#define MESHDATA_H

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

struct MeshTraits : public OpenMesh::DefaultTraits
{
    VertexAttributes ( OpenMesh::Attributes::Status );
    FaceAttributes ( OpenMesh::Attributes::Status );
    EdgeAttributes ( OpenMesh::Attributes::Status );
};

typedef OpenMesh::PolyMesh_ArrayKernelT<MeshTraits>  MeshData;

#endif

