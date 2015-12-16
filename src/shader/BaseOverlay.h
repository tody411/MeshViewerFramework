
/*!
  \file     BaseOverlay.h
  \author   Tody
  BaseOverlay definition.
  \date     2015/12/16
*/

#ifndef BASEOVERLAY_H
#define BASEOVERLAY_H

#include <QString>
#include <QPainter>

#include "Scene.h"

//! BaseOverlay implementation.
class BaseOverlay
{
public :
    //! Constructor.
    BaseOverlay ( const QString& name, Scene* scene )
        : _name ( name ), _scene ( scene )
    {}

    //! Destructor.
    virtual ~BaseOverlay() {}

    //! Out Name.
    const QString name() { return _name;}

    void setScene ( Scene* scene )
    {
        _scene = scene;
    }

    void renderGL()
    {
        if ( _scene == nullptr )
        {
            return;
        }

        renderGLImp();
    }

    void renderPainter ( QPainter* painter )
    {
        if ( _scene == nullptr )
        {
            return;
        }

        renderPainterImp ( painter );
    }

protected:
    virtual void renderGLImp() {}

    virtual void renderPainterImp ( QPainter* painter ) {}

protected:
    QString    _name;
    Scene*    _scene;
};

#endif

