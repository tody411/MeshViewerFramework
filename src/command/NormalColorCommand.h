
/*!
  \file     NormalColorCommand.h
  \author   Tody
  NormalColorCommand definition.
  \date     2015/12/17
*/

#ifndef NORMALCOLORCOMMAND_H
#define NORMALCOLORCOMMAND_H

#include "BaseCommand.h"

//! NormalColorCommand implementation.
class NormalColorCommand : public BaseCommand
{
public :
    //! Constructor.
    NormalColorCommand ( Scene* scene )
        :  BaseCommand ( "Normal Color", scene )
    {}

    //! Destructor.
    virtual ~NormalColorCommand() {}

    void doImp ();

};

#endif

