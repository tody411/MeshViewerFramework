
/*!
  \file     RemoveSmallClusters.h
  \author   Tody
  RemoveSmallClusters definition.
  \date     2016/03/07
*/

#ifndef REMOVESMALLCLUSTERS_H
#define REMOVESMALLCLUSTERS_H

#include "Eigen/Dense"
#include "Eigen/Sparse"

//! RemoveSmallClusters implementation.
class RemoveSmallClusters
{
public :
    //! Constructor.
    RemoveSmallClusters ( const Eigen::VectorXi& clusterIDs, const Eigen::VectorXd& Area_f, const Eigen::SparseMatrix<double>& M )
    {
        _Area_f = Area_f;
        _M = M;
        _clusterIDs = clusterIDs;
        compute();
    }

    //! Destructor.
    virtual ~RemoveSmallClusters() {}

    //! Out clusterIDs.
    const Eigen::VectorXi clusterIDs() const { return _clusterIDs;}

private:
    void compute();

    void computeClusterAreas ( Eigen::VectorXd& Area_c );

    void removeSmallClusters ( const Eigen::VectorXd& Area_c );

    void optimizeWeight();

    void computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b );

private:
    Eigen::VectorXi _clusterIDs;
    Eigen::VectorXd _Area_f;
    Eigen::SparseMatrix<double> _M;
};

#endif

