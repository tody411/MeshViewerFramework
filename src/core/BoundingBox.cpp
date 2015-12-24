
/*!
  \file     BoundingBox.cpp
  \author       Tody
  BoundingBox definition.
  date      2015/12/15
*/

#include "BoundingBox.h"

#include <QtOpenGL>

void BoundingBox::expand ( const Eigen::Vector3f& p )
{
    for ( int i = 0; i < 3; i++ )
    {
        if ( _min ( i ) > p ( i ) )
        {
            _min ( i ) = p ( i );
        }

        if ( _max ( i ) < p ( i ) )
        {
            _max ( i ) = p ( i );
        }
    }
}

void BoundingBox::expand ( const MeshData& mesh )
{
    MeshData::VertexIter v_it, v_end ( mesh.vertices_end() );

    for ( v_it = mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p = mesh.point ( *v_it );
        expand ( Eigen::Vector3f ( p[0], p[1], p[2] ) );
    }
}

void BoundingBox::glFocus()
{

    float scale = 2.0 * sqrt ( 2.0 ) / size();

    glScalef ( scale, scale, scale );
    glTranslatef ( - center() ( 0 ), - center() ( 1 ), - center() ( 2 ) );
}