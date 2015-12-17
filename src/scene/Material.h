
/*!
  \file     Material.h
  \author   Tody
  Material definition.
  \date     2015/12/17
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <Eigen/Dense>

#include "SceneObject.h"

//! Material implementation.
class Material : public SceneObject
{
public :
    //! Constructor.
    Material ( Scene* scene )
        : SceneObject ( scene )
    {
        ambient  = Eigen::Vector4f ( 0.2, 0.2, 0.2, 1.0 );

        diffuse  = Eigen::Vector4f ( 0.4, 0.4, 0.8, 1.0 );

        specular  = Eigen::Vector4f ( 0.6, 0.6, 1.0, 1.0 );

        shininess = 20.0;
    }

    //! Destructor.
    virtual ~Material() {}

    void gl();

private:
    Eigen::Vector4f ambient;
    Eigen::Vector4f diffuse;
    Eigen::Vector4f specular;
    float shininess;


};

#endif

