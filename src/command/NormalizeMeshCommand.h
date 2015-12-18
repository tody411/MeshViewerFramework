
/*!
  \file     NormalizeMeshCommand.h
  \author   Tody
  NormalizeMeshCommand definition.
  \date     2015/12/17
*/

#ifndef NORMALIZEMESHCOMMAND_H
#define NORMALIZEMESHCOMMAND_H

#include "BaseCommand.h"

//! NormalizeMeshCommand implementation.
class NormalizeMeshCommand : public BaseCommand
{
public :
    //! Constructor.
    NormalizeMeshCommand ( Scene* scene )
        :  BaseCommand ( "Normalize Mesh", scene )
    {}

    //! Destructor.
    virtual ~NormalizeMeshCommand() {}

    void doImp ();



};

#endif

