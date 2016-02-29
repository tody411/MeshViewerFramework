
/*!
  \file     KMeans.cpp
  \author       Tody
  KMeans definition.
  date      2016/02/28
*/

#include "KMeans.h"

#include <random>


const Eigen::MatrixXd KMeans::projectedData() const
{
    Eigen::MatrixXd X;

    project ( _centers, _clusterIDs, X );
    return X;
}

void KMeans::compute ( const Eigen::MatrixXd& X )
{
    int numData = X.rows();
    int dataSize = X.cols();

    _centers.resize ( _numCenters, dataSize );
    _clusterIDs.resize ( numData );

    computeRandomCenters ( _numCenters, numData, _clusterIDs );
    updateCenters ( X, _clusterIDs, _centers );

    for ( int i = 0; i < _numIterations; i++ )
    {
        clustering ( _centers, X, _clusterIDs );
        updateCenters ( X, _clusterIDs, _centers );
    }
}

void KMeans::computeRandomCenters ( int numCenters, int numData, Eigen::VectorXi& clusterIDs )
{
    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_int_distribution<int> randCenter ( 0, numCenters - 1 );

    for ( int i = 0; i < numData; i++ )
    {
        clusterIDs ( i ) = randCenter ( mt );
    }
}


void KMeans::clustering ( const Eigen::MatrixXd& centers, const Eigen::MatrixXd& X, Eigen::VectorXi& clusterIDs )
{
    int numCenters = centers.rows();
    int numData = X.rows();

    Eigen::MatrixXd D ( numData, numCenters );

    for ( int ci = 0; ci < numCenters; ci++ )
    {
        D.col ( ci ) = ( X.rowwise() - centers.row ( ci ) ).rowwise().norm();
    }

    for ( int di = 0; di < numData; di++ )
    {
        int clusterID = 0;
        D.row ( di ).minCoeff ( &clusterID );

        clusterIDs ( di ) = clusterID;
    }
}


void KMeans::project ( const Eigen::MatrixXd& centers, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& X ) const
{
    int numData = clusterIDs.size();
    int dataSize = centers.cols();
    X.resize ( numData, dataSize );

    for ( int di = 0; di < numData; di++ )
    {
        X.row ( di ) = centers.row ( clusterIDs ( di ) );
    }
}


void KMeans::updateCenters ( const Eigen::MatrixXd& X, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& centers )
{
    int numCenters =  centers.rows();

    centers = Eigen::MatrixXd::Zero ( numCenters, centers.cols() );

    Eigen::VectorXd centerHists = Eigen::VectorXd::Zero ( numCenters );

    for ( int di = 0; di < X.rows(); di++ )
    {
        int ci = clusterIDs ( di );

        double w = 1.0;

        centers.row ( ci ) += w * X.row ( di );

        centerHists ( ci ) += w;
    }

    for ( int ci = 0; ci < numCenters; ci++ )
    {
        if ( centerHists ( ci ) > 0.0 )
        {
            centers.row ( ci ) /=  centerHists ( ci );
        }
    }

}