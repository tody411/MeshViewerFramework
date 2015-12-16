
/*!
  \file     Mesh.h
  \author   Tody
  Mesh definition.
  \date     2015/12/16
*/

#ifndef MESH_H
#define MESH_H

#include <QString>

#include "MeshData.h"

//! Mesh implementation.
class Mesh
{
public :
    //! Constructor.
    Mesh() {}

    //! Destructor.
    virtual ~Mesh() {}

    //! Load mesh data from the file path.
    bool loadMesh ( const QString& filePath );


    unsigned int numVertices() const
    {
        return _mesh.n_vertices();
    }

    unsigned int numEdges() const
    {
        return _mesh.n_edges();
    }

    unsigned int numFaces() const
    {
        return _mesh.n_faces;
    }

    void gl();

    MeshData* openMeshData()
    {
        return &_mesh;
    }

private:
    void computeIndices();

private:
    //! OpenMesh data.
    MeshData    _mesh;

    std::vector<unsigned int> _indices;
};

#endif

