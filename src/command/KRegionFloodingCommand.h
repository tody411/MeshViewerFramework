
//! KRegionFloodingCommand definition.
/*!
  \file     KRegionFloodingCommand.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef KREGIONFLOODINGCOMMAND_H
#define KREGIONFLOODINGCOMMAND_H

#include "BaseCommand.h"

#include "BiharmonicSmoothing.h"

//! KRegionFloodingCommand implementation.
class KRegionFloodingCommand: public BaseCommand
{
public :
    //! Constructor.
    KRegionFloodingCommand ( Scene* scene )
        :  BaseCommand ( "K-Region Flooding", scene ),
           _numCenters ( "numCenters", 2, 500, 50 ),
           _numIterations ( "numIterations", 1, 500, 10 ),
           _norm ( "norm", 0.0, 50.0, 2.0 ),
           _postFileter ( "postFileter", 0.0, 1000.0, 1.0 )
    {
        _params.addInt ( &_numCenters );
        _params.addInt ( &_numIterations );
        _params.addDouble ( &_norm );
        _params.addDouble ( &_postFileter );
    }

    //! Destructor.
    virtual ~KRegionFloodingCommand() {}

    void setupImp();

    void doImp ();

private:
    void doSelection();

    void doAll();

private:
    IntParameter _numCenters;
    IntParameter _numIterations;
    DoubleParameter _norm;
    DoubleParameter _postFileter;

    BiharmonicSmoothing smoothing;

    Eigen::MatrixXd _N_f;
};

#endif

