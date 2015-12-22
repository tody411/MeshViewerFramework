
/*!
  \file     Scene.cpp
  \author       Tody
  Scene definition.
  date      2015/12/15
*/

#define OM_USE_OSG

#include "Scene.h"

#include <OpenMesh/Core/IO/MeshIO.hh>

#include <QGLWidget>
#include <QtOpenGL>

#include <Eigen/Dense>

#include "Logger.h"

Scene::Scene ( QObject* parent )
    : QObject ( parent ), _meshDisplayMode ( Mesh::DisplayMode::GLSL )
{
    _camera = new Camera ( this );
    _mesh = new Mesh ( this );
    _light = new Light ( this );
    _material = new Material ( this );
    _selection = new SelectionInfo ( this );
    _shader = new ShaderObject ( this );
}

bool Scene::loadMesh ( const QString& filePath )
{
    _selection->clear();

    if ( !_mesh->loadMesh ( filePath ) )
    {
        return false;
    }

    _meshDisplayMode =  Mesh::DisplayMode::GLSL;

    return true;
}

bool Scene::saveMesh ( const QString& filePath )
{
    return _mesh->saveMesh ( filePath );
}


void Scene::render()
{
    if ( _meshDisplayMode == Mesh::DisplayMode::GLSL )
    {
        _shader->bind();

    }
    glEnable ( GL_LIGHTING );

    _mesh->gl ( _meshDisplayMode );

    if ( _meshDisplayMode == Mesh::DisplayMode::GLSL )
    {
        _shader->release();
    }

    _selection->gl();

    glFlush();
}

void Scene::glCamera()
{
    _camera->gl();
    //_mesh->glFocus();
}


void Scene::glFocus()
{
    _mesh->glFocus();
}

void  Scene::showMessage ( const QString& message, int timeout )
{
    emit messageUpdated ( message, timeout );
}
