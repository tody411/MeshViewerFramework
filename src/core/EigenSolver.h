
/*!
  \file     EigenSolver.h
  \author   Tody
  EigenSolver definition.
  \date     2015/12/30
*/

#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H

#include <Eigen/Sparse>
#include <Eigen/Dense>

//! EigenSolver implementation with Power Iteration.
template<typename SparseMatrix>
class EigenSolver
{
public :
    typedef typename SparseMatrix::Scalar Scalar;
    typedef typename SparseMatrix::Index Index;
    typedef typename Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> DenseMatrix;
    typedef typename Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ScalarVector;

    //! Constructor.
    EigenSolver ( const SparseMatrix& A )
    {
        int r = ( A.rows() < A.cols() ) ? A.rows() : A.cols();
        compute ( A, r );
    }

    EigenSolver ( const SparseMatrix& A, const Index rank )
    {
        compute ( A, rank );
    }

    //! Compute eigenvalues and eigenvectors in large part.
    void compute ( const SparseMatrix& A, const Index rank )
    {
        computePowerIteration  ( A, rank );
    }

    //! Compute eigenvalues and eigenvectos in large part by Power Iteration.
    void computePowerIteration ( const SparseMatrix& A, const Index rank )
    {
        if ( A.cols() == 0 || A.rows() == 0 )
            return;

        Index k = ( rank < A.cols() ) ? rank : A.cols();

        k = ( k < A.rows() ) ? k : A.rows();

        Index n = ( A.rows() < A.cols() ) ? A.rows() : A.cols();

        _eigenvectors = DenseMatrix::Zero ( n, k );
        _eigenvalues = ScalarVector::Zero ( k, 1 );

        SparseMatrix I ( A.rows(), A.cols() );
        I.setIdentity ();

        Scalar tol = 1e-10;
        Scalar epsilon = 1e-14;

        Scalar errorPre = std::numeric_limits<Scalar>::infinity();

        Scalar sigma = 0;
        Scalar lambda = 0;

        int maxIter = 100;
        int sigmaIter = 1000;

        SparseMatrix B = A;

        for ( int i = 0; i < k; i++ )
        {
            ScalarVector x = ScalarVector::Random ( n, 1 );
            x.normalize();

            for ( int iter = 0; iter < sigmaIter; iter++ )
            {
                orthoToExistingEivenvectors ( x, i );
                powerIteration ( B, x, i );
            }

            orthoToExistingEivenvectors ( x, i );
            Scalar sigma = computeSigma ( B, x );
            std::cout << "Sigma (estimated) " << i << ":" << sigma << std::endl;

            for ( int iter = 0; iter < maxIter; iter++ )
            {
                orthoToExistingEivenvectors ( x, i );

                sigma = computeSigma ( B, x );
                inverseIteration ( B, x, sigma );

                Scalar error = computeError ( B, x );

                if ( error <  tol )
                {
                    std::cout << "Convergence " << iter << ": " << error << std::endl;
                    break;
                }

                if ( iter % ( maxIter / 10 ) == 0 )
                {
                    std::cout << "Error " << iter << ": " << error << std::endl;
                }
            }

            sigma = computeSigma ( B, x );
            std::cout << "Sigma (result) " << i << ":" << sigma << std::endl;

            //! Compute eigenvalue.
            lambda = x.dot ( B * x );

            _eigenvectors.col ( i ) = x;
            _eigenvalues ( i ) = lambda;

        }

        checkOrthogonal();
    }

    //! Compute eigenvalues and eigenvectos in large part by QR Iteration.
    void computeQRIteration ( const SparseMatrix& A, const Index rank )
    {
        if ( A.cols() == 0 || A.rows() == 0 )
            return;

        Index k = ( rank < A.cols() ) ? rank : A.cols();

        k = ( k < A.rows() ) ? k : A.rows();

        Index n = ( A.rows() < A.cols() ) ? A.rows() : A.cols();

        _eigenvectors = DenseMatrix::Random ( n, k );
        _eigenvalues = ScalarVector::Zero ( k, 1 );

        Scalar tol = 1e-10;
        Scalar epsilon = 1e-14;

        int maxIter = 3000;
        for ( int iter = 0; iter < maxIter; iter++ )
        {
            for ( int i = 1; i < k; i++ )
            {
                ScalarVector ui = _eigenvectors.col ( i );
                orthoToExistingEivenvectors ( ui, i );
                _eigenvectors.col ( i ) = ui;
            }

            _eigenvectors = A * _eigenvectors;
            normalizeEigenvectors();
        }

        checkEigenvalueRange ( A );
    }

