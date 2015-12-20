
/*!
  \file     RenderWindowCommand.cpp
  \author       Tody
  RenderWindowCommand definition.
  date      2015/12/20
*/

#include "RenderWindowCommand.h"

#include <QFileDialog>

void RenderWindowCommand::doImp ()
{
    if ( _outputFile == "" )
    {
        _outputFile = QFileDialog::getSaveFileName ( nullptr,
                      "Save Screen Shot", QString(),
                      "Image File (*.png *.bmp *.tiff)" );
    }

    if ( _outputFile == "" ) return;

    _win->renderScreenShot ( _outputFile ) ;

    _outputFile = "";
}