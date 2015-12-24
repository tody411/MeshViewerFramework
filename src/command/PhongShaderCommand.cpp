
/*!
  \file     PhongShaderCommand.cpp
  \author       Tody
  PhongShaderCommand definition.
  date      2015/12/24
*/

#include "PhongShaderCommand.h"


void PhongShaderCommand::doImp ()
{
    ShaderObject* shader = _scene->shader();

    shader->linkShaders ( "SimpleTransform.vert", "PhongShader.frag" );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::GLSL );
}