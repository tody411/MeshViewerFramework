
/*!
  \file     HieerarchicalClustering.cpp
  \author       Tody
  HieerarchicalClustering definition.
  date      2016/03/14
*/

#include "HieerarchicalClustering.h"


void HieerarchicalClustering::compute ( Eigen::VectorXi& clusterIDs )
{
    fit ( clusterIDs );
}


void HieerarchicalClustering::fit ( const Eigen::VectorXi& clusterIDs )
{
    int numClusters = clusterIDs.maxCoeff() + 1;

    _N_c.resize ( numClusters, 3 );
    _Area_c = Eigen::VectorXd::Zero ( numClusters );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        int clusterID = clusterIDs[fi];

        _Area_c[clusterID] += _Area_f[fi];
        _N_c.row ( clusterID ) += _N_f.row ( fi );
    }

    _N_c.rowwise().normalize();
}

void HieerarchicalClustering::pushEdges ( const Eigen::VectorXi& clusterIDs, HCQue& edgeQue )
{
    for ( int ei = 0; ei < _A_ef.rows(); ei++ )
    {
        if ( _A_ef ( ei, 0 ) == -1 || _A_ef ( ei, 1 ) == -1 ) continue;

        int f1 =  _A_ef ( ei, 0 ) ;
        int f2 =  _A_ef ( ei, 1 ) ;

        int c1 = clusterIDs[f1];
        int c2 = clusterIDs[f2];

        if ( c1 == c2 ) continue;

        double A_c1 = _Area_c[c1];
        double A_c2 = _Area_c[c2];

        double E_c1 = _E_c[c1];
        double E_c2 = _E_c[c2];

        double error = ( A_c1 * E_c1 + A_c2 * E_c2 ) / ( A_c1 + A_c2 );

        edgeQue.push ( HCQueData ( error, c1, c2 ) );
    }
}

void HieerarchicalClustering::mergeClusters ( int c1, int c2, Eigen::VectorXi& clusterIDs )
{
    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        int clusterID = clusterIDs[fi];

        if ( clusterID == c2 )
        {
            clusterIDs[fi] = c1;
        }
    }

    double A_c1 = _Area_c[c1];
    double A_c2 = _Area_c[c2];

    double E_c1 = _E_c[c1];
    double E_c2 = _E_c[c2];

    Eigen::Vector3d N_c1 = _N_c.row ( c1 );
    Eigen::Vector3d N_c2 = _N_c.row ( c2 );

    Eigen::Vector3d N_c = A_c1 * N_c1 + A_c2 * N_c2;
    N_c.normalize();

    _E_c[c1] = ( A_c1 * ( N_c1 - N_c ).norm() + A_c2 * ( N_c2 - N_c ).norm() ) / ( A_c1 + A_c2 );

    _N_c.row ( c1 ) = N_c;

    _Area_c[c1] = ( A_c1 + A_c2 );
}