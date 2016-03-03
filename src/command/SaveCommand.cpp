
//! SaveCommand definition.
/*!
  \file     SaveCommand.cpp
  \author       Tody
  \date     2015/12/16
*/

#include "SaveCommand.h"

#include <QFileDialog>

void SaveCommand::doImp ()
{
    if ( _outputFile == "" )
    {
        QFileDialog().setDirectory ( _scene->project()->modelDir() );
        _outputFile = QFileDialog::getSaveFileName ( nullptr,
                      "Save 3D Mesh File", QString(),
                      "Mesh File (*.obj *.off *.ply)" );
    }

    if ( _outputFile == "" ) return;

    _scene->saveMesh ( _outputFile );

    _outputFile = "";
}