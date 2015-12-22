
//! ColorMap definition.
/*!
  \file     ColorMap.h
  \author   Tody
  \date     2015/12/22
*/

#ifndef COLORMAP_H
#define COLORMAP_H

#include <Eigen/Dense>

//! ColorMap implementation.
namespace ColorMap
{
    void generateRandomColors ( int numColors, Eigen::MatrixXd& C );


    void generateIDColors ( int numColors, Eigen::MatrixXd& C );
};

#endif

