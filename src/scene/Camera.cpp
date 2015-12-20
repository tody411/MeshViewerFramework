
/*!
  \file     Camera.cpp
  \author       Tody
  Camera definition.
  date      2015/12/19
*/

#include "Camera.h"

#include <QtOpenGL>

void Camera::gl()
{
    glTranslatef ( _translation[0], _translation[1], _translation[2] );
    glScalef ( _scale[0], _scale[1], _scale[2] );
    glRotatef ( _rotation[0], 1.0f, 0.0f, 0.0f );
    glRotatef ( _rotation[1], 0.0f, 1.0f, 0.0f );
    glRotatef ( _rotation[2], 0.0f, 1.0f, 0.0f );
}