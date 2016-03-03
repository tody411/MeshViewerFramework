
//! MenuGroup definition.
/*!
  \file     MenuGroup.h
  \author   Tody
  \date     2015/12/16
*/

#ifndef COMMANDMENUE_H
#define COMMANDMENUE_H

#include <QMenu>
#include <QAction>

#include "BaseCommand.h"
#include "OverlayCommand.h"

class QDockWidget;

//! MenuGroup implementation.
class MenuGroup : public QMenu
{
    Q_OBJECT
public :
    //! Constructor.
    MenuGroup ( const QString& name, QWidget* parent = nullptr, QDockWidget* toolDock = nullptr )
        : _name ( name ), QMenu ( name, parent ), _toolDock ( toolDock )
    {
    }

    //! Destructor.
    virtual ~MenuGroup() {}

    //! Add command to the menu group.
    void addCommand ( BaseCommand* command );

    //! Add overlay command.
    void addOverlayCommand ( OverlayCommand* command );

private:
    //! Menu group name.
    QString _name;

    //! Tool UI.
    QDockWidget* _toolDock;
};

#endif

