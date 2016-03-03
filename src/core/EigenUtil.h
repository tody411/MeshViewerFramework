
/*!
  \file     EigenUtil.h
  \author   Tody
  EigenUtil definition.
  \date     2015/12/25
*/

#ifndef EIGENUTIL_H
#define EIGENUTIL_H

#include "Eigen/Dense"

#include <vector>

//! EigenUtil implementation.
namespace EigenUtil
{
    template <typename MatrixType>
    const std::string info ( const MatrixType& X, const std::string& name )
    {
        std::stringstream ss;
        ss << name << ": " << X.rows() << ", " << X.cols() << std::endl;
        ss << "  Range:" << X.minCoeff() << ", " << X.maxCoeff();
        ss << "  Norm: " << X.norm();
        return ss.str();
    }

    template <typename ListType, typename VectorType>
    void listToVector ( const ListType& X, VectorType& Y )
    {
        Y.resize ( X.size() );

        for ( int i = 0; i < X.size(); i++ )
        {
            Y[i] = X[i];
        }
    }

    template <typename VectorType, typename ListType>
    void vectorToList ( const VectorType& X, ListType& Y )
    {
        Y.resize ( X.size() );

        for ( int i = 0; i < X.size(); i++ )
        {
            Y[i] = X[i];
        }
    }

    template <typename ListType, typename MatrixType>
    void listToMatrix ( const ListType& X, int rows, int cols, MatrixType& Y )
    {
        Y.resize ( rows, cols );

        int di = 0;
        for ( int ri = 0; ri < rows; ri++ )
        {
            for ( int ci = 0; ci < cols; ci++ )
            {
                Y ( ri, ci ) = X[di];
                ++di;
            }
        }
    }

    template <typename MatrixType, typename ListType>
    void matrixToList ( const MatrixType& X, ListType& Y )
    {
        int dsize = X.rows() * X.cols();

        Y.resize ( dsize );

        int di = 0;
        for ( int ri = 0; ri < rows; ri++ )
        {
            for ( int ci = 0; ci < cols; ci++ )
            {
                Y[di] = X ( ri, ci );
                ++di;
            }
        }
    }

    template <typename IndexVectorType>
    void isValue ( const IndexVectorType& X, int value, IndexVectorType& Y )
    {
        std::vector<int> Y_list;

        for ( int i = 0; i < X.size(); i++ )
        {
            if ( X[i] == value )
            {
                Y_list.push_back ( i );
            }
        }

        if ( Y_list.empty() )
        {
            std::cout << "Y_list is empty" << std::endl;
            return;
        }

        listToVector ( Y_list, Y );
    }

    template <typename MatrixType, typename IndexType>
    void slice ( const MatrixType& X, const IndexType& R, MatrixType& Y )
    {
        if ( R.size() == 0 ) return;

        Y.resize ( R.size(), X.cols() );

        for ( int ri = 0; ri < R.size(); ri++ )
        {
            for ( int ci = 0; ci < X.cols(); ci++ )
            {
                Y ( ri, ci ) = X ( R[ri], ci );
            }
        }
    }
};

#endif

