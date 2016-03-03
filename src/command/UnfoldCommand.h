
/*!
  \file     UnfoldCommand.h
  \author   Tody
  UnfoldCommand definition.
  \date     2016/03/03
*/

#ifndef UNFOLDCOMMAND_H
#define UNFOLDCOMMAND_H

#include "BaseCommand.h"


//! UnfoldCommand implementation.
class UnfoldCommand : public BaseCommand
{
public :
    //! Constructor.
    UnfoldCommand ( Scene* scene )
        :  BaseCommand ( "Unfold", scene ),  _lambda ( "lambda", 0.0, 10.0, 1.0 )
    {
        _params.addDouble ( &_lambda );
        setInteractive ( true );
    }

    //! Destructor.
    virtual ~UnfoldCommand() {}

    void setupImp();

    void doImp ();

private:
    DoubleParameter _lambda;

    Eigen::MatrixXd _UVs;

    Eigen::SparseMatrix<double> _M;
};

#endif

