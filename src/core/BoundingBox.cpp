
/*!
  \file     BoundingBox.cpp
  \author       Tody
  BoundingBox definition.
  date      2015/12/15
*/

#include "BoundingBox.h"


void BoundingBox::addPoint ( const Eigen::Vector3f& p )
{
    for ( int i = 0; i < 3; i++ )
    {
        if ( _pMin ( i ) > p ( i ) )
        {
            _pMin ( i ) = p ( i );
        }

        if ( _pMax ( i ) < p ( i ) )
        {
            _pMax ( i ) = p ( i );
        }
    }
}

void BoundingBox::addMesh ( const MeshData& mesh )
{
    MeshData::VertexIter v_it, v_end ( mesh.vertices_end() );

    for ( v_it = mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p = mesh.point ( *v_it );
        addPoint ( Eigen::Vector3f ( p[0], p[1], p[2] ) );
    }
}