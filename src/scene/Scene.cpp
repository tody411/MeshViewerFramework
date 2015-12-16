
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
    _bb.addMesh ( _mesh );

    Logger::getLogger ( "Scene" )->info ( "Bounding Box", _bb.dump() );

    emit updated();

    return true;
}


void Scene::render()
{
    _light.gl();

    _geometry.gl();

    //glDisable ( GL_LIGHTING );

    /*glBegin ( GL_TRIANGLES );

    MeshData::ConstFaceIter    fIt ( _mesh.faces_begin() ),
             fEnd ( _mesh.faces_end() );
    MeshData::ConstFaceVertexIter fvIt;
    for ( ; fIt != fEnd; ++fIt )
    {
        fvIt = _mesh.cfv_iter ( fIt.handle() );
        glVertex3fv ( &_mesh.point ( fvIt ) [0] );
        glNormal3fv ( &_mesh.normal ( fvIt ) [0] );
        ++fvIt;
        glVertex3fv ( &_mesh.point ( fvIt ) [0] );
        glNormal3fv ( &_mesh.normal ( fvIt ) [0] );
        ++fvIt;
        glVertex3fv ( &_mesh.point ( fvIt ) [0] );
        glNormal3fv ( &_mesh.normal ( fvIt ) [0] );
    }
    glEnd();*/

    glFlush();
}


void Scene::focusGL()
{
    if ( _mesh.vertices_empty() ) return;

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    Eigen::VectorXf pMean = _bb.pMean();

    float range = _bb.range();

    float scale = 2.0 / range;

    glScalef ( scale, scale, scale );
    glTranslatef ( - pMean ( 0 ), - pMean ( 1 ), - pMean ( 2 ) );
}