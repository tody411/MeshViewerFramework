
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

#include "Camera.h"
#include "Light.h"
#include "BoundingBox.h"
#include "Mesh.h"
#include "Material.h"
#include "ShaderObject.h"
#include "SelectionInfo.h"
#include "Project.h"

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

    void glCamera();

    void glFocus();

    Mesh* mesh()
    {
        return _mesh;
    }

    Camera* camera()
    {
        return _camera;
    }

    Light* light()
    {
        return _light;
    }

    Material* material()
    {
        return _material;
    }

    SelectionInfo* selectionInfo()
    {
        return _selection;
    }

    ShaderObject* shader()
    {
        return _shader;
    }

    Project* project()
    {
        return &_project;
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
    //! Camera object.
    Camera* _camera;

    //! Light object.
    Light*   _light;

    //! Mesh object.
    Mesh*    _mesh;

    //! Materials.
    Material* _material;

    //! Selection info.
    SelectionInfo* _selection;

    //! Mesh display mode.
    Mesh::DisplayMode _meshDisplayMode;

    //! Shader program.
    ShaderObject* _shader;

    //! Project.
    Project _project;
};

#endif

