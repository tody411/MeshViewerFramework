
/*!
  \file     MeshMatrix.h
  \author   Tody
  MeshMatrix definition.
  \date     2015/12/21
*/

#ifndef MESHMATRIX_H
#define MESHMATRIX_H

#include "MeshData.h"

#include <Eigen/Dense>
#include <Eigen/Sparse>

//! MeshMatrix implementation.
class MeshMatrix
{
public :
    //! Constructor.
    MeshMatrix ( MeshData& mesh )
        : _mesh ( mesh )
    {}

    //! Destructor.
    virtual ~MeshMatrix() {}

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

    //! Return the vertex Laplacian matrix.
    void L_vv ( Eigen::SparseMatrix<double>& L );

    //! Return the face Laplacian matrix.
    void L_ff ( Eigen::SparseMatrix<double>& L, double w_u = 0.0, double w_a = 1.0, double sigma_a = 0.5 );

    //! Return  the face Distance matrix.
    void W_ff ( Eigen::SparseMatrix<double>& W, double sigma = 0.5 );

    //! Return  the face Area vector.
    void Area_f ( Eigen::VectorXd& A );

private:
    //! OpenMesh data.
    MeshData&    _mesh;


};

#endif

