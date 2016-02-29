
/*!
  \file     KMeans.h
  \author   Tody
  KMeans definition.
  \date     2016/02/28
*/

#ifndef KMEANS_H
#define KMEANS_H

#include <Eigen/Dense>

//! KMeans implementation.
class KMeans
{
public :
    //! Constructor.
    KMeans ()
        : _numIterations ( 40 )
    {}

    //! Destructor.
    virtual ~KMeans() {}


    //! Set NumIterations.
    void setNumIterations ( int numIterations ) { _numIterations = numIterations;}

    //! Set NumCenters.
    void setNumCenters ( int numCenters ) { _numCenters = numCenters;}

    //! Set Centers.
    void setCenters ( const Eigen::MatrixXd& centers )
    {
        _centers = centers;
    }

    //! Out centers.
    const Eigen::MatrixXd centers() const { return _centers;}

    //! Out clusterIDs.
    const Eigen::VectorXi clusterIDs() const { return _clusterIDs;}

    //! Out clusterWeights.
    const Eigen::MatrixXd clusterWeights() const { return _clusterWeights;}


    //! Out projectedData.
    const Eigen::MatrixXd projectedData() const;


    void compute ( const Eigen::MatrixXd& X );

private:
    void computeRandomCenters ( int numCenters, int numData, Eigen::VectorXi& clusterIDs );

    void clustering ( const Eigen::MatrixXd& centers, const Eigen::MatrixXd& X, Eigen::VectorXi& clusterIDs );

    void project ( const Eigen::MatrixXd& centers, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& X ) const;

    void updateCenters ( const Eigen::MatrixXd& X, const Eigen::VectorXi& clusterIDs, Eigen::MatrixXd& centers );

private:
    //! Number of iterations.
    int _numIterations;

    //! Number of cluster centers.
    int             _numCenters;

    //! Cluster center data.
    Eigen::MatrixXd _centers;

    //! Cluster ids.
    Eigen::VectorXi _clusterIDs;

    //! Cluster weights.
    Eigen::MatrixXd _clusterWeights;

};

#endif

