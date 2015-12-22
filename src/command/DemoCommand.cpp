
/*!
  \file     DemoCommand.cpp
  \author       Tody
  DemoCommand definition.
  date      2015/12/21
*/

#include "DemoCommand.h"

#include <QApplication>
#include <QDebug>
#include <QThread>

#include "NoiseCommand.h"

void DemoCommand::doImp ()
{


    //_view->resize ( QSize ( 512, 512 ) );

    Eigen::MatrixXd V0;
    Mesh* mesh = _scene->mesh();
    mesh->points ( V0 );

    BaseCommand* command = new NoiseCommand ( _scene );
    command->doDefault();

    _view->update();

    QString testFilePath = _scene->project()->imageDir().absoluteFilePath ( "test.png" );

    _view->renderScreenShot ( testFilePath );

    //mesh->setPoints ( V0 );
}
