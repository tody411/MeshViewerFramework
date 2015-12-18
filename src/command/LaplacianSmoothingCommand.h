
/*!
  \file     LaplacianSmoothingCommand.h
  \author   Tody
  LaplacianSmoothingCommand definition.
  \date     2015/12/16
*/

#ifndef LAPLACIANSMOOTHINGCOMMAND_H
#define LAPLACIANSMOOTHINGCOMMAND_H

#include "BaseCommand.h"

#include "SceneParameters.h"

//! LaplacianSmoothingCommand implementation.
class LaplacianSmoothingCommand : public BaseCommand
{
public :
    //! Constructor.
    LaplacianSmoothingCommand ( Scene* scene )
        :  BaseCommand ( "Laplacian Smoothing", scene ), _lambda ( "lambda", 0.0, 100.0, 1.0, "Laplacian Smoothing" )
    {
        _params.addDouble ( &_lambda );
        setInteractive ( true );
    }

    //! Destructor.
    virtual ~LaplacianSmoothingCommand() {}

    void setupImp();

    void doImp ();

private:
    DoubleParameter _lambda;

    Eigen::MatrixXd _V;
    Eigen::SparseMatrix<double> _M;

};

#endif

