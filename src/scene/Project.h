
/*!
  \file     Project.h
  \author   Tody
  Project definition.
  \date     2015/12/22
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <QDir>

//! Project implementation.
class Project
{
public :
    //! Constructor.
    Project()
    {
        setDefaultProject();
    }

    //! Destructor.
    virtual ~Project() {}

    void setDefaultProject();

    void setProject ( const QString& project );

    const QDir projectDir() const
    {
        return _projectDir;
    }

    const QDir modelDir() const
    {
        return _projectDir.absoluteFilePath ( "models" );
    }

    const QDir dataDir() const
    {
        return _projectDir.absoluteFilePath ( "data" );
    }

    const QDir imageDir() const
    {
        return _projectDir.absoluteFilePath ( "images" );
    }

    const QDir sceneDir() const
    {
        return _projectDir.absoluteFilePath ( "scenes" );
    }

private:
    QDir _projectDir;


};

#endif

