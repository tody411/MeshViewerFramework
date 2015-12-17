
/*!
  \file     SceneInfoOverlay.cpp
  \author       Tody
  SceneInfoOverlay definition.
  date      2015/12/16
*/

#include "SceneInfoOverlay.h"

void SceneInfoOverlay::renderPainterImp ( QPainter* painter )
{
    painter->setRenderHint ( QPainter::Antialiasing );
    painter->setFont ( QFont ( "Arial", 13, QFont::Bold )  );

    QString text = "Scene Info:\n";

    int x = 10;
    int xTab = 20;
    int y = 10;
    int text_width = 200;
    int text_height = 100;

    painter->setPen ( QColor ( 230, 230, 240 ) );

    Mesh* mesh = _scene->mesh();

    BoundingBox bb = _scene->boundingBox();

    text += QString ( "  Num Vertices  : %1\n" ).arg ( mesh->numVertices() );
    text += QString ( "  Num Edges     : %1\n" ).arg ( mesh->numEdges() );
    text += QString ( "  Num Faces     : %1\n" ).arg ( mesh->numFaces() );

    text += QString ( "  Bounding Box  : (%1, %2, %3)\n" ).arg ( bb.min() ( 0 ) ).arg ( bb.min() ( 1 ) ).arg ( bb.min() ( 2 ) );

    painter->drawText ( QRectF ( x, y, text_width, text_height ), text );

}
