
/*!
  \file     MeshColorSet.h
  \author   Tody
  MeshColorSet definition.
  \date     2015/12/17
*/

#ifndef MESHCOLORSET_H
#define MESHCOLORSET_H

#include <Eigen/Dense>

#include <QString.h>

#include "MeshData.h"

//! MeshColorSet implementation.
class MeshColorSet
{
public :
    //! Constructor.
    MeshColorSet() {}

    //! Destructor.
    virtual ~MeshColorSet() {}

    void setMeshData ( MeshData* mesh )
    {
        _mesh = mesh;
    }

    void setColorSet ( const QString& colorSetName );

private:
    //! OpenMesh data.
    MeshData*    _mesh;

    OpenMesh::VPropHandleT<MeshData::Color> _vpColor;

};

#endif

