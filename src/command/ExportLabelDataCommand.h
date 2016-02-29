
/*!
  \file     ExportLabelDataCommand.h
  \author   Tody
  ExportLabelDataCommand definition.
  \date     2016/02/23
*/

#ifndef EXPORTLABELDATACOMMAND_H
#define EXPORTLABELDATACOMMAND_H

#include "BaseCommand.h"

//! ExportLabelDataCommand implementation.
class ExportLabelDataCommand: public BaseCommand
{
public :
    //! Constructor.
    ExportLabelDataCommand ( Scene* scene, const QString& outputFile = "" )
        : BaseCommand ( "Export Label Data", scene ), _outputFile ( outputFile )
    {}

    //! Destructor.
    virtual ~ExportLabelDataCommand() {}

    void doImp ();

private:
    QString _outputFile;



};

#endif

