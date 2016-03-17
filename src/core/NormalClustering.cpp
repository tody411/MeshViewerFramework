
//! NormalClustering definition.
/*!
  \file     NormalClustering.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "NormalClustering.h"


void NormalClustering::clustering ( const Eigen::MatrixXd& N_c, const Eigen::MatrixXd& N_l, Eigen::VectorXi& clusterIDs )
{
    clusterIDs.resize ( N_l.rows() );

    Eigen::MatrixXd W = N_c * N_l.transpose();

    for ( int di = 0; di < clusterIDs.size(); di++ )
    {
        int clusterID = 0;
        W.col ( di ).maxCoeff ( &clusterID );
        clusterIDs ( di ) = clusterID;
    }
}

void NormalClustering::updateCenters ( const Eigen::MatrixXd& N_l, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& N_c )
{
    N_c = Eigen::MatrixXd::Zero ( clusterIDs.maxCoeff() + 1, 3  );

    for ( int di = 0; di < clusterIDs.size(); di++ )
    {
        int clusterID = clusterIDs[di];

        if ( clusterID < 0 ) continue;

        N_c.row ( clusterID ) += N_l.row ( di );
    }

    N_c.rowwise().normalize();
}

void NormalClustering::centerSamples ( const Eigen::MatrixXd& N_c, const Eigen::MatrixXd& N_l, Eigen::VectorXi& sampleIDs )
{
    sampleIDs.resize ( N_c.rows() );

    Eigen::MatrixXd W = N_c * N_l.transpose();

    for ( int ci = 0; ci < N_c.rows(); ci++ )
    {
        int sampleID = 0;
        W.row ( ci ).maxCoeff ( &sampleID );
        sampleIDs ( ci ) = sampleID;
    }
}