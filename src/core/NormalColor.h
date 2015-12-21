
/*!
  \file     NormalColor.h
  \author   Tody
  NormalColor definition.
  \date     2015/12/20
*/

#ifndef NORMALCOLOR_H
#define NORMALCOLOR_H

#include <Eigen/Dense>

//! NormalColor implementation.
namespace NormalColor
{
    inline void normalToColor ( const Eigen::MatrixXd& N, Eigen::MatrixXd& C )
    {
        C = N;
        C.rowwise().normalize();
        C  =  0.5 * C + 0.5 * Eigen::MatrixXd::Ones ( N.rows(), N.cols() );
    }

    inline void colorToNormal ( const Eigen::MatrixXd& C, Eigen::MatrixXd& N )
    {
        N = 2.0 * C - Eigen::MatrixXd::Ones ( C.rows(), 3 );
        N.rowwise().normalize();
    }

};

#endif

