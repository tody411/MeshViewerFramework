
//! SceneObject definition.
/*!
  \file     SceneObject.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QObject>

class Scene;

//! SceneObject implementation.
class SceneObject : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    SceneObject ( Scene* scene );


    //! Destructor.
    virtual ~SceneObject() {}

signals:
    void updated();

protected:
    Scene* _scene;

};

#endif

