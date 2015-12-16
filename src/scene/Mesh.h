
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

    //! Return the number of vertices.
    unsigned int numVertices() const
    {
        return _mesh.n_vertices();
    }

    //! Return the number of edges.
    unsigned int numEdges() const
    {
        return _mesh.n_edges();
    }

    //! Return the number of faces.
    unsigned int numFaces() const
    {
        return _mesh.n_faces();
    }

    //! OpenGL calls for rendering.
    void gl();

    //! Return open mesh data.
    MeshData* openMeshData()
    {
        return &_mesh;
    }

private:
    //! Compute triangle index list for OpenGL calls.
    void computeIndices();

private:
    //! OpenMesh data.
    MeshData    _mesh;

    //! Traianble index list for OpenGL calls.
    std::vector<unsigned int> _indices;
};

#endif

