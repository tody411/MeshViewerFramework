
/*!
  \file     SmoothNormalCommand.h
  \author   Tody
  SmoothNormalCommand definition.
  \date     2015/12/21
*/

#ifndef SMOOTHNORMALCOMMAND_H
#define SMOOTHNORMALCOMMAND_H

#include "BaseCommand.h"

//! SmoothNormalCommand implementation.
class SmoothNormalCommand : public BaseCommand
{
public :
    //! Constructor.
    SmoothNormalCommand ( Scene* scene )
        :  BaseCommand ( "Normal Smoothing", scene ), _lambda ( "lambda", 0.0, 100.0, 1.0, "NOrmal Smoothing" )
    {
        _params.addDouble ( &_lambda );
        setInteractive ( true );
    }

    //! Destructor.
    virtual ~SmoothNormalCommand() {}

    void setupImp();

    void doImp ();

private:
    DoubleParameter _lambda;

    Eigen::MatrixXd _N;
    Eigen::SparseMatrix<double> _M;


};

#endif

