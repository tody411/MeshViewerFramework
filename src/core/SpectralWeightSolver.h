
/*!
  \file     SpectralWeightSolver.h
  \author   Tody
  SpectralWeightSolver definition.
  \date     2016/01/04
*/

#ifndef SPECTRALWEIGHTSOLVER_H
#define SPECTRALWEIGHTSOLVER_H

#include <Eigen/Sparse>
#include <Eigen/Dense>

//! SpectralWeightSolver implementation.
template<typename SparseMatrix>
class SpectralWeightSolver
{
public :
    typedef typename SparseMatrix::Scalar Scalar;
    typedef typename SparseMatrix::Index Index;
    typedef typename Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> DenseMatrix;
    typedef typename Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ScalarVector;

    //! Constructor.
    SpectralWeightSolver ( const SparseMatrix& A )
    {
        //int r = ( A.rows() < A.cols() ) ? A.rows() : A.cols();
        Index r = 30;
        compute ( A, r );
    }

    SpectralWeightSolver ( const SparseMatrix& A, const Index rank )
    {
        compute ( A, rank );
    }

    //! Compute spectral weight.
    void compute ( const SparseMatrix& A, const Index rank )
    {
        computeIteration  ( A, rank );
    }

    //! Return computed weights.
    DenseMatrix weights() const
    {
        return _weights;
    }

private:
    //! Compute spectral weight by spectral iteration.
    void computeIteration ( const SparseMatrix& A, const Index rank )
    {
        if ( A.cols() == 0 || A.rows() == 0 )
            return;

        Index k = ( rank < A.cols() ) ? rank : A.cols();

        k = ( k < A.rows() ) ? k : A.rows();

        Index n = ( A.rows() < A.cols() ) ? A.rows() : A.cols();

        _weights = DenseMatrix::Random ( n, k );
        positiveWeights();
        //normalizeWeights();

        Scalar tol = 1e-10;
        Scalar epsilon = 1e-14;

        int maxIter = 1000;
        for ( int iter = 0; iter < maxIter; iter++ )
        {
            orthoWeights ();
            _weights = A * _weights;

            positiveWeights();
            normalizeWeights();
            //unityWeights();
        }

        //unityWeights();
    }

    inline void positiveWeight ( ScalarVector& w )
    {
        Scalar w_min = 0.0;

        for ( int i = 0; i < w.size(); i++ )
        {
            if ( w ( i ) <  w_min )
            {
                w ( i ) = w_min;
            }
        }
    }

    inline void positiveWeights()
    {
        for ( int i = 0; i < _weights.cols(); i++ )
        {
            ScalarVector w = _weights.col ( i );
            positiveWeight ( w );
            _weights.col ( i ) = w;
        }
    }

    inline void orthoWeights ( )
    {
        for ( int i = 0; i < _weights.cols(); i++ )
        {
            ScalarVector wi = _weights.col ( i );
            for ( int j = 0; j < i; j++ )
            {
                const ScalarVector wj = _weights.col ( j );
                wi = wi - wj.dot ( wi ) * wj / wj.dot ( wj );
            }
            _weights.col ( i ) = wi;
        }
    }

    inline void normalizeWeights()
    {
        for ( int i = 0; i < _weights.cols(); i++ )
        {
            /* Scalar w_max = _weights.col ( i ).array().abs().maxCoeff();
             _weights.col ( i ) = _weights.col ( i ) / w_max;*/
            _weights.col ( i ).normalize();
        }
    }

    inline void unityWeights()
    {
        Scalar epsilon = 1e-14;

        for ( int i = 0; i < _weights.rows(); i++ )
        {
            Scalar w_sum =  _weights.row ( i ).sum();
            if ( w_sum > epsilon )
            {
                _weights.row ( i ) /= w_sum;
            }
        }
    }

    inline void centerWeight()
    {
        for ( int i = 0; i < _weights.rows(); i++ )
        {
            ScalarVector w = _weights.row ( i );

            Scalar w_max = 0.0;
            int max_id = -1;

            for ( int j = 0; j < w.size(); j++ )
            {
                if ( w ( j ) > w_max )
                {
                    w_max = w ( j );
                    max_id = j;
                }
            }

            if ( max_id > -1 )
            {
                w ( max_id ) = 1.0;
                _weights.row ( i ) = w;
            }

        }
    }

private:
    //! Weights.
    DenseMatrix _weights;

};

#endif

