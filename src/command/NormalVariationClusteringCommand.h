
/*!
  \file     NormalVariationClusteringCommand.h
  \author   Tody
  NormalVariationClusteringCommand definition.
  \date     2015/12/22
*/

#ifndef NORMALVARIATIONCLUSTERINGCOMMAND_H
#define NORMALVARIATIONCLUSTERINGCOMMAND_H

#include "BaseCommand.h"

//! NormalVariationClusteringCommand implementation.
class NormalVariationClusteringCommand: public BaseCommand
{
public :
    //! Constructor.
    NormalVariationClusteringCommand ( Scene* scene )
        :  BaseCommand ( "Normal Kmeans", scene ), _numCenters ( "numCenters", 2, 20, 6 )
    {
        _params.addInt ( &_numCenters );
    }

    //! Destructor.
    virtual ~NormalVariationClusteringCommand() {}

    void doImp ();

private:
    IntParameter _numCenters;

};

#endif

