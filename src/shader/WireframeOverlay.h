
/*!
  \file     WireframeOverlay.h
  \author   Tody
  WireframeOverlay definition.
  \date     2015/12/17
*/

#ifndef WIREFRAMEOVERLAY_H
#define WIREFRAMEOVERLAY_H

#include "BaseOverlay.h"

//! WireframeOverlay implementation.
class WireframeOverlay : public BaseOverlay
{
public :
    //! Constructor.
    WireframeOverlay ( Scene* scene )
        : BaseOverlay ( "Show Wireframe", scene, false )
    {
    }

    //! Destructor.
    virtual ~WireframeOverlay() {}

    void renderSceneOverlayImp();

private:

// inputs.


// outputs.



};

#endif

