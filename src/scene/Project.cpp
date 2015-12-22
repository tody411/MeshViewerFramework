
/*!
  \file     Project.cpp
  \author       Tody
  Project definition.
  date      2015/12/22
*/

#include "Project.h"

#include <QApplication>

void Project::setDefaultProject()
{
    QDir appDir = QApplication::applicationDirPath();
    _projectDir = QDir ( appDir.absoluteFilePath ( "../" ) );
}

void Project::setProject ( const QString& project )
{
    QDir projectDir ( project );

    if ( projectDir.exists() )
    {
        _projectDir = QDir ( project ) ;
    }
}