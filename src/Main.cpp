#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>

#include "MainWindow.h"
#include "Logger.h"

int main ( int argc, char* argv[] )
{
    QApplication app ( argc, argv );

    app.setApplicationName ( "SimpleMeshViewer" );
    app.setApplicationVersion ( "1.0" );

    QCommandLineParser parser;
    parser.setApplicationDescription ( "Simple Mesh Viewer." );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument ( "input", "Input Mesh file path."  );

    parser.process ( app );
    const QStringList args = parser.positionalArguments();


    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();

    if ( args.length() > 0 )
    {
        QFileInfo inputInfo ( args[0] );

        if ( inputInfo.isFile() )
        {
            QString inputFile ( inputInfo.absoluteFilePath() );

            Logger::getLogger ( "SimpleMeshViewer" )->info ( inputFile );
            Logger::getLogger ( "SimpleMeshViewer" )->setIndent ( 1 );

        }

        else
        {
            Logger::getLogger ( "SimpleMeshViewer" )->error ( "Input should be file." );
        }
    }

    int rc =  app.exec();

    mainWindow->release();
    return rc;
}