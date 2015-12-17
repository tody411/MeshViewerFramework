
/*!
  \file     Material.cpp
  \author       Tody
  Material definition.
  date      2015/12/17
*/

#include "Material.h"

#include <QtOpenGL>

void Material::gl()
{
    glShadeModel ( GL_SMOOTH );

    glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, ambient.data() );
    glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.data() );
    glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, specular.data() );
    glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, &shininess );
}