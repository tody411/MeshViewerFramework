
//! BaseCommand definition.
/*!
  \file     BaseCommand.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <QString>
#include <QElapsedTimer>

#include "Scene.h"

#include "SceneParameters.h"
#include "CommandParameterUI.h"

//! BaseCommand implementation.
class BaseCommand : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    BaseCommand ( const QString& name, Scene* scene )
        :
        _scene ( scene ), _name ( name ), _isInteractive ( false )
    {}

    //! Destructor.
    virtual ~BaseCommand() {}

    const QString name()
    {
        return _name;
    }

public slots:
    void actionSlot()
    {
        if ( _scene->empty() ) return;

        if ( _params.empty() )
        {
            doSlot();
        }

        else
        {
            setupImp() ;
            CommandParameterUI* paramUI = new CommandParameterUI ( _name, _params );
            paramUI->show();

            connect ( paramUI, &CommandParameterUI::editFinished, this, &BaseCommand::doSlot );

            if ( _isInteractive )
            {
                connect ( paramUI, &CommandParameterUI::paramUpdated, this, &BaseCommand::doSlot );
            }
        }
    }

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

private slots:
    void doSlot()
    {
        _inputInfo = _params.str();

        QElapsedTimer timer;
        timer.start();

        doImp();

        _performanceInfo = QString ( "%1 sec" ).arg ( timer.elapsed() / 1000.0f );

        _scene->showMessage ( str() );
    }

protected:
    virtual void setupImp() {}

    virtual void doImp () {}

    //! Set interactive mode.
    void setInteractive ( bool isInteractive )
    {
        _isInteractive = isInteractive;
    }

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

    //! Command parameters.
    SceneParameters _params;

    //! Interactive mode.
    bool _isInteractive;
};

#endif

