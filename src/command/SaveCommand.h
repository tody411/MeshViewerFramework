
//! SaveCommand definition.
/*!
  \file     SaveCommand.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "BaseCommand.h"


//! SaveCommand implementation.
class SaveCommand : public BaseCommand
{
public :
    //! Constructor.
    SaveCommand ( Scene* scene, const QString& outputFile = "" )
        : BaseCommand ( "Save 3D Mesh File", scene ), _outputFile ( outputFile )
    {}

    //! Destructor.
    virtual ~SaveCommand() {}

    void doImp ();

private:
    QString _outputFile;



};

#endif

