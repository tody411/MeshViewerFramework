
/*!
  \file     NormalShaderCommand.h
  \author   Tody
  NormalShaderCommand definition.
  \date     2015/12/20
*/

#ifndef NORMALSHADERCOMMAND_H
#define NORMALSHADERCOMMAND_H

#include "BaseCommand.h"

//! NormalShaderCommand implementation.
class NormalShaderCommand : public BaseCommand
{
public :
    //! Constructor.
    NormalShaderCommand ( Scene* scene )
        :  BaseCommand ( "Normal Shader", scene )
    {}

    //! Destructor.
    virtual ~NormalShaderCommand() {}

    void doImp ();



};

#endif

