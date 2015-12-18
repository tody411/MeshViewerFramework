
/*!
  \file     CoordinateSystemOverlay.h
  \author   Tody
  CoordinateSystemOverlay definition.
  \date     2015/12/17
*/

#ifndef COORDINATESYSTEMOVERLAY_H
#define COORDINATESYSTEMOVERLAY_H

#include "BaseOverlay.h"

#include "ModelView.h"
#include "CameraTool.h"

//! CoordinateSystemOverlay implementation.
class CoordinateSystemOverlay  : public BaseOverlay
{
public :
    //! Constructor.
    CoordinateSystemOverlay ( Scene* scene, CameraTool* cameraTool, ModelView* view )
        : BaseOverlay ( "CoordinateSystem", scene ), _cameraTool ( cameraTool ), _view ( view )
    {}

    //! Destructor.
    virtual ~CoordinateSystemOverlay() {}

    void renderViewOverlayImp();

private:
    CameraTool* _cameraTool;

    ModelView* _view;


};

#endif

