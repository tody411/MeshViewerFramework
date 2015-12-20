
/*!
  \file     ToonShaderCommand.h
  \author   Tody
  ToonShaderCommand definition.
  \date     2015/12/19
*/

#ifndef TOONSHADERCOMMAND_H
#define TOONSHADERCOMMAND_H

#include "BaseCommand.h"

#include "SceneParameters.h"

//! ToonShaderCommand implementation.
class ToonShaderCommand : public BaseCommand
{
public :
    //! Constructor.
    ToonShaderCommand ( Scene* scene )
        :  BaseCommand ( "Toon Shader", scene ), _border ( "border", 0.0, 1.0, 0.5, "Threshold" )
    {
        _params.addDouble ( &_border );
        setInteractive ( true );
    }

    //! Destructor.
    virtual ~ToonShaderCommand() {}

    void setupImp();

    void doImp ();

private:
    DoubleParameter _border;

};

#endif