    //! Return computed eigenvalues.
    ScalarVector eigenvalues() const
    {
        return _eigenvalues;
    }

    //! Return computed eigenvectors.
    DenseMatrix eigenvectors() const
    {
        return _eigenvectors;
    }

private:
    inline void orthoToExistingEivenvectors (  ScalarVector& x, int i )
    {
        for ( int j = 0; j < i; j++ )
        {
            const ScalarVector u = _eigenvectors.col ( j );
            x = x - u.dot ( x ) * u / u.dot ( u );
        }
    }

    inline void removeExistingEigenvectorEntries ( ScalarVector& x, int i )
    {
        for ( int j = 0; j < i; j++ )
        {
            const ScalarVector u = _eigenvectors.col ( j );
            Scalar u_max = u.array().abs().maxCoeff();
            for ( int k = 0; k < u.size(); k++ )
            {
                if ( fabs ( u ( k ) ) > 0.5 * u_max )
                {
                    x ( k ) = 0.0;
                }
            }
        }
    }

    inline void normalizeEigenvectors()
    {
        for ( int i = 0; i < _eigenvectors.cols(); i++ )
        {
            _eigenvectors.col ( i ).normalize();
        }
    }

    inline Scalar computeSigma ( const SparseMatrix& A, const ScalarVector& x )
    {
        return x.dot ( A * x ) / ( x.dot ( x ) );
    }

    inline void powerIteration ( const SparseMatrix& A, ScalarVector& x, int i )
    {
        x = A * x;
        /*for ( int j = 0; j < i; j++ )
        {
            Scalar lambda = _eigenvalues ( j );
            x = x - lambda * x;
        }*/
        x.normalize();
    }

    inline void inverseIteration ( const SparseMatrix& A, ScalarVector& x, Scalar sigma )
    {
        SparseMatrix I ( A.rows(), A.cols() );
        I.setIdentity ();

        SparseMatrix B = A - sigma * I;

        Eigen::SimplicialLDLT<SparseMatrix > solver;
        solver.compute ( B );

        switch ( solver.info() )
        {
        case Eigen::Success:
            break;
        case Eigen::NumericalIssue:
            std::cerr << "Error: Numerical issue." << std::endl;
            return;
        default:
            std::cerr << "Error: Other." << std::endl;
            return;
        }
        x = solver.solve ( x );
        x.normalize();
    }

    inline void deflationMatrix ( const SparseMatrix& A, const ScalarVector& u, SparseMatrix& B )
    {
        SparseMatrix u_sp = u.sparseView();

        B = A - ( ( ( A * u_sp ) * u_sp.transpose() ) * A ) / ( u.dot ( A * u ) );
    }

    inline Scalar computeError ( const SparseMatrix& A, const ScalarVector& x )
    {
        Scalar lambda = x.dot ( A * x );
        Scalar error = ( A * x - lambda * x ).array().abs().maxCoeff();
        return error;
    }

    inline void checkOrthogonal()
    {
        Scalar epsilon = 1e-10;

        for ( int i = 0; i < _eigenvectors.cols(); i++ )
        {
            const ScalarVector ui = _eigenvectors.col ( i );
            for ( int j = 0; j < _eigenvectors.cols(); j++ )
            {
                const ScalarVector uj = _eigenvectors.col ( j );

                Scalar ortho = ui.dot ( uj );

                std::cout << "orth " << i << "," << j << ":" << ortho << std::endl;
            }
        }
    }

    inline void checkEigenvectorRange()
    {
        for ( int i = 0; i < _eigenvectors.cols(); i++ )
        {
            const ScalarVector ui = _eigenvectors.col ( i );

            std::cout << "Eigenvector " << i << ":" << ui.minCoeff() << ", " << ui.maxCoeff() << std::endl;
        }
    }

    inline void checkEigenvalueRange ( const SparseMatrix& A )
    {
        for ( int i = 0; i < _eigenvectors.cols(); i++ )
        {
            const ScalarVector ui = _eigenvectors.col ( i );

            ScalarVector x = A * ui;
            Scalar lambda = ui.dot ( x );
            std::cout << "Eigenvalue " << i << ":" << x.minCoeff() << ", " << x.maxCoeff() << ", " << lambda << std::endl;
        }
    }



private:
    //! Eigenvalues.
    ScalarVector _eigenvalues;

    //! Eigenvectors.
    DenseMatrix _eigenvectors;

};

#endif

