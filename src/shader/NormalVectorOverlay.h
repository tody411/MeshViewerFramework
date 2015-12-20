
/*!
  \file     NormalVectorOverlay.h
  \author   Tody
  NormalVectorOverlay definition.
  \date     2015/12/20
*/

#ifndef NORMALVECTOROVERLAY_H
#define NORMALVECTOROVERLAY_H

#include "BaseOverlay.h"

//! NormalVectorOverlay implementation.
class NormalVectorOverlay : public BaseOverlay
{
public :
    //! Constructor.
    NormalVectorOverlay ( Scene* scene )
        : BaseOverlay ( "Show Normals", scene, false  )
    {
    }

    //! Destructor.
    virtual ~NormalVectorOverlay() {}

protected:
    void renderSceneOverlayImp();


};

#endif

