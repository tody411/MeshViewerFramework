
/*!
  \file     FindExtremePoiintsCommand.h
  \author   Tody
  FindExtremePoiintsCommand definition.
  \date     2015/12/22
*/

#ifndef FINDEXTREMEPOIINTSCOMMAND_H
#define FINDEXTREMEPOIINTSCOMMAND_H

#include "BaseCommand.h"

//! FindExtremePoiintsCommand implementation.
class FindExtremePoiintsCommand: public BaseCommand
{
public :
    //! Constructor.
    FindExtremePoiintsCommand ( Scene* scene )
        :  BaseCommand ( "Find Extreme Points", scene )
    {}

    //! Destructor.
    virtual ~FindExtremePoiintsCommand() {}

    void setupImp();

    void doImp ();

private:
    void computeWeightConstraint ( Eigen::SparseMatrix<double>& A, Eigen::VectorXd& b );

private:
    Eigen::SparseMatrix<double> _M;

};
#endif

