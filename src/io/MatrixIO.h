
/*!
  \file     MatrixIO.h
  \author   Tody
  MatrixIO definition.
  \date     2014/07/09
*/

#ifndef	MATRIXIO_H
#define	MATRIXIO_H

#include <Eigen/Core>
#include <Eigen/Sparse>
#include <ostream>
#include <string>

//! MatrixIO implementation.
class MatrixIO
{
public :
  //! Constructor.
  MatrixIO(){}

  //! Destructor.
  virtual ~MatrixIO(){}

  static void save(const Eigen::MatrixXd& mat, const std::string& filePath);
  static void saveSparse(const Eigen::SparseMatrix<double>& M, const std::string& filePath);
  
  static void load( Eigen::MatrixXd& mat, const std::string& filePath);
  
  static void loadSparse( Eigen::SparseMatrix<double>& M, const std::string& filePath);

private:

// inputs.

  
// outputs.

  

};

#endif

