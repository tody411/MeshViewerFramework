
/*!
  \file     Light.h
  \author   Tody
  Light definition.
  \date     2015/12/15
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>

//! Light implementation.
class Light
{
public :
    //! Constructor.
    Light()
    {
        lightNo = 0;
        lightPosition = Eigen::Vector4f ( 0.2, 0.3, 1.0, 0.0 ).normalized();

        ambient  = Eigen::Vector4f ( 0.2, 0.2, 0.2, 1.0 ).normalized();

        diffuse  = Eigen::Vector4f ( 0.8, 0.8, 0.8, 1.0 ).normalized();

        specular  = Eigen::Vector4f ( 0.8, 0.8, 0.8, 1.0 ).normalized();
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

