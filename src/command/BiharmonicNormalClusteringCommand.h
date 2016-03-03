
//! BiharmonicNormalClusteringCommand definition.
/*!
  \file     BiharmonicNormalClusteringCommand.h
  \author   Tody
  \date     2015/12/22
*/

#ifndef BIHARMONICNORMALCLUSTERINGCOMMAND_H
#define BIHARMONICNORMALCLUSTERINGCOMMAND_H

#include "BaseCommand.h"

//! BiharmonicNormalClusteringCommand implementation.
class BiharmonicNormalClusteringCommand: public BaseCommand
{
public :
    //! Constructor.
    BiharmonicNormalClusteringCommand ( Scene* scene )
        :  BaseCommand ( "Biharmonic Normal Clustering", scene ),
           _showSmoothColor ( "showSmoothColor", true )
    {
        //_params.addBool ( &_showSmoothColor );
    }

    //! Destructor.
    virtual ~BiharmonicNormalClusteringCommand() {}

    void setupImp();
    void doImp ();

private:
    void computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::MatrixXd& b );

private:
    Eigen::SparseMatrix<double> _M;

    BoolParameter _showSmoothColor;
};

#endif

