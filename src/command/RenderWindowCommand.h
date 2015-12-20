
/*!
  \file     RenderWindowCommand.h
  \author   Tody
  RenderWindowCommand definition.
  \date     2015/12/20
*/

#ifndef RENDERWINDOWCOMMAND_H
#define RENDERWINDOWCOMMAND_H

#include "BaseCommand.h"

#include "MainWindow.h"

//! RenderWindowCommand implementation.
class RenderWindowCommand : public BaseCommand
{
public :
    //! Constructor.
    RenderWindowCommand ( Scene* scene, MainWindow* win,  const QString& outputFile = ""  )
        : BaseCommand ( "Render Current Window", scene ), _win ( win ), _outputFile ( outputFile )
    {}

    //! Destructor.
    virtual ~RenderWindowCommand() {}

    void doImp ();

private:
    MainWindow* _win;
    QString _outputFile;



};


#endif

