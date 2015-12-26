
/*!
  \file     EigenUtil.cpp
  \author       Tody
  EigenUtil definition.
  date      2015/12/25
*/

#include "EigenUtil.h"



const std::string EigenUtil::info ( const Eigen::MatrixXd& X, const std::string& name )
{
    std::stringstream ss;
    ss << name << ": " << X.rows() << ", " << X.cols() << std::endl;
    ss << "  Rnage " << X.minCoeff() << ", " << X.maxCoeff();
    ss << "  Norm: " << X.norm();
    return ss.str();
}