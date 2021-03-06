
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
#include <QDockWidget>

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
        _scene ( scene ), _name ( name ), _isInteractive ( false ), _isCheckSceneEmtpy ( true ), _toolDock ( nullptr )
    {}

    //! Destructor.
    virtual ~BaseCommand() {}

    const QString name()
    {
        return _name;
    }

    void setToolDock ( QDockWidget* toolDock )
    {
        _toolDock = toolDock;
    }

public slots:
    void actionSlot()
    {
        if ( _isCheckSceneEmtpy && ( _scene->empty() ) ) return;

        if ( _params.empty() )
        {
            setupImp() ;
            CommandParameterUI* paramUI = new CommandParameterUI ( _name, _params );
            if ( _toolDock )
            {
                _toolDock->setWidget ( paramUI );
                _toolDock->setWindowTitle ( _name );
            }

            connect ( paramUI, &CommandParameterUI::editFinished, this, &BaseCommand::doSlot );
            doSlot();
        }

        else
        {
            setupImp() ;

            CommandParameterUI* paramUI = new CommandParameterUI ( _name, _params );
            if ( _toolDock )
            {
                _toolDock->setWidget ( paramUI );
                _toolDock->setWindowTitle ( _name );
            }

            connect ( paramUI, &CommandParameterUI::editFinished, this, &BaseCommand::doSlot );

            if ( _isInteractive )
            {
                connect ( paramUI, &CommandParameterUI::paramUpdated, this, &BaseCommand::doSlot );
            }
        }
    }

    void doDefault()
    {
        setupImp() ;
        doSlot();
    }

    void doSlot()
    {
        _inputInfo = _params.str();

        QElapsedTimer timer;
        timer.start();

        doImp();

        _performanceInfo = QString ( "%1 sec" ).arg ( timer.elapsed() / 1000.0f );

        _scene->showMessage ( str() );
    }

public:
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
    virtual void setupImp() {}

    virtual void doImp () {}

//! Set interactive mode.
    void setInteractive ( bool isInteractive )
    {
        _isInteractive = isInteractive;
    }

    void setIsCheckSceneEmpty ( bool isCheckSceneEmpty )
    {
        _isCheckSceneEmtpy = isCheckSceneEmpty;
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

//! Checking scene empty.
    bool _isCheckSceneEmtpy;

//! Tool UI.
    QDockWidget* _toolDock;
};

#endif

