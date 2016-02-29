
/*!
  \file     ExportLabelDataCommand.cpp
  \author       Tody
  ExportLabelDataCommand definition.
  date      2016/02/23
*/

#include "ExportLabelDataCommand.h"

#include <QFileDialog>
#include <fstream>

void ExportLabelDataCommand::doImp ()
{
    if ( _outputFile == "" )
    {
        QFileDialog().setDirectory ( _scene->project()->dataDir() );
        _outputFile = QFileDialog::getSaveFileName ( nullptr,
                      "Export Label Data", QString(),
                      "Label Data (*.dat)" );
    }

    if ( _outputFile == "" ) return;

    std::vector<int> faceLabels;
    _scene->labelData()->faceLabelData ( faceLabels );

    std::ofstream  ofs ( _outputFile.toStdString() );

    for ( int i = 0; i < faceLabels.size(); i++ )
    {
        ofs << faceLabels[i] << std::endl;
    }

    _outputFile = "";
}