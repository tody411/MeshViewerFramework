
/*!
  \file     MeshColorSet.cpp
  \author       Tody
  MeshColorSet definition.
  date      2015/12/17
*/

#include "MeshColorSet.h"


void MeshColorSet::setColorSet ( const QString& colorSetName )
{
    MeshData::VertexIter v_it, v_end ( _mesh->vertices_end() );

    for ( v_it = _mesh->vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Color vColor = _mesh->property ( _vpColor, *v_it );
        _mesh->set_color ( *v_it, vColor );

    }
}