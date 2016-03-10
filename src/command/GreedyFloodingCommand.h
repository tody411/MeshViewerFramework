
//! GreedyFloodingCommand definition.
/*!
  \file     GreedyFloodingCommand.h
  \author   Tody
  \date     2016/03/10
*/

#ifndef GREEDYFLOODINGCOMMAND_H
#define GREEDYFLOODINGCOMMAND_H

#include "BaseCommand.h"

//! GreedyFloodingCommand implementation.
class GreedyFloodingCommand: public BaseCommand
{
public :
    //! Constructor.
    GreedyFloodingCommand ( Scene* scene )
        :  BaseCommand ( "Greedy Flooding", scene ),
           _tolerance ( "tolerance", 0.0, 1.0, 0.1 )

    {
        _params.addDouble ( &_tolerance );

    }

    void doImp ();

private:
    DoubleParameter _tolerance;

};

#endif

