
/*!
  \file     Light.cpp
  \author       Tody
  Light definition.
  date      2015/12/15
*/

#include "Light.h"

#include <QtOpenGL>

void Light::gl()
{
    glEnable ( GL_LIGHT0 + lightNo );
    glLightfv ( GL_LIGHT0 + lightNo, GL_AMBIENT, ambient.data() );
    glLightfv ( GL_LIGHT0 + lightNo, GL_DIFFUSE, diffuse.data() );
    glLightfv ( GL_LIGHT0 + lightNo, GL_SPECULAR, specular.data() );
    glLightfv ( GL_LIGHT0 + lightNo, GL_POSITION, lightPosition.data() );
}
