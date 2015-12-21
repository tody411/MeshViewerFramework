
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
    qDebug() << demoDir();

    //_view->resize ( QSize ( 512, 512 ) );

    Eigen::MatrixXd V0;
    Mesh* mesh = _scene->mesh();
    mesh->points ( V0 );

    BaseCommand* command = new NoiseCommand ( _scene );
    command->doDefault();

    _view->update();

    QString testFilePath = demoDir().absoluteFilePath ( "test.png" );

    _view->renderScreenShot ( testFilePath );

    //mesh->setPoints ( V0 );
}

QDir DemoCommand::demoDir()
{
    QDir appDir = QApplication::applicationDirPath();

    QDir _demoDir ( appDir.absoluteFilePath ( "../images" ) );
    return QDir ( _demoDir.absolutePath() );
}