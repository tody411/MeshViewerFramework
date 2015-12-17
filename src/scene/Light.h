
/*!
  \file     Light.h
  \author   Tody
  Light definition.
  \date     2015/12/15
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>

#include "SceneObject.h"

//! Light implementation.
class Light : public SceneObject
{
public :
    //! Constructor.
    Light ( Scene* scene )
        : SceneObject ( scene )
    {
        lightNo = 0;
        lightPosition = Eigen::Vector4f ( 0.2, 0.3, 0.6, 0.0 );

        ambient  = Eigen::Vector4f ( 1.0, 1.0, 1.0, 1.0 );
        diffuse  = Eigen::Vector4f (  1.0, 1.0, 1.0, 1.0 );
        specular  = Eigen::Vector4f (  1.0, 1.0, 1.0, 1.0 );
    }

    //! Destructor.
    virtual ~Light() {}

    void gl();

private:
    int lightNo;
    Eigen::Vector4f lightPosition;
    Eigen::Vector4f ambient;
    Eigen::Vector4f diffuse;
    Eigen::Vector4f specular;
};

#endif

