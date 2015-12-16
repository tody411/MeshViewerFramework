
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

//! Scene implementation.
class Scene : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    Scene ( QObject* parent = nullptr )
        : QObject ( parent )
    {}

    //! Destructor.
    virtual ~Scene() {}

    bool loadMesh ( const QString& filePath );

    void render();

    void focusGL();

    Mesh* mesh()
    {
        return &_mesh;
    }

signals:
    void updated();


private:
    Light       _light;
    Mesh    _mesh;
    BoundingBox _bb;



};

#endif

