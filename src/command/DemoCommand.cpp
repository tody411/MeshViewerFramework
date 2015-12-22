
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

#include "Commands.h"

void DemoCommand::doImp ()
{


    //_view->resize ( QSize ( 512, 512 ) );

    Eigen::MatrixXd V0;
    Mesh* mesh = _scene->mesh();
    mesh->points ( V0 );

    QList<BaseCommand*> commandList;

    commandList.append ( new NoiseCommand ( _scene ) );
    commandList.append ( new LaplacianSmoothingCommand ( _scene ) );
    commandList.append ( new NormalColorCommand ( _scene ) );
    commandList.append ( new NormalShaderCommand ( _scene ) );
    commandList.append ( new ToonShaderCommand ( _scene ) );
    commandList.append ( new NormalKmeansCommand ( _scene ) );

    foreach ( BaseCommand* command, commandList )
    {
        command->doDefault();
        _view->update();

        QString imageName = command->name();
        imageName.remove ( QString ( " " ) );
        QString testFilePath = _scene->project()->imageDir().absoluteFilePath ( QString ( "test/%1.png" ).arg ( imageName ) );
        _view->renderScreenShot ( testFilePath );
        mesh->setPoints ( V0 );

        _scene->shader()->linkShaders ( "SimpleTransform.vert", "LambertShader.frag" );
        _scene->setMeshDisplayMode ( Mesh::DisplayMode::GLSL );
    }

    /*BaseCommand* command = new NoiseCommand ( _scene );
    command->doDefault();

    _view->update();

    QString testFilePath = _scene->project()->imageDir().absoluteFilePath ( "test.png" );

    _view->renderScreenShot ( testFilePath );
    */
    //mesh->setPoints ( V0 );
}
