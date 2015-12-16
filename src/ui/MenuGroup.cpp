
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
    QAction* commandAction = new QAction ( command->name(), nullptr );
    connect ( commandAction, &QAction::triggered, command, &BaseCommand::doSlot );
    addAction ( commandAction );
}