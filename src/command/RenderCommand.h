
/*!
  \file     RenderCommand.h
  \author   Tody
  RenderCommand definition.
  \date     2015/12/16
*/

#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

#include "BaseCommand.h"

#include "ModelView.h"

//! RenderCommand implementation.
class RenderCommand : public BaseCommand
{
public :
    //! Constructor.
    RenderCommand ( Scene* scene, ModelView* view,  const QString& outputFile = ""  )
        : BaseCommand ( "Render Current Screen", scene ), _view ( view ), _outputFile ( outputFile )
    {}

    //! Destructor.
    virtual ~RenderCommand() {}

    void doImp ();

private:
    ModelView* _view;
    QString _outputFile;



};

#endif

