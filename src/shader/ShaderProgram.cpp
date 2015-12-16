
/*!
  \file     ShaderProgram.cpp
  \author       Tody
  ShaderProgram definition.
  date      2014/12/10
*/

#include "ShaderProgram.h"

#include <QGLContext>

void ShaderProgram::linkShaders ( const QString& vertexShader, const QString& fragmentShader )
{
    _vertexShaderName = vertexShader;
    _fragmentShaderName = fragmentShader;

    QString vertexShaderFilePath = vertexShader;
    QString fragmentShaderFilePath = fragmentShader;

    _program.removeAllShaders();
    _program.addShaderFromSourceFile ( QGLShader::Vertex, vertexShaderFilePath );
    _program.addShaderFromSourceFile ( QGLShader::Fragment, fragmentShaderFilePath );
    _program.link();
    _program.bind();
}