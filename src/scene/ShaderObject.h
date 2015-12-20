
/*!
  \file     ShaderObject.h
  \author   Tody
  ShaderObject definition.
  \date     2015/12/20
*/

#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include "SceneObject.h"

#include "ShaderProgram.h"

//! ShaderObject implementation.
class ShaderObject: public SceneObject
{
    Q_OBJECT
public :

    //! Constructor.
    ShaderObject ( Scene* scene )
        : SceneObject ( scene )
    {}

    //! Destructor.
    virtual ~ShaderObject() {}

    void linkShaders ( const QString& vertexShader, const QString& fragmentShader )
    {
        _shader.linkShaders ( vertexShader, fragmentShader );
        emit updated();
    }

    void bind()
    {
        _shader.bind();
    }

    void release()
    {
        _shader.release();
    }

    bool isLinked()
    {
        return _shader.isLinked();
    }

    template <typename AttrType>
    void setUniformValue ( const QString& name, AttrType value )
    {
        _shader.setUniformValue ( name, value );
        emit updated();
    }

private:
    ShaderProgram _shader;
};

#endif

