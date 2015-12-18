
/*!
  \file     PositionColorCommand.h
  \author   Tody
  PositionColorCommand definition.
  \date     2015/12/18
*/

#ifndef POSITIONCOLORCOMMAND_H
#define POSITIONCOLORCOMMAND_H

#include "BaseCommand.h"

//! PositionColorCommand implementation.
class PositionColorCommand : public BaseCommand
{
public :
    //! Constructor.
    PositionColorCommand ( Scene* scene )
        :  BaseCommand ( "Position Color", scene )
    {}

    //! Destructor.
    virtual ~PositionColorCommand() {}

    void doImp ();

};

#endif

