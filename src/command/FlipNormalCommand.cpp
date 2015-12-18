
/*!
  \file     FlipNormalCommand.cpp
  \author       Tody
  FlipNormalCommand definition.
  date      2015/12/17
*/

#include "FlipNormalCommand.h"


void FlipNormalCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->vertexNormals ( N );
    mesh->setVertexNormals ( N );
}