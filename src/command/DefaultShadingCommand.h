
/*!
  \file     DefaultShadingCommand.h
  \author   Tody
  DefaultShadingCommand definition.
  \date     2015/12/19
*/

#ifndef DEFAULTSHADINGCOMMAND_H
#define DEFAULTSHADINGCOMMAND_H

#include "BaseCommand.h"

//! DefaultShadingCommand implementation.
class DefaultShadingCommand: public BaseCommand
{
public :
    //! Constructor.
    DefaultShadingCommand ( Scene* scene )
        :  BaseCommand ( "Default Shading", scene )
    {}

    //! Destructor.
    virtual ~DefaultShadingCommand() {}

    void doImp ();


};

#endif

