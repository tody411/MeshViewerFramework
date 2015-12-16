/*!
    \file       Logger.h
    \author     Tody
    Logger definition.
    \date       2013/10/05
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <QString>
#include <QObject>
#include <QMap>

//! Logger implementation.
class Logger : public QObject
{
    Q_OBJECT

private:
    //! Constructor.
    Logger ( const QString& logname );

public:
    //! Destructor.
    virtual ~Logger() {}

    static Logger* getLogger ( const QString& logname );

    static Logger* main();

    void setIndent ( int indent )
    {
        _indent = indent;
    }

    void block ( const QString& message );

    void info ( const QString& message );

    void info ( const QString& label, const QString& message );

    void debug ( const QString& message );

    void debug ( const QString& label, const QString& message );

    void error ( const QString& message );

signals:
    void logging ( const QString& message );

private:
    QString formatLogMessage ( const QString& message );
    QString formatLogMessage ( const QString& label, const QString& message );

private:
    QString     _logname;
    int         _indent;
    static QMap < QString, Logger* > _logMap;
};

#endif