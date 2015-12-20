
/*!
  \file     Camera.h
  \author   Tody
  Camera definition.
  \date     2015/12/19
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

#include "SceneObject.h"

//! Camera implementation.
class Camera: public SceneObject
{
public :
    //! Constructor.
    Camera ( Scene* scene )
        : SceneObject ( scene )
    {
        _scale = Eigen::Vector3f::Ones();
    }

    //! Destructor.
    virtual ~Camera() {}

    void focus()
    {
        _scale = Eigen::Vector3f::Ones();
        _translation = Eigen::Vector3f::Zero();

        emit updated();
    }

    void setAspect ( double aspect )
    {
        _aspect = aspect;
    }

    double aspect() const
    {
        return _aspect;
    }

    void setScale ( const Eigen::Vector3f& scale )
    {
        _scale = scale;
        emit updated();
    }

    const Eigen::Vector3f scale() const
    {
        return _scale;
    }

    void setTranslation ( const Eigen::Vector3f& translation )
    {
        _translation = translation;
        emit updated();
    }

    const Eigen::Vector3f translation() const
    {
        return _translation;
    }

    void setRotation ( const Eigen::Vector3f& rotation )
    {
        _rotation = rotation;
        emit updated();
    }

    const Eigen::Vector3f rotation() const
    {
        return _rotation;
    }

    void gl();

private:
    double _aspect;

    Eigen::Vector3f _scale;

    Eigen::Vector3f _translation;

    Eigen::Vector3f _rotation;


};

#endif

