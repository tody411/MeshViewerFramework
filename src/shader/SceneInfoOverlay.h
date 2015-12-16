
/*!
  \file     SceneInfoOverlay.h
  \author   Tody
  SceneInfoOverlay definition.
  \date     2015/12/16
*/

#ifndef SCENEINFOOVERLAY_H
#define SCENEINFOOVERLAY_H

#include "BaseOverlay.h"

//! SceneInfoOverlay implementation.
class SceneInfoOverlay : public BaseOverlay
{
public :
    //! Constructor.
    SceneInfoOverlay()
        : BaseOverlay ( "Scene Information" )
    {}

    //! Destructor.
    virtual ~SceneInfoOverlay() {}

    void renderPainterImp ( QPainter* painter );

private:

// inputs.


// outputs.



};

#endif

