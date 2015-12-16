
//! BaseCommand definition.
/*!
  \file     BaseCommand.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <QString>

#include "Scene.h"

#include "CommandParameters.h"

//! BaseCommand implementation.
class BaseCommand : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    BaseCommand ( const QString& name, Scene* scene )
        :
        _scene ( scene ), _name ( name )
    {}

    //! Destructor.
    virtual ~BaseCommand() {}

    const QString name()
    {
        return _name;
    }

public slots:
    void doSlot() {}

    //! Return the command information.
    const QString str() const
    {
        QString info = _name;

        if ( _inputInfo != "" )
        {
            info += QString ( " (%1)" ).arg ( _inputInfo );
        }

        if ( _outputInfo != "" )
        {
            info += QString ( " => %1" ).arg ( _outputInfo );
        }

        if ( _performanceInfo != "" )
        {
            info += QString ( ": %1" ).arg ( _performanceInfo );
        }

        return info;
    }

protected:
    void doIt ( const CommandParameters& parameters );

protected:
    //! Command name.
    QString     _name;

    //! Target scene.
    Scene*   _scene;

    //! Input information.
    QString _inputInfo;

    //! Output information.
    QString _outputInfo;

    //! Perfomance info.
    QString _performanceInfo;
};

#endif

