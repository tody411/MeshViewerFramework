
//! NormalSampling definition.
/*!
  \file     NormalSampling.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "NormalSampling.h"
#include "NormalClustering.h"

#include <random>

const Eigen::MatrixXd NormalSampling::samples ()
{
    Eigen::MatrixXd N_c ( _numSamples, 3 );

    Eigen::MatrixXd N_l = randomNormals ( _numLearnSamples );
    Eigen::VectorXi clusterIDs = randomIDs ( _numLearnSamples, _numSamples );

    NormalClustering normalClustering;

    normalClustering.updateCenters ( N_l, clusterIDs, N_c );

    for ( int i = 0; i < _numIterations; i++ )
    {
        normalClustering.clustering ( N_c, N_l, clusterIDs );
        normalClustering.updateCenters ( N_l, clusterIDs, N_c );
    }
    return N_c;
}


const Eigen::MatrixXd NormalSampling::randomNormals ( int numSamples )
{
    Eigen::MatrixXd N ( numSamples, 3 );

    std::random_device rd;
    std::mt19937 mt ( rd() );
    std::uniform_real_distribution<double> randomNormal ( -1.0, 1.0 );

    for ( int i = 0; i < numSamples; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            N ( i, j ) = randomNormal ( mt );
        }
    }

    N.rowwise().normalize();
    return N;
}

const Eigen::VectorXi NormalSampling::randomIDs (  int numSamples, int numLabels )
{
    Eigen::VectorXi clusterIDs ( numSamples );

    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_int_distribution<int> randomID ( 0, numLabels - 1 );

    for ( int i = 0; i < numSamples; i++ )
    {
        clusterIDs[i] = randomID ( mt );
    }
    return clusterIDs;
}
