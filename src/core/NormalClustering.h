
//! NormalClustering definition.
/*!
  \file     NormalClustering.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef NORMALCLUSTERING_H
#define NORMALCLUSTERING_H

#include <Eigen/Dense>


//! NormalClustering implementation.
class NormalClustering
{
public :
    //! Constructor.
    NormalClustering() {}

    //! Destructor.
    virtual ~NormalClustering() {}

    void clustering ( const Eigen::MatrixXd& N_c, const Eigen::MatrixXd& N_l, Eigen::VectorXi& clusterIDs );

    void updateCenters ( const Eigen::MatrixXd& N_l, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& N_c );

    void centerSamples ( const Eigen::MatrixXd& N_c, const Eigen::MatrixXd& N_l, Eigen::VectorXi& sampleIDs );


};

#endif

