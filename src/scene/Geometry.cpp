
/*!
  \file     Geometry.cpp
  \author       Tody
  Geometry definition.
  date      2015/12/15
*/

#include "Geometry.h"
#include <QtOpenGL>

void Geometry::setMeshData ( MeshData& mesh )
{
    int numVertices = mesh.n_vertices();
    _points.resize ( 3 * numVertices );
    _normals.resize ( 3 * numVertices );

    for ( int i = 0; i < numVertices; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            _points[3 * i + j] = mesh.points() [i][j];
            _normals[3 * i + j] = mesh.vertex_normals() [i][j];
        }


    }

    int numFaces = mesh.n_faces();
    indices.resize ( 3 * numFaces );

    MeshData::ConstFaceIter    fIt ( mesh.faces_begin() ),
             fEnd ( mesh.faces_end() );
    MeshData::ConstFaceVertexIter fvIt;

    int triID = 0;

    for ( ; fIt != fEnd; ++fIt )
    {
        fvIt = mesh.cfv_iter ( fIt.handle() );
        indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        indices[triID] = fvIt->idx();
        ++triID;
    }
}

void Geometry::gl()
{
    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, &_points[0] );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, 0, &_normals[0] );

    glDrawElements ( GL_TRIANGLES,
                     indices.size(),
                     GL_UNSIGNED_INT,
                     &indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
}