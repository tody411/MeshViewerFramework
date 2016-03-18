
//! Random definition.
/*!
  \file     Random.h
  \author   Tody
  \date     2016/03/18
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <Eigen/Dense>

//! Random implementation.
namespace Random
{
    void rand ( int size, Eigen::VectorXd& x, double low = 0.0, double high = 1.0 );

    void rand ( int rows, int cols, Eigen::MatrixXd& X, double low = 0.0, double high = 1.0 );

    void randint ( int size, Eigen::VectorXi& x, int low = 0, int high = 256 );

    void randint ( int rows, int cols, Eigen::MatrixXi& X, int low = 0, int high = 256 );

};

#endif

