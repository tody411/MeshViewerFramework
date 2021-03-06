
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
        POINTS,
        GLSL
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

    //! Return the number of texture coordinates.
    unsigned int numUVs() const
    {
        return _UVs.rows();
    }

    bool hasUVs() const
    {
        return ! _UVs.size() == 0;
    }

    bool hasUVIDs() const
    {
        return ! _UVIDs.size() == 0;
    }

    //! Return the point matrix.
    void points ( Eigen::MatrixXd& V ) const;

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

    //! Return the face centers matrix.
    void faceCenters ( Eigen::MatrixXd& V );

    //! Set the UV matrix to this mesh.
    void setUVs ( const Eigen::MatrixXd& UVs )
    {
        _UVs = UVs;
        emit updated();
    }

    //! Return the texture coordinates.
    void UVs ( Eigen::MatrixXd& UVs ) const
    {
        UVs = _UVs;
    }

    //! Set the UV matrix to this mesh.
    void setUVIDs ( const Eigen::MatrixXi& UVIDs )
    {
        _UVIDs = UVIDs;
        emit updated();
    }

    //! Return the texture coordinates.
    void UVIDs ( Eigen::MatrixXi& UVIDs ) const
    {
        UVIDs = _UVIDs;
    }

    //! Return the vertex Laplacian matrix.
    void vertexLaplacian ( Eigen::SparseMatrix<double>& L );

    //! Return the face Laplacian matrix.
    void faceLaplacian ( Eigen::SparseMatrix<double>& L, double w_u = 0.0, double w_a = 1.0, double sigma_a = 0.5 );

    //! Return  the face Area vector.
    void Area_f ( Eigen::VectorXd& A );

    //! Return  the face Distance matrix.
    void W_ff ( Eigen::SparseMatrix<double>& W, double sigma = 0.5 );

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

    //! Return open mesh data.
    MeshData* openMeshData()
    {
        return &_mesh;
    }

    //-----------------------
    //  Connectivity.
    //=======================

    //! Return edge-face connection matrix.
    void Adj_ef ( Eigen::MatrixXi& A );

    //! Return face-vertex connection matrix.
    void Adj_fv ( Eigen::MatrixXi& A ) const;

    //! Return face-face connection matrix.
    void Adj_ff ( Eigen::SparseMatrix<double>& A  ) ;

    void isolatedFaces ( std::vector<int>& iso_faces );

    //-----------------------
    //  Bounding box.
    //=======================

    //! Return the bounding box.
    const BoundingBox boundingBox() const
    {
        return _bb;
    }

    void updateBoundingBox();

    void glFocus()
    {
        return _bb.glFocus();
    }

private:
    //! Compute triangle index list for OpenGL calls.
    void computeIndices();

    //-----------------------
    //  Clean up.
    //=======================
    void cleanIsolatedFaces ( MeshData& mesh );

private:
    //! OpenMesh data.
    MeshData    _mesh;

    //! Bounding box.
    BoundingBox _bb;

    //! Vertex color for OpenGL calls.
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> _C;

    //! Traianble index list for OpenGL calls.
    Eigen::Matrix<unsigned int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> _A_fv;

    //! UV coordinates.
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> _UVs;

    //! Face UV IDs.
    Eigen::MatrixXi _UVIDs;
};

#endif

