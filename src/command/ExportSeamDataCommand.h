
/*!
  \file     ExportSeamDataCommand.h
  \author   Tody
  ExportSeamDataCommand definition.
  \date     2016/02/27
*/

#ifndef EXPORTSEAMDATACOMMAND_H
#define EXPORTSEAMDATACOMMAND_H

#include "BaseCommand.h"

//! ExportSeamDataCommand implementation.
class ExportSeamDataCommand: public BaseCommand
{
public :
    //! Constructor.
    ExportSeamDataCommand ( Scene* scene, const QString& outputFile = "" )
        : BaseCommand ( "Export Seam Data", scene ), _outputFile ( outputFile )
    {}

    //! Destructor.
    virtual ~ExportSeamDataCommand() {}

    void doImp ();

private:
    QString _outputFile;
};

#endif

