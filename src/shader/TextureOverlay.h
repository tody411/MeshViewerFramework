
/*!
  \file     TextureOverlay.h
  \author   Tody
  TextureOverlay definition.
  \date     2016/03/01
*/

#ifndef TEXTUREOVERLAY_H
#define TEXTUREOVERLAY_H

#include "BaseOverlay.h"
#include "ModelView.h"

//! TextureOverlay implementation.
class TextureOverlay : public BaseOverlay
{
public :
    //! Constructor.
    TextureOverlay ( Scene* scene )
        : BaseOverlay ( "Show Texture Coordinates", scene )
    {}

    //! Destructor.
    virtual ~TextureOverlay() {}

    void renderViewOverlayImp();

private:

};

#endif

