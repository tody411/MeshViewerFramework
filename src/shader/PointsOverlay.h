
/*!
  \file     PointsOverlay.h
  \author   Tody
  PointsOverlay definition.
  \date     2015/12/17
*/

#ifndef POINTSOVERLAY_H
#define POINTSOVERLAY_H

#include "BaseOverlay.h"

//! PointsOverlay implementation.
class PointsOverlay : public BaseOverlay
{
public :
    //! Constructor.
    PointsOverlay ( Scene* scene )
        : BaseOverlay ( "Show Points", scene, false  )
    {
    }

    //! Destructor.
    virtual ~PointsOverlay() {}

protected:
    void renderSceneOverlayImp();



};

#endif

