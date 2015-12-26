
/*!
  \file     EigenUtil.h
  \author   Tody
  EigenUtil definition.
  \date     2015/12/25
*/

#ifndef EIGENUTIL_H
#define EIGENUTIL_H

#include "Eigen/Dense"

//! EigenUtil implementation.
namespace EigenUtil
{
    const std::string info ( const Eigen::MatrixXd& X, const std::string& name );
};

#endif

