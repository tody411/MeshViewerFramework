
/*!
  \file     WireframeOverlay.cpp
  \author       Tody
  WireframeOverlay definition.
  date      2015/12/17
*/

#include "WireframeOverlay.h"

#include <QtOpenGL>

#include "Mesh.h"


void WireframeOverlay::renderSceneOverlayImp()
{
    Mesh* mesh = _scene->mesh();
    glDisable ( GL_LIGHTING );
    glEnable ( GL_DEPTH_TEST );
    glColor3f ( 0.25f, 1.0f, 0.65f );
    mesh->gl ( Mesh::DisplayMode::WIREFRAME );
}
