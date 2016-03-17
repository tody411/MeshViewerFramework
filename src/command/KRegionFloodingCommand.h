
//! KRegionFloodingCommand definition.
/*!
  \file     KRegionFloodingCommand.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef KREGIONFLOODINGCOMMAND_H
#define KREGIONFLOODINGCOMMAND_H

#include "BaseCommand.h"

//! KRegionFloodingCommand implementation.
class KRegionFloodingCommand: public BaseCommand
{
public :
    //! Constructor.
    KRegionFloodingCommand ( Scene* scene )
        :  BaseCommand ( "K-Region Flooding", scene ),
           _numCenters ( "numCenters", 2, 500, 50 ),
           _numIterations ( "numIterations", 1, 500, 1 ),
           _norm ( "norm", 0.0, 1000.0, 2.0 )
    {
        _params.addInt ( &_numCenters );
        _params.addInt ( &_numIterations );
        _params.addDouble ( &_norm );
    }

    //! Destructor.
    virtual ~KRegionFloodingCommand() {}

    void setupImp();

    void doImp ();

private:
    IntParameter _numCenters;
    IntParameter _numIterations;
    DoubleParameter _norm;
};

#endif

