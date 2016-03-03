
//! PlanarMappingCommand definition.
/*!
  \file     PlanarMappingCommand.h
  \author   Tody
  \date     2016/02/29
*/

#ifndef PLANARMAPPINGCOMMAND_H
#define PLANARMAPPINGCOMMAND_H

#include "BaseCommand.h"

//! PlanarMappingCommand implementation.
class PlanarMappingCommand : public BaseCommand
{
public :
    //! Constructor.
    PlanarMappingCommand ( Scene* scene )
        :  BaseCommand ( "Planar Mapping", scene )
    {}

    //! Destructor.
    virtual ~PlanarMappingCommand() {}

    void doImp ();

private:
    void doAll();

    void doSelection();

    void doLabel();

};


#endif

