
//! ColorMap definition.
/*!
  \file     ColorMap.cpp
  \author       Tody
  \date     2015/12/22
*/

#include "ColorMap.h"

#include <random>

void ColorMap::generateRandomColors ( int numColors, Eigen::MatrixXd& C )
{

    C.resize ( numColors, 3 );

    std::random_device rd;
    std::mt19937 mt ( rd() );
    std::uniform_real_distribution<double> randColor ( 0.0, 1.0 );

    for ( int ci = 0; ci < numColors; ci++ )
    {
        C.row ( ci ) = Eigen::Vector3d ( randColor ( mt ), randColor ( mt ), randColor ( mt ) );
    }
}


void ColorMap::generateIDColors ( int numColors, Eigen::MatrixXd& C )
{
    Eigen::Matrix3d RGB;
    RGB.row ( 0 ) = Eigen::Vector3d ( 1, 0, 0 );
    RGB.row ( 1 ) = Eigen::Vector3d ( 0, 1, 0 );
    RGB.row ( 2 ) = Eigen::Vector3d ( 0, 0, 1 );

    Eigen::MatrixXd W ( numColors, 3 );

    for ( int i = 0; i < numColors; i++ )
    {
        double w_r = 1.0 -  2.0 * i / ( double ) ( numColors - 1 );
        double w_b = 2.0 * i / ( double ) ( numColors - 1 ) - 1.0;

        w_r = std::min ( std::max ( w_r, 0.0 ), 1.0 );
        w_b = std::min ( std::max ( w_b, 0.0 ), 1.0 );
        double w_g = 1.0 - w_r - w_b;
        W ( i, 0 ) = w_r;
        W ( i, 1 ) = w_g;
        W ( i, 2 ) = w_b;
    }

    C = W * RGB;
}