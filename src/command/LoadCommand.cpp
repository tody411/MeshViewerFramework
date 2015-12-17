
//! LoadCommand definition.
/*!
  \file     LoadCommand.cpp
  \author       Tody
  \date     2015/12/16
*/

#include "LoadCommand.h"

#include <QFileDialog>

void LoadCommand::doImp ()
{
    if ( _inputFile == "" )
    {
        _inputFile = QFileDialog::getOpenFileName ( nullptr,
                     "Open 3D Mesh File", QString(), "Mesh File (*.obj *.off *.ply)" );
    }

    if ( _inputFile == "" ) return;

    _scene->loadMesh ( _inputFile );

    _inputFile = "";
}