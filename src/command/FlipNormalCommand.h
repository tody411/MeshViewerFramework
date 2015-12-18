
/*!
  \file     FlipNormalCommand.h
  \author   Tody
  FlipNormalCommand definition.
  \date     2015/12/17
*/

#ifndef FLIPNORMALCOMMAND_H
#define FLIPNORMALCOMMAND_H

#include "BaseCommand.h"

//! FlipNormalCommand implementation.
class FlipNormalCommand : public BaseCommand
{
public :
    //! Constructor.
    FlipNormalCommand ( Scene* scene )
        :  BaseCommand ( "Flip Normal", scene )
    {
    }

    //! Destructor.
    virtual ~FlipNormalCommand() {}

    void doImp ();

};

#endif

