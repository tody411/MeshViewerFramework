
/*!
  \file     SelectTool.h
  \author   Tody
  SelectTool definition.
  \date     2015/12/18
*/

#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "BaseTool.h"

#include "PointOnMesh.h"

//! SelectTool implementation.
class SelectTool : public BaseTool
{
public :
    //! Constructor.
    SelectTool ( Scene* scene, ModelView* view, QObject* parent = nullptr )
        : BaseTool ( "Select Tool", scene, view, parent )
    {}

    //! Destructor.
    virtual ~SelectTool() {}

    void mousePressEvent ( QMouseEvent* event );

    void keyPressEvent ( QKeyEvent* event );

    void renderSceneOverlay();

private:
    PointOnFace _intersectedPoint;


};

#endif

