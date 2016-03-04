
//! ColorMap definition.
/*!
  \file     ColorMap.cpp
  \author       Tody
  \date     2015/12/22
*/

#include "ColorMap.h"

#include <random>
#include <iostream>

Eigen::MatrixXd ColorMap::_C_id;

void ColorMap::randomColors ( int numColors, Eigen::MatrixXd& C )
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


void ColorMap::IDColors ( int numColors, Eigen::MatrixXd& C )
{
    if ( numColors > _C_id.size() / 3 )
    {
        generateIDColors ( numColors );
    }

    C = _C_id.block ( 0, 0, numColors, 3 );
}

void ColorMap::heatMap ( const Eigen::VectorXd& V, Eigen::MatrixXd& C )
{
    double v_min = V.minCoeff();
    double v_max = V.maxCoeff();

    heatMap ( V, C, v_min, v_max );
}

void ColorMap::heatMap ( const Eigen::VectorXd& V, Eigen::MatrixXd& C, double v_min, double v_max )
{
    C.resize ( V.rows(), 3 );

    Eigen::Vector3d r ( 1, 0, 0 );
    Eigen::Vector3d g ( 0, 1, 0 );
    Eigen::Vector3d b ( 0, 0, 1 );

    for ( int i = 0; i < V.rows(); i++ )
    {
        double v = V ( i );

        Eigen::Vector3d c;

        double t = ( v - v_min ) / ( v_max - v_min );

        double t_gb = std::max ( 0.0, std::min ( 2.0 * t, 1.0 ) );

        c = ( 1.0 - t_gb ) * b + t_gb * g;

        double t_rg = std::max ( 0.0, std::min ( 2.0 * ( t - 0.5 ), 1.0 ) );
        c = ( 1.0 - t_rg ) * c + t_rg * r;

        C.row ( i ) = c;
    }
}

void ColorMap::generateIDColors ( int numColors )
{
    std::cout << "Generate Colors" << numColors << std::endl;
    if ( numColors == 1 )
    {
        _C_id = Eigen::Vector3d ( 1, 0, 0 );
        return;
    }

    if ( numColors == 2 )
    {
        _C_id.resize ( 2, 3 );
        _C_id.row ( 0 ) = Eigen::Vector3d ( 1, 0, 0 );
        _C_id.row ( 1 ) = Eigen::Vector3d ( 0, 0, 1 );
        return;
    }

    Eigen::Matrix3d RGB;
    RGB.row ( 0 ) = Eigen::Vector3d ( 1, 0, 0 );
    RGB.row ( 1 ) = Eigen::Vector3d ( 0, 0, 1 );
    RGB.row ( 2 ) = Eigen::Vector3d ( 0, 1, 0 );


    if ( numColors == 3 )
    {
        _C_id = RGB;
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

    _C_id = Eigen::MatrixXd ( numColors, 3 );

    for ( int i = 0; i < numColors; i++ )
    {
        _C_id.row ( i ) = colors[i + 2];
    }
}