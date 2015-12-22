
//! LoadCommand definition.
/*!
  \file     LoadCommand.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H

#include "BaseCommand.h"

#include <QDir>

//! LoadCommand implementation.
class LoadCommand : public BaseCommand
{
public :
    //! Constructor.
    LoadCommand ( Scene* scene, const QString& inputFile = "" )
        : BaseCommand ( "Load 3D Mesh File", scene ), _inputFile ( inputFile )
    {
        defaultModelDir();
        setIsCheckSceneEmpty ( false );
    }

    //! Destructor.
    virtual ~LoadCommand() {}

    void doImp ();

private:
    void defaultModelDir();

private:
    QString _inputFile;

    QDir _modelDir;

};

#endif

