
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
    if ( numColors == 1 )
    {
        C = Eigen::Vector3d ( 1, 0, 0 );
        return;
    }

    if ( numColors == 2 )
    {
        C.resize ( 2, 3 );
        C.row ( 0 ) = Eigen::Vector3d ( 1, 0, 0 );
        C.row ( 1 ) = Eigen::Vector3d ( 0, 0, 1 );
        return;
    }

    Eigen::Matrix3d RGB;
    RGB.row ( 0 ) = Eigen::Vector3d ( 1, 0, 0 );
    RGB.row ( 1 ) = Eigen::Vector3d ( 0, 0, 1 );
    RGB.row ( 2 ) = Eigen::Vector3d ( 0, 1, 0 );


    if ( numColors == 3 )
    {
        C = RGB;
        return;
    }

    std::vector<Eigen::Vector3d> colors;
    colors.push_back ( Eigen::Vector3d ( 0, 0, 0 ) );
    colors.push_back ( Eigen::Vector3d ( 1, 1, 1 ) );
    colors.push_back ( Eigen::Vector3d ( 1, 0, 0 ) );
    colors.push_back ( Eigen::Vector3d ( 0, 0, 1 ) );
    colors.push_back ( Eigen::Vector3d ( 0, 1, 0 ) );

    int numColorSpace = 16;

    for ( int ci = 0; ci < numColors - 3; ci++ )
    {
        Eigen::Vector3d colorNew ( 0, 0, 0 );
        double dMax = 0.0;

        for ( int ri = 0; ri < numColorSpace; ri++ )
        {
            for ( int gi = 0; gi < numColorSpace; gi++ )
            {
                for ( int bi = 0; bi < numColorSpace; bi++ )
                {
                    Eigen::Vector3d color ( ri / ( double ) ( numColorSpace - 1 ),
                                            gi / ( double ) ( numColorSpace - 1 ),
                                            bi / ( double ) ( numColorSpace - 1 ) );

                    double dMin = 3.0;

                    for ( int rci = 0; rci < colors.size(); rci++ )
                    {
                        double d = ( color - colors[rci] ).norm();

                        if ( d < dMin )
                        {
                            dMin = d;
                        }
                    }

                    if ( dMin > dMax )
                    {
                        dMax = dMin;
                        colorNew = color;
                    }
                }
            }
        }

        colors.push_back ( colorNew );
    }

    C = Eigen::MatrixXd ( numColors, 3 );

    for ( int i = 0; i < numColors; i++ )
    {
        C.row ( i ) = colors[i + 2];
    }
}