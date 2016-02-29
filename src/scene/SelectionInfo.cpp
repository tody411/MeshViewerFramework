
/*!
  \file     SelectionInfo.cpp
  \author       Tody
  SelectionInfo definition.
  date      2015/12/19
*/

#include "SelectionInfo.h"

#include "Scene.h"
#include "BoundingBox.h"
#include "Mesh.h"
#include "MeshData.h"

#include <QtOpenGL>

#include <iostream>

bool IndexSelection::empty() const
{
    return _selection.empty();
}

void IndexSelection::clear()
{
    _selection.clear();
}

void IndexSelection::setIndexList ( const std::vector<int>& indices )
{
    std::copy ( indices.begin(), indices.end(), std::back_inserter ( _selection ) );
}

void IndexSelection::addIndex ( int index )
{
    _selection.push_back ( index );
}

void IndexSelection::indexList ( std::vector<int>& indices ) const
{
    std::copy ( _selection.begin(), _selection.end(), std::back_inserter ( indices ) );
}

void SelectionInfo::gl()
{
    glVertexSelection();
    glFaceSelection();
}

void SelectionInfo::glVertexSelection()
{
    if ( _vertexSelection.empty() ) return;

    MeshData* mesh = _scene->mesh()->openMeshData();
    BoundingBox bb =  _scene->mesh()->boundingBox();
    float bb_size = bb.size();

    glDisable ( GL_LIGHTING );
    glEnable ( GL_DEPTH_TEST );

    glColor4f ( 1.0f, 0.2f, 0.1f, 0.5f );

    glBegin ( GL_POINTS );

    float epsilon = 1e-3;

    std::vector<int> indices;
    vertexSelection ( indices );

    for ( int vi = 0; vi < indices.size(); vi++ )
    {
        int vID = indices[vi];
        MeshData::VertexHandle vh = mesh->vertex_handle ( vID );
        OpenMesh::Vec3f v = mesh->point ( vh );

        OpenMesh::Vec3f n = mesh->normal ( vh );

        v += epsilon * bb_size * n;

        glVertex3fv ( v.data() );
    }

    glEnd();
}

void SelectionInfo::glFaceSelection()
{
    if ( _faceSelection.empty() ) return;

    MeshData* mesh = _scene->mesh()->openMeshData();

    BoundingBox bb =  _scene->boundingBox();

    float bb_size = bb.size();

    MeshData::FaceVertexIter fvIt;
    MeshData::FaceHandle fh;

    float epsilon = 1e-4;

    std::vector<int> indices;
    faceSelection ( indices );

    glDisable ( GL_LIGHTING );
    glEnable ( GL_DEPTH_TEST );
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    glColor4f ( 1.0f, 0.2f, 0.1f, 0.5f );

    glBegin ( GL_TRIANGLES );

    for ( int fi = 0; fi < indices.size(); fi++ )
    {
        int fID = indices[fi];

        fh = mesh->face_handle ( fID );
        fvIt = mesh->fv_iter ( fh );

        for ( int vi = 0; vi < 3; vi++ )
        {
            OpenMesh::Vec3f v = mesh->point ( *fvIt );
            OpenMesh::Vec3f n = mesh->normal ( *fvIt );

            v += ( epsilon * bb_size ) * n;

            glVertex3fv ( v.data() );
            ++fvIt;
        }
    }

    glEnd();
}


void SelectionInfoSet::gl()
{
    foreach ( SelectionInfo* selectionInfo,  _selectionSet )
    {
        selectionInfo->gl();
    }
}