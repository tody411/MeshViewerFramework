
/*!
  \file     RenderCommand.cpp
  \author       Tody
  RenderCommand definition.
  date      2015/12/16
*/

#include "RenderCommand.h"

#include <QFileDialog>

void RenderCommand::doImp ()
{
    if ( _outputFile == "" )
    {
        _outputFile = QFileDialog::getSaveFileName ( nullptr,
                      "Save Screen Shot", QString(),
                      "Image File (*.png *.bmp *.tiff)" );
    }

    if ( _outputFile == "" ) return;

    _view->renderScreenShot ( _outputFile ) ;

    _outputFile = "";
}