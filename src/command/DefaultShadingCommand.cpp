
/*!
  \file     DefaultShadingCommand.cpp
  \author       Tody
  DefaultShadingCommand definition.
  date      2015/12/19
*/

#include "DefaultShadingCommand.h"


void DefaultShadingCommand::doImp ()
{
    _scene->setMeshDisplayMode ( Mesh::DisplayMode::SHADING );
}