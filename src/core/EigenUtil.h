
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
    template <typename MatrixType>
    const std::string info ( const MatrixType& X, const std::string& name )
    {
        std::stringstream ss;
        ss << name << ": " << X.rows() << ", " << X.cols() << std::endl;
        ss << "  Range:" << X.minCoeff() << ", " << X.maxCoeff();
        ss << "  Norm: " << X.norm();
        return ss.str();
    }
};

#endif

