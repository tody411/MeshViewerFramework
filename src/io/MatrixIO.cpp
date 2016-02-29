
/*!
  \file     MatrixIO.cpp
  \author       Tody
  MatrixIO definition.
  date      2014/07/09
*/

#include "MatrixIO.h"

#include <Eigen/SparseCore>
#include <unsupported/Eigen/SparseExtra>

#include <fstream>

void MatrixIO::save ( const Eigen::MatrixXd& mat, const std::string& filePath )
{
    std::ofstream  ofs ( filePath );
    if ( !ofs )
    {
        std::string openError ( "Could not open: " );
        openError += filePath;
        std::cout << openError << std::endl;
        return;
    }
    ofs << mat;
}

void MatrixIO::saveSparse ( const Eigen::SparseMatrix<double>& M, const std::string& filePath )
{
    Eigen::saveMarket ( M, filePath );
}

void MatrixIO::load ( Eigen::MatrixXd& mat, const std::string& filePath )
{
    std::ifstream ifs ( filePath );

    if ( !ifs )
    {
        std::string openError ( "Could not open: " );
        openError += filePath;
        std::cout << openError << std::endl;
        return;
    }

    std::string str;

    std::vector <double> dataVec;

    int rowSize = 0;
    int colSize = 0;

    while ( ifs && getline ( ifs, str ) )
    {
        std::istringstream iss ( str );

        int tColSize = 0;
        while ( !iss.eof() )
        {
            double data;
            iss >> data;
            dataVec.push_back ( data );
            tColSize++;
        }

        if ( colSize == 0 )
        {
            colSize = tColSize;
        }

        if ( colSize != tColSize )
        {
            std::cout << "Matrix data is broken."  << std::endl;
        }
        rowSize++;
    }

    if ( dataVec.size() != rowSize * colSize )
    {
        std::cout << "Matrix data is broken."  << std::endl;
    }

    mat = Eigen::MatrixXd ( rowSize, colSize );

    for ( unsigned int i = 0; i < rowSize; ++i )
    {
        for ( unsigned int j = 0; j < colSize; ++j )
        {
            mat ( i, j ) = dataVec[i * colSize + j];
        }
    }
}

void MatrixIO::loadSparse ( Eigen::SparseMatrix<double>& M, const std::string& filePath )
{
    Eigen::loadMarket ( M, filePath );
}