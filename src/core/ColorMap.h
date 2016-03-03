
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
class ColorMap
{
public:
    static void randomColors ( int numColors, Eigen::MatrixXd& C );

    static void IDColors ( int numColors, Eigen::MatrixXd& C );

    static void heatMap ( const Eigen::VectorXd& V, Eigen::MatrixXd& C );

    static void heatMap ( const Eigen::VectorXd& V, Eigen::MatrixXd& C, double v_min, double v_max );

private:
    static void generateIDColors ( int numColors );

private:
    static Eigen::MatrixXd _C_id;
};

#endif

