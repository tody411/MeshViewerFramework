
/*!
  \file     Mesh.cpp
  \author       Tody
  Mesh definition.
  date      2015/12/16
*/

#include "Mesh.h"

#include <QtOpenGL>

#include <OpenMesh/Core/IO/MeshIO.hh>

bool Mesh::loadMesh ( const QString& filePath )
{
    _mesh.request_face_normals();
    _mesh.request_face_colors();
    _mesh.request_vertex_normals();
    _mesh.request_vertex_texcoords2D();

    std::string file = filePath.toStdString();

    if ( !OpenMesh::IO::read_mesh ( _mesh, file ) )
    {
        std::cerr << "read error" << std::endl;
        return false;
    }

    _mesh.triangulate();

    _mesh.update_normals();

    computeIndices();
    return true;
}

bool Mesh::saveMesh ( const QString& filePath )
{
    std::string file = filePath.toStdString();
    if ( !OpenMesh::IO::write_mesh ( _mesh, file ) )
    {
        std::cerr << "write error" << std::endl;
        return false;
    }
    return true;
}


void Mesh::points ( Eigen::MatrixXd& V )
{
    V.resize ( numVertices(), 3 );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p = _mesh.point ( *v_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            V ( v_it->idx(), ci ) = p[ci];
        }

    }
}

void Mesh::setPoints ( const Eigen::MatrixXd& V )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p;
        for ( int ci = 0; ci < 3; ci++ )
        {
            p[ci] = V ( v_it->idx(), ci );
        }

        _mesh.point ( *v_it ) = p;
    }
}

void Mesh::vertexNormals ( Eigen::MatrixXd& N )
{
    N .resize ( numVertices(), 3 );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Normal n = _mesh.normal ( *v_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            N ( v_it->idx(), ci ) = n[ci];
        }

    }
}

void Mesh::setVertexNormals ( const Eigen::MatrixXd& N )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Normal n;
        for ( int ci = 0; ci < 3; ci++ )
        {
            n[ci] = N ( v_it->idx(), ci );
        }

        _mesh.point ( *v_it ) = n;
    }
}

void Mesh::faceNormals ( Eigen::MatrixXd& N )
{
    N .resize ( numFaces(), 3 );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        MeshData::Normal n = _mesh.normal ( *f_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            N ( f_it->idx(), ci ) = n[ci];
        }

    }
}

void Mesh::gl()
{
    if ( _mesh.vertices_empty() ) return;

    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, _mesh.points() );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, 0, _mesh.vertex_normals() );

    glDrawElements ( GL_TRIANGLES,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     &_indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
}

void Mesh::computeIndices()
{
    int numFaces = _mesh.n_faces();
    _indices.resize ( 3 * numFaces );

    MeshData::ConstFaceIter    fIt ( _mesh.faces_begin() ),
             fEnd ( _mesh.faces_end() );
    MeshData::ConstFaceVertexIter fvIt;

    int triID = 0;

    for ( ; fIt != fEnd; ++fIt )
    {
        fvIt = _mesh.cfv_iter ( *fIt );
        _indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        _indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        _indices[triID] = fvIt->idx();
        ++triID;
    }
}