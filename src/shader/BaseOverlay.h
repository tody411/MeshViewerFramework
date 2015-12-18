
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
    BaseOverlay ( const QString& name, Scene* scene, bool show = true )
        : _name ( name ), _scene ( scene ), _isShow ( show )
    {}

    //! Destructor.
    virtual ~BaseOverlay() {}

    //! Out Name.
    const QString name() { return _name;}

    void setScene ( Scene* scene )
    {
        _scene = scene;
    }

    bool isShow() const
    {
        return _isShow;
    }

    void setIsShow ( bool isShow )
    {
        _isShow = isShow;
    }

    void renderSceneOverlay()
    {
        if ( _scene == nullptr || !_isShow )
        {
            return;
        }

        renderSceneOverlayImp();
    }

    void renderViewOverlay()
    {
        if ( _scene == nullptr || !_isShow )
        {
            return;
        }

        renderViewOverlayImp();
    }

    void renderPainter ( QPainter* painter )
    {
        if ( _scene == nullptr || !_isShow )
        {
            return;
        }

        renderPainterImp ( painter );
    }

protected:
    virtual void renderSceneOverlayImp() {}

    virtual void renderViewOverlayImp() {}

    virtual void renderPainterImp ( QPainter* painter ) {}

protected:
    QString    _name;
    Scene*    _scene;
    bool        _isShow;
};

#endif

