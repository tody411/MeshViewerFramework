
//! LoadCommand definition.
/*!
  \file     LoadCommand.cpp
  \author       Tody
  \date     2015/12/16
*/

#include "LoadCommand.h"

#include "NormalizeMeshCommand.h"

#include <QApplication>
#include <QFileDialog>

void LoadCommand::doImp ()
{
    if ( _inputFile == "" )
    {
        QFileDialog().setDirectory ( _modelDir );

        _inputFile = QFileDialog::getOpenFileName ( nullptr,
                     "Open 3D Mesh File", QString(), "Mesh File (*.obj *.off *.ply)" );
    }

    if ( _inputFile == "" ) return;

    _scene->loadMesh ( _inputFile );

    _modelDir = QFileInfo ( _inputFile ).absoluteDir();

    _inputFile = "";
}


void LoadCommand::defaultModelDir()
{
    _modelDir = _scene->project()->modelDir();
}