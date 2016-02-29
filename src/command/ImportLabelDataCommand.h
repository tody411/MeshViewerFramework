
/*!
  \file     ImportLabelDataCommand.h
  \author   Tody
  ImportLabelDataCommand definition.
  \date     2016/02/27
*/

#ifndef IMPORTLABELDATACOMMAND_H
#define IMPORTLABELDATACOMMAND_H

#include "BaseCommand.h"

#include <QDir>


//! ImportLabelDataCommand implementation.
class ImportLabelDataCommand : public BaseCommand
{
public :
    //! Constructor.
    ImportLabelDataCommand ( Scene* scene, const QString& inputFile = "" )
        : BaseCommand ( "Import Label Data", scene ), _inputFile ( inputFile )
    {
    }

    //! Destructor.
    virtual ~ImportLabelDataCommand() {}

    void doImp ();

private:
    void defaultModelDir();

private:
    QString _inputFile;

};

#endif

