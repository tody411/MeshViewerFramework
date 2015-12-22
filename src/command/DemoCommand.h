
/*!
  \file     DemoCommand.h
  \author   Tody
  DemoCommand definition.
  \date     2015/12/21
*/

#ifndef DEMOCOMMAND_H
#define DEMOCOMMAND_H

#include "BaseCommand.h"

#include <QDir>

#include "ModelView.h"

//! DemoCommand implementation.
class DemoCommand : public BaseCommand
{
public :
    //! Constructor.
    DemoCommand (  Scene* scene, ModelView* view )
        :  BaseCommand ( "Generate Demo Images", scene ), _view ( view )
    {
    }

    //! Destructor.
    virtual ~DemoCommand() {}

    void doImp ();


private:
    ModelView* _view;

};

#endif

