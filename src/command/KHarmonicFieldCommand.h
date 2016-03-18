
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
           _numCenters ( "numCenters", 2, 50, 6 )
    {
        _params.addInt ( &_numCenters );
    }

    //! Destructor.
    virtual ~KHarmonicFieldCommand() {}

    void setupImp();

    void doImp ();

private:
    IntParameter _numCenters;

    Eigen::SparseMatrix<double> _M;

};

#endif

