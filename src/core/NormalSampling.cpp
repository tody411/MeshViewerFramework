
//! NormalSampling definition.
/*!
  \file     NormalSampling.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "NormalSampling.h"
#include "NormalClustering.h"

#include "Random.h"

#include <random>

const Eigen::MatrixXd NormalSampling::samples ()
{
    Eigen::MatrixXd N_c ( _numSamples, 3 );

    Eigen::MatrixXd N_l = randomNormals ( _numLearnSamples );
    Eigen::VectorXi clusterIDs;
    Random::randint ( _numLearnSamples, clusterIDs, _numSamples - 1 );

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
    Random::rand ( numSamples, 3, N, -1.0, 1.0 );

    N.rowwise().normalize();
    return N;
}