
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
#include "BoundingBox.h"
#include "SceneObject.h"

//! Mesh implementation.
class Mesh : public SceneObject
{
    Q_OBJECT
public :
    //! Display mode for the mesh.
    enum DisplayMode
    {
        SHADING,
        VERTEX_COLOR,
        FACE_COLOR,
        WIREFRAME,
        POINTS
    };

    //! Constructor.
    Mesh ( Scene* scene )
        : SceneObject ( scene )
    {}

    //! Destructor.
    virtual ~Mesh() {}

    bool empty() const
    {
        return _mesh.vertices_empty();
    }

    //! Load mesh data from the file path.
    bool loadMesh ( const QString& filePath );

    //! Save mesh data to the given file path.
    bool saveMesh ( const QString& filePath );

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

    //! Return the face point matrix.
    void facePoints ( Eigen::MatrixXd& V );

    //! Return the normal matrix.
    void vertexNormals ( Eigen::MatrixXd& N );

    //! Set the normal matrix to the vertices of this mesh.
    void setVertexNormals ( const Eigen::MatrixXd& N );

    //! Return the color matrix.
    void vertexColors ( Eigen::MatrixXd& C );

    //! Set the color matrix to the vertices of this mesh.
    void setVertexColors ( const Eigen::MatrixXd& C );

    //! Return the face colors.
    void faceColors ( Eigen::MatrixXd& C );

    //! Set the color matrix to the vertices of this mesh.
    void setFaceColors ( const Eigen::MatrixXd& C );

    //! Return the face normal matrix.
    void faceNormals ( Eigen::MatrixXd& N );

    //! Return the vertex Laplacian matrix.
    void vertexLaplacian ( Eigen::SparseMatrix<double>& L );

    //! OpenGL calls for rendering.
    void gl ( DisplayMode displayMode = SHADING );

    //! OpenGL calls for shading.
    void glShadingMode ( );

    //! OpenGL calls for coloring.
    void glVertexColorMode ( );

    //! OpenGL calls for coloring.
    void glFaceColorMode ( );

    //! OpenGK calls for points.
    void glPoints ( );

    //! OpenGL calls for wireframe.
    void glWireframeMode ( );

    //! OpenGL calls for

    //! Return open mesh data.
    MeshData* openMeshData()
    {
        return &_mesh;
    }

    //! Return the bounding box.
    const BoundingBox boundingBox() const
    {
        return _bb;
    }

    void updateBoundingBox();

    void focusGL()
    {
        return _bb.focusGL();
    }

private:
    //! Compute triangle index list for OpenGL calls.
    void computeIndices();

private:
    //! OpenMesh data.
    MeshData    _mesh;

    //! Bounding box.
    BoundingBox _bb;

    //! Traianble index list for OpenGL calls.
    std::vector<unsigned int> _indices;

    //! Vertex color for OpenGL calls.
    Eigen::MatrixXf _C;
};

#endif

