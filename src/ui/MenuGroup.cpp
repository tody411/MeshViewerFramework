
//! MenuGroup definition.
/*!
  \file     MenuGroup.cpp
  \author       Tody
  \date     2015/12/16
*/

#include "MenuGroup.h"

#include <QObject>

void MenuGroup::addCommand ( BaseCommand* command )
{
    command->setToolDock ( _toolDock );

    QAction* commandAction = new QAction ( command->name(), nullptr );
    connect ( commandAction, &QAction::triggered, command, &BaseCommand::actionSlot );
    addAction ( commandAction );
}

void MenuGroup::addOverlayCommand ( OverlayCommand* command )
{
    QAction* commandAction = new QAction ( command->name(), nullptr );
    commandAction->setCheckable ( true );
    commandAction->setChecked ( command->isShow() );
    connect ( commandAction, &QAction::toggled, command, &OverlayCommand::toggeldSlot );
    addAction ( commandAction );
}