
/*!
  \file     Mesh.h
  \author   Tody
  Mesh definition.
  \date     2015/12/16
*/

#ifndef MESH_H
#define MESH_H

#include <QString>

#include <Eigen/Dense>
#include <Eigen/Sparse>

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

    //! Return the point matrix.
    void points ( Eigen::MatrixXd& V );

    //! Set the point matrix to the vertices of this mesh.
    void setPoints ( const Eigen::MatrixXd& V );

    //! Return the normal matrix.
    void vertexNormals ( Eigen::MatrixXd& N );

    //! Set the normal matrix to the vertices of this mesh.
    void setVertexNormals ( const Eigen::MatrixXd& N );

    //! Return the face normal matrix.
    void faceNormals ( Eigen::MatrixXd& N );

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

