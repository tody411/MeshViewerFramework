
/*!
\file     ShaderProgram.h
\author   Tody
ShaderProgram definition.
\date     2014/12/10
*/

#ifndef BASESHADERPROGRAM_H
#define BASESHADERPROGRAM_H

#include <QGLShaderProgram>
#include <QObject>


//! ShaderProgram implementation.
class ShaderProgram : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    ShaderProgram ( QObject* parent = nullptr )
        : QObject ( parent )
    {}

    //! Destructor.
    virtual ~ShaderProgram() {}

public slots:
    virtual void init() {}

public:
    void linkShaders ( const QString& vertexShader, const QString& fragmentShader );

    void bind()
    {
        if ( !isLinked() )
        {
            init();
        }
        _program.bind();
    }

    void release()
    {
        _program.release();
    }

    bool isLinked()
    {
        return _program.isLinked();
    }

    template <typename AttrType>
    void setUniformValue ( const QString& name, AttrType value )
    {
        int location = _program.uniformLocation ( name );
        _program.setUniformValue ( location, value );
    }

protected:
    QGLShaderProgram _program;

    QString _vertexShaderName;
    QString _fragmentShaderName;
};

#endif

