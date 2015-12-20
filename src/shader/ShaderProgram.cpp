
/*!
  \file     ShaderProgram.cpp
  \author       Tody
  ShaderProgram definition.
  date      2014/12/10
*/

#include "ShaderProgram.h"
#include <QApplication>
#include <QGLContext>
#include <QDir>
#include <QDebug>

void ShaderProgram::linkShaders ( const QString& vertexShader, const QString& fragmentShader )
{
    _vertexShaderName = vertexShader;
    _fragmentShaderName = fragmentShader;

    QString vertexShaderFilePath = filePath ( vertexShader );
    QString fragmentShaderFilePath = filePath ( fragmentShader );

    _program.removeAllShaders();
    _program.addShaderFromSourceFile ( QGLShader::Vertex, vertexShaderFilePath );
    _program.addShaderFromSourceFile ( QGLShader::Fragment, fragmentShaderFilePath );
    _program.link();
    _program.bind();
}

const QString ShaderProgram::filePath ( const QString& name )
{
    QDir appDir = QApplication::applicationDirPath();

    QDir shaderDir ( appDir.absoluteFilePath ( "shaders" ) );

    QString file = shaderDir.absoluteFilePath ( name );
    return file;
}