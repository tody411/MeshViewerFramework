/*!
    \file       Logger.cpp
    \author     Tody
    Logger definition.
    date        2013/10/05
*/
#include "Logger.h"
#include <iostream>

QMap < QString, Logger* > Logger::_logMap;

Logger::Logger ( const QString& logname  )
    : _logname ( logname ), _indent ( 0 )
{}

Logger* Logger::getLogger ( const QString& logname )
{
    if ( _logMap.contains ( logname ) )
    {
        return _logMap[logname];
    }

    _logMap[logname] = new Logger ( logname );
    _logMap[logname]->block ( logname );
    return _logMap[logname];
}

Logger* Logger::main()
{
    QString logname ( "main" );
    return getLogger ( logname );
}

void Logger::block ( const QString& message )
{
    std::cout << "==========================" << std::endl;
    std::cout << message.toStdString() << std::endl;
    std::cout << "==========================" << std::endl;
}

void Logger::info ( const QString& label, const QString& messageStr )
{
    QString message = formatLogMessage ( label, messageStr );
    std::cout << message.toStdString() << std::endl;
    emit logging ( message );
}

void Logger::info ( const QString& messageStr )
{
    QString message = formatLogMessage ( messageStr );
    std::cout << message.toStdString() << std::endl;
    emit logging ( message );
}

void Logger::debug ( const QString& messageStr )
{
    QString message = formatLogMessage ( messageStr );
    std::cout << message.toStdString() << std::endl;
    emit logging ( message );
}

void Logger::debug ( const QString& label, const QString& messageStr )
{
    QString message = formatLogMessage ( label, messageStr );
    std::cout << message.toStdString() << std::endl;
    emit logging ( message );
}


void Logger::error ( const QString& messageStr )
{
    QString message = formatLogMessage ( "Error", messageStr );
    std::cout << message.toStdString() << std::endl;
    emit logging ( message );
}

QString Logger::formatLogMessage ( const QString& messageStr )
{
    QString message = messageStr;
    message = message.leftJustified ( _indent * 4 );
    return message;
}

QString Logger::formatLogMessage (  const QString& label, const QString& messageStr )
{
    QString message = QString ( "%1: %2" ).arg ( label ).arg ( messageStr );
    message = message.leftJustified ( _indent * 4 );
    return message;
}