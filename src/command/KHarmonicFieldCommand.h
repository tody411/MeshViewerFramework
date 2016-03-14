
//! KHarmonicFieldCommand definition.
/*!
  \file     KHarmonicFieldCommand.h
  \author   Tody
  \date     2016/03/14
*/

#ifndef KHARMONICFIELDCOMMAND_H
#define KHARMONICFIELDCOMMAND_H

#include "BaseCommand.h"

//! KHarmonicFieldCommand implementation.
class KHarmonicFieldCommand: public BaseCommand
{
public :
    //! Constructor.
    KHarmonicFieldCommand ( Scene* scene )
        :  BaseCommand ( "K-Harmonic Field", scene ),
           _numCenters ( "numCenters", 2, 50, 6 ),
           _prefilterNormal ( "prefilterNormal", 0.0, 10.0, 1.0 )
    {
        _params.addInt ( &_numCenters );
        _params.addDouble ( &_prefilterNormal );
    }

    //! Destructor.
    virtual ~KHarmonicFieldCommand() {}

    void setupImp();

    void doImp ();

private:
    IntParameter _numCenters;
    DoubleParameter _prefilterNormal;

    Eigen::SparseMatrix<double> _M;

};

#endif

