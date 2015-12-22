
/*!
  \file     SetProjectCommand.cpp
  \author       Tody
  SetProjectCommand definition.
  date      2015/12/22
*/

#include "SetProjectCommand.h"


#include <QApplication>
#include <QFileDialog>

void SetProjectCommand::doImp ()
{
    if ( _inputDir == "" )
    {
        _inputDir = QFileDialog::getExistingDirectory ( nullptr,
                    "Set Project Directory", QString() );
    }

    if ( _inputDir == "" ) return;

    _scene->project()->setProject ( _inputDir );

    _inputDir = "";
}
