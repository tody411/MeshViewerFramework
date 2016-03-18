
//! KHarmonicField definition.
/*!
  \file     KHarmonicField.h
  \author   Tody
  \date     2016/03/14
*/

#ifndef KHARMONICFIELD_H
#define KHARMONICFIELD_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

//! KHarmonicField implementation.
class KHarmonicField
{
public :
    //! Constructor.
    KHarmonicField ( Eigen::SparseMatrix<double>& M, int numCenters )
        : _numCenters ( numCenters )
    {
        _M = M;
        compute();
    }

    //! Destructor.
    virtual ~KHarmonicField() {}


    //! Set FaceNormals.
    void setFaceNormals ( const  Eigen::MatrixXd& N_f ) { _N_f = N_f;}


    //! Out clusterIDs.
    const Eigen::VectorXi clusterIDs() const { return _clusterIDs;}

private:
    void compute();

    void computeRandomCenters ( int numCenters, std::vector<int>& seedFaces );

    void computeWeightConstraint ( const std::vector<int>& seedFaces, Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b );

    void optimize ( std::vector<int>& seedFaces );

    void optimizeWithIncremental ( std::vector<int>& seedFaces );

    void updateCenter ( std::vector<int>& seedFaces );

    void updateClusterIDs ();

private:
    //! Number of cluster centers.
    int             _numCenters;

    //! Cluster center data.
    Eigen::MatrixXd _centers;

    //! Cluster ids.
    Eigen::VectorXi _clusterIDs;

    Eigen::MatrixXd _N_f;
    Eigen::MatrixXd _N_c;

    Eigen::SparseMatrix<double> _M;
    Eigen::MatrixXd _W;
};

#endif

