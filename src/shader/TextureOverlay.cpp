
/*!
  \file     TextureOverlay.cpp
  \author       Tody
  TextureOverlay definition.
  date      2016/03/01
*/

#include "TextureOverlay.h"

void glTextureViewport()
{
    glBegin ( GL_LINES );

    glColor4f ( 1.0, 0.2, 0.2, 0.2 );
    glVertex3f ( 0, 0, 0 );
    glVertex3f ( 1, 0, 0 );

    glVertex3f ( 1, 0, 0 );
    glVertex3f ( 1, 1, 0 );

    glVertex3f ( 1, 1, 0 );
    glVertex3f ( 0, 1, 0 );

    glVertex3f ( 0, 1, 0 );
    glVertex3f ( 0, 0, 0 );

    glEnd();

    glBegin ( GL_QUADS );
    glColor4f ( 0.8, 0.8, 1.0, 0.2 );
    glVertex3f ( 0, 0, 0 );
    glVertex3f ( 1, 0, 0 );
    glVertex3f ( 1, 1, 0 );
    glVertex3f ( 0, 1, 0 );

    glEnd();
}

void TextureOverlay::renderViewOverlayImp()
{

    double aspect = _scene->camera()->aspect();

    Eigen::Vector3f center ( - aspect * 0.98, - 0.2, 0.0 );

    glTranslatef ( center[0], center[1], center[2] );
    glScalef ( 0.7f, 0.7f, 0.0f );

    glDisable ( GL_LIGHTING );

    glTextureViewport();

    if ( !_scene->mesh()->hasUVs() ) return;

    Eigen::MatrixXd UVs;
    _scene->mesh()->UVs ( UVs );

    Eigen::MatrixXi UVIDs;

    if ( _scene->mesh()->hasUVIDs() )
    {
        _scene->mesh()->UVIDs ( UVIDs );
    }

    else
    {
        _scene->mesh()->Adj_fv ( UVIDs );
    }

    glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
    glColor4f ( 1.0, 0.7, 0.2, 0.3 );

    glBegin ( GL_TRIANGLES );

    for ( int uvi = 0; uvi < UVIDs.rows(); uvi++ )
    {
        for ( int ci = 0; ci < 3; ci++ )
        {
            int uvID = UVIDs ( uvi, ci );

            Eigen::Vector2d uv = UVs.row ( uvID );

            glVertex3f ( uv ( 0 ), uv ( 1 ), 0 );
        }
    }

    glEnd();

    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
}