
/*!
  \file     ToonShaderCommand.cpp
  \author       Tody
  ToonShaderCommand definition.
  date      2015/12/19
*/

#include "ToonShaderCommand.h"

void ToonShaderCommand::setupImp()
{
    ShaderObject* shader = _scene->shader();

    shader->linkShaders ( "SimpleTransform.vert", "ToonShader.frag" );
    _scene->setMeshDisplayMode ( Mesh::DisplayMode::GLSL );
}

void ToonShaderCommand::doImp ()
{
    float border = _border.value();
    ShaderObject* shader = _scene->shader();
    shader->bind();
    shader->setUniformValue ( "border", border );
    shader->release();
}