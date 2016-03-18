
//! Random definition.
/*!
  \file     Random.cpp
  \author       Tody
  \date     2016/03/18
*/

#include "Random.h"

#include <random>

class RandomDistribution
{
public:
    RandomDistribution ( double low, double high )
    {
        std::random_device rd;
        _mt = std::mt19937 ( rd() );
        _rdist =  std::uniform_real_distribution<double> ( low, high );
    }

    double value()
    {
        return _rdist ( _mt );
    }

private:
    std::mt19937 _mt;
    std::uniform_real_distribution<double> _rdist;
};

class RandomDistributionInt
{
public:
    RandomDistributionInt ( int low, int high )
    {
        std::random_device rd;
        _mt = std::mt19937 ( rd() );
        _rdist =  std::uniform_int_distribution<int> ( low, high );
    }

    int value()
    {
        return _rdist ( _mt );
    }

private:
    std::mt19937 _mt;
    std::uniform_int_distribution<int> _rdist;
};

void Random::rand ( int size, Eigen::VectorXd& x, double low, double high )
{
    RandomDistribution rdist ( low, high );

    x.resize ( size );

    for ( int i = 0; i < size; i++ )
    {
        x[i] = rdist.value();
    }
}

void Random::rand ( int rows, int cols, Eigen::MatrixXd& X, double low, double high )
{
    RandomDistribution rdist ( low, high );

    X.resize ( rows, cols );

    int size = rows * cols;
    for ( int i = 0; i < size; i++ )
    {
        X.data() [i] = rdist.value();
    }
}


void Random::randint ( int size, Eigen::VectorXi& x, int low, int high )
{
    RandomDistributionInt rdist ( low, high );

    x.resize ( size );

    for ( int i = 0; i < size; i++ )
    {
        x[i] = rdist.value();
    }
}

void Random::randint ( int rows, int cols, Eigen::MatrixXi& X, int low, int high )
{
    RandomDistributionInt rdist ( low, high );

    X.resize ( rows, cols );

    int size = rows * cols;
    for ( int i = 0; i < size; i++ )
    {
        X.data() [i] = rdist.value();
    }
}