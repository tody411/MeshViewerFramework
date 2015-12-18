
/*!
  \file     Scene.h
  \author   Tody
  Scene definition.
  \date     2015/12/15
*/

#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QString>

#include "Light.h"
#include "BoundingBox.h"
#include "Mesh.h"
#include "Material.h"

//! Scene implementation.
class Scene : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    Scene ( QObject* parent = nullptr );


    //! Destructor.
    virtual ~Scene() {}

    bool empty() const
    {
        return _mesh->empty();
    }

    bool loadMesh ( const QString& filePath );

    bool saveMesh ( const QString& filePath );

    void glLight();

    void render();

    void focusGL();

    Mesh* mesh()
    {
        return _mesh;
    }

    Light* light()
    {
        return _light;
    }

    Material* material()
    {
        return _material;
    }

    const BoundingBox boundingBox() const
    {
        return _mesh->boundingBox();
    }

    void  showMessage ( const QString& message, int timeout = 0 );

    void updateBoundingBox();

    void setMeshDisplayMode ( Mesh::DisplayMode displayMode )
    {
        _meshDisplayMode = displayMode;
    }

signals:
    void updated();

    void messageUpdated ( const QString& message, int timeout );

private:
    Light*   _light;
    Mesh*    _mesh;

    Material* _material;

    Mesh::DisplayMode _meshDisplayMode;
};

#endif

