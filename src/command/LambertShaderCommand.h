
//! LambertShaderCommand definition.
/*!
  \file     LambertShaderCommand.h
  \author   Tody
  \date     2015/12/22
*/

#ifndef LAMBERTSHADERCOMMAND_H
#define LAMBERTSHADERCOMMAND_H

#include "BaseCommand.h"

//! LambertShaderCommand implementation.
class LambertShaderCommand : public BaseCommand
{
public :
    //! Constructor.
    LambertShaderCommand ( Scene* scene )
        :  BaseCommand ( "Lambert Shader", scene )
    {}

    //! Destructor.
    virtual ~LambertShaderCommand() {}

    void doImp ();



};


#endif

