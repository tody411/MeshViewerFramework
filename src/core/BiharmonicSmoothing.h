
/*!
  \file     BiharmonicSmoothing.h
  \author   Tody
  BiharmonicSmoothing definition.
  \date     2016/03/17
*/

#ifndef BIHARMONICSMOOTHING_H
#define BIHARMONICSMOOTHING_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "Mesh.h"

//! BiharmonicSmoothing implementation.
class BiharmonicSmoothing
{
public :
    //! Constructor.
    BiharmonicSmoothing()
        : _w_u ( 0.1 ), _w_a ( 1.0 ), _sigma ( 0.5 ), _lambda ( 100.0 )
    {}

    //! Destructor.
    virtual ~BiharmonicSmoothing() {}


    //! Set HarmonicDistanceWeight.
    void setHarmonicDistanceWeight ( double w_u, double w_a, double sigma )
    {
        _w_u = w_u;
        _w_a = w_a;
        _sigma = sigma;
    }


    //! Set Lambda.
    void setLambda ( double lambda ) { _lambda = lambda;}

    void setMesh ( Mesh* mesh );

    void setLaplacianMatrix ( const Eigen::SparseMatrix<double>& L );

    void setConstraints ( const Eigen::MatrixXd& b_cons );


    const Eigen::MatrixXd smoothing ();

    void smoothingClusters ( Eigen::VectorXi& clusterIDs );

private:
    Eigen::SparseMatrix<double> _M;

    Eigen::SparseMatrix<double> _A_cons;
    Eigen::MatrixXd _b_cons;

    double _lambda;
    double _w_u;
    double _w_a;
    double _sigma;


};

#endif

