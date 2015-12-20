
/*!
  \file     NormalShaderCommand.cpp
  \author       Tody
  NormalShaderCommand definition.
  date      2015/12/20
*/

#include "NormalShaderCommand.h"


void NormalShaderCommand::doImp ()
{
    ShaderObject* shader = _scene->shader();

    shader->linkShaders ( "SimpleTransform.vert", "NormalShader.frag" );

    _scene->setMeshDisplayMode ( Mesh::DisplayMode::GLSL );
}