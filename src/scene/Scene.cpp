
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

bool Scene::loadMesh ( const QString& filePath )
{
    if ( !_mesh.loadMesh ( filePath ) )
    {
        return false;
    }

    Logger::getLogger ( "Scene" )->info ( "Load Mesh", filePath );

    _bb.clear();
    _bb.expand ( * ( _mesh.openMeshData() ) );

    Logger::getLogger ( "Scene" )->info ( "Bounding Box", _bb.dump() );

    emit updated();

    return true;
}


void Scene::render()
{
    glEnable ( GL_LIGHTING );
    _light.gl();

    _mesh.gl();

    glFlush();
}


void Scene::focusGL()
{
    _bb.focusGL();
}