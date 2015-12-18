
/*!
  \file     PointsOverlay.cpp
  \author       Tody
  PointsOverlay definition.
  date      2015/12/17
*/

#include "PointsOverlay.h"

#include <QtOpenGL>

void PointsOverlay::renderSceneOverlayImp()
{
    Mesh* mesh = _scene->mesh();
    glDisable ( GL_LIGHTING );
    glColor3f ( 1.0f, 1.0f, 0.0f );
    mesh->gl ( Mesh::DisplayMode::POINTS );
}