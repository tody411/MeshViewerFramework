
/*!
  \file     NoiseCommand.h
  \author   Tody
  NoiseCommand definition.
  \date     2015/12/18
*/

#ifndef NOISECOMMAND_H
#define NOISECOMMAND_H

#include "BaseCommand.h"

#include "SceneParameters.h"

//! NoiseCommand implementation.
class NoiseCommand: public BaseCommand
{
public :
    //! Constructor.
    NoiseCommand ( Scene* scene )
        : BaseCommand ( "Noise", scene ), _sigma ( "sigma", 0.0, 0.1, 0.05, "Noise" )
    {
        _params.addDouble ( &_sigma );
        setInteractive ( true );
    }

    //! Destructor.
    virtual ~NoiseCommand() {}

    void setupImp();

    void doImp ();

private:
    DoubleParameter _sigma;

    Eigen::MatrixXd _V;



};

#endif

