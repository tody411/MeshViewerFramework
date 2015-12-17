
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
    : QObject ( parent )
{
    _mesh = new Mesh ( this );
    _light = new Light ( this );
    _material = new Material ( this );
}

bool Scene::loadMesh ( const QString& filePath )
{
    if ( !_mesh->loadMesh ( filePath ) )
    {
        return false;
    }

    Logger::getLogger ( "Scene" )->info ( "Load Mesh", filePath );

    _bb.clear();
    _bb.expand ( * ( _mesh->openMeshData() ) );

    Logger::getLogger ( "Scene" )->info ( "Bounding Box", _bb.dump() );

    emit updated();

    return true;
}

bool Scene::saveMesh ( const QString& filePath )
{
    return _mesh->saveMesh ( filePath );
}


void Scene::render()
{
    glEnable ( GL_LIGHTING );

    _mesh->gl ( Mesh::DisplayMode::WIREFRAME );

    glFlush();
}


void Scene::focusGL()
{
    _bb.focusGL();
}

void  Scene::showMessage ( const QString& message, int timeout )
{
    emit messageUpdated ( message, timeout );
}