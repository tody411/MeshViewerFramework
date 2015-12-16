
//! SceneObject definition.
/*!
  \file     SceneObject.cpp
  \author       Tody
  \date     2015/12/16
*/

#include "SceneObject.h"

#include "Scene.h"

SceneObject::SceneObject ( Scene* scene )
    : _scene ( scene ), QObject ( scene )
{
    connect ( this, & SceneObject::updated, _scene, & Scene::updated );
}