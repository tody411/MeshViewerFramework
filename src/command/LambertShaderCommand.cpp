
//! LambertShaderCommand definition.
/*!
  \file     LambertShaderCommand.cpp
  \author       Tody
  \date     2015/12/22
*/

#include "LambertShaderCommand.h"


void LambertShaderCommand::doImp ()
{
    ShaderObject* shader = _scene->shader();

    shader->linkShaders ( "SimpleTransform.vert", "LambertShader.frag" );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::GLSL );
}