
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
}

void Mesh::gl()
{
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
        fvIt = _mesh.cfv_iter ( fIt.handle() );
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