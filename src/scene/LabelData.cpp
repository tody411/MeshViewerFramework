
/*!
  \file     LabelData.cpp
  \author       Tody
  LabelData definition.
  date      2016/02/26
*/

#include "LabelData.h"

#include "Scene.h"
#include "BoundingBox.h"
#include "ColorMap.h"

bool LabelData::empty() const
{
    bool isEmpty = true;

    for ( int i = 0; i < _faceLabels.size(); i++ )
    {
        if ( _faceLabels[i] > UNLABELED ) isEmpty = false;
    }
    return isEmpty;
}

void LabelData::clear()
{
    for ( int i = 0; i < _faceLabels.size(); i++ )
    {
        _faceLabels[i] = UNLABELED;
        _faceLabelConfidents[i] = 0.0;
    }
}

void LabelData::resize ( int size )
{
    _faceLabels.resize ( size );
    _faceLabelConfidents.resize ( size );
    clear();
}

int LabelData::numLabels()
{
    int labelMax = UNLABELED;
    for ( int i = 0; i < _faceLabels.size(); i++ )
    {
        labelMax = std::max ( labelMax, _faceLabels[i] );
    }
    return labelMax + 1;
}

void LabelData::setFaceLabelData ( const std::vector<int>& faceLabels )
{
    for ( int i = 0; i < faceLabels.size(); i++ )
    {
        _faceLabels[i] = faceLabels[i];
    }
}

void LabelData::setFaceLabelData ( const std::vector<int>& indices, int label )
{
    for each ( int index in indices )
    {
        _faceLabels[index] = label;
    }
}

void LabelData::setFaceLabelConfidents ( const std::vector<int>& indices, double w )
{
    for each ( int index in indices )
    {
        _faceLabelConfidents[index] = w;
    }
}


int LabelData::getFaceLabel ( int index )
{
    return _faceLabels[index];
}

void LabelData::faceLabelData ( std::vector<int>& faceLabels ) const
{
    std::copy ( _faceLabels.begin(), _faceLabels.end(), std::back_inserter ( faceLabels ) );
}

void LabelData::faceLabelConfidentsData ( std::vector<double>& faceLabelConfidents ) const
{
    std::copy ( _faceLabelConfidents.begin(), _faceLabelConfidents.end(), std::back_inserter ( faceLabelConfidents ) );
}


void LabelData::gl()
{
    if ( _faceLabels.empty() ) return;

    MeshData* mesh = _scene->mesh()->openMeshData();

    BoundingBox bb =  _scene->boundingBox();

    float bb_size = bb.size();

    MeshData::FaceVertexIter fvIt;
    MeshData::FaceHandle fh;

    float epsilon = 1e-5;

    Eigen::MatrixXd C;
    ColorMap::generateIDColors ( 10, C );

    glDisable ( GL_LIGHTING );
    glEnable ( GL_DEPTH_TEST );
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

    glBegin ( GL_TRIANGLES );

    for ( int fi = 0; fi < _faceLabels.size(); fi++ )
    {
        int label = _faceLabels[fi];

        if ( label == -1 ) continue;

        fh = mesh->face_handle ( fi );
        fvIt = mesh->fv_iter ( fh );

        double w = _faceLabelConfidents[fi];

        glColor4f ( C ( label, 0 ), C ( label, 1 ), C ( label, 2 ), 0.5f + 0.3f * w );

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