
/*!
  \file     SetProjectCommand.h
  \author   Tody
  SetProjectCommand definition.
  \date     2015/12/22
*/

#ifndef SETPROJECTCOMMAND_H
#define SETPROJECTCOMMAND_H

#include "BaseCommand.h"

//! SetProjectCommand implementation.
class SetProjectCommand : public BaseCommand
{
public :
    //! Constructor.
    SetProjectCommand ( Scene* scene, const QString& inputDir = "" )
        : BaseCommand ( "Set Project", scene ), _inputDir ( inputDir )
    {
        setIsCheckSceneEmpty ( false );
    }

    //! Destructor.
    virtual ~SetProjectCommand() {}

    void doImp ();

private:
    QString _inputDir;

};

#endif

