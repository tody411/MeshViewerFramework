
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
        Index r = 10;
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

        inverseIteration ( A );
        //simultaneousIteration ( A, true );
    }

    inline void simultaneousIteration ( const SparseMatrix& A, bool isPositive = false )
    {
        int maxIter = 1000;
        for ( int iter = 0; iter < maxIter; iter++ )
        {
            if ( iter % 10 == 0 )
            {
                std::cout << "simultaneousIteration " << iter << std::endl;
            }

            orthoWeights ();
            _weights = A * _weights;

            if ( isPositive )
            {
                positiveWeights();
            }
            normalizeWeights();
        }
    }

    inline void inverseIteration ( const SparseMatrix& A )
    {
        Scalar tol = 1e-12;
        Scalar epsilon = 1e-14;

        Index n = _weights.rows();
        Index k = _weights.cols();

        SparseMatrix I = DenseMatrix::Identity (  A.rows(),  A.cols() ).sparseView();

        /*int maxIter = 100;
        for ( int iter = 0; iter < maxIter; iter++ )
        {
            orthoWeights ();
            _weights = A * _weights;
            normalizeWeights();
        }

        return;*/

        for ( int i = 0; i < k; i++ )
        {
            std::cout << "InvIteration " << i << std::endl;

            int maxIter = 500;
            for ( int iter = 0; iter < maxIter; iter++ )
            {
                orthoWeights ( i );
                _weights.col ( i ) = A * _weights.col ( i );
                normalizeWeights ( i );
            }

            ScalarVector w = _weights.col ( i );
            Scalar lambda = w.dot ( A * w );

            SparseMatrix B = A - lambda * I;
            Eigen::SimplicialCholesky<SparseMatrix> solver;
            solver.compute ( B );

            if ( solver.info() != Eigen::Success )
            {
                continue;
            }

            maxIter = 50;
            for ( int iter = 0; iter < maxIter; iter++ )
            {
                _weights.col ( i ) = solver.solve ( _weights.col ( i ) );
                normalizeWeights ( i );

                w = _weights.col ( i );

                lambda = w.dot ( A * w );
                Scalar error = ( A * w - lambda * w ).array().abs().maxCoeff();

                std::cout << "  iter" << iter << ": " << error << std::endl;

                if ( error < tol )
                {
                    std::cout << "  lambda: " << lambda << std::endl;
                    break;
                }

            }
        }
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
        orthoWeights ( _weights.cols() );
    }

    inline void orthoWeights ( Index k )
    {
        for ( int i = 0; i < k; i++ )
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
            normalizeWeights ( i );
        }
    }

    inline void normalizeWeights ( Index i )
    {
        /* Scalar w_max = _weights.col ( i ).array().abs().maxCoeff();
             _weights.col ( i ) = _weights.col ( i ) / w_max;*/
        _weights.col ( i ).normalize();
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

