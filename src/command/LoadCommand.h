
//! LoadCommand definition.
/*!
  \file     LoadCommand.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H

#include "BaseCommand.h"

//! LoadCommand implementation.
class LoadCommand : public BaseCommand
{
public :
    //! Constructor.
    LoadCommand ( Scene* scene, const QString& inputFile = "" )
        : BaseCommand ( "Load 3D Mesh File", scene ), _inputFile ( inputFile )
    {}

    //! Destructor.
    virtual ~LoadCommand() {}

    void doImp ();

private:
    QString _inputFile;


};

#endif

