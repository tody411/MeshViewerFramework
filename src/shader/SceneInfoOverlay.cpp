
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

    painter->setPen ( QColor ( 20, 15, 100 ) );

    if ( _modelData == NULL ) return;
    if ( _modelData->model() == NULL ) return;


    text += QString ( "  Num Textures  : %1\n" ).arg ( _modelData->getNumTextures() );
    text += QString ( "  Num Parts     : %1\n" ).arg ( _modelData->getPartsDataCount() );
    text += QString ( "  Num Draw Data : %1\n" ).arg ( _modelData->getDrawDataCount() );

    painter->drawText ( QRectF ( x, y, text_width, text_height ), text );

    text = QString ( "%1" ).arg ( _renderer->name() );

    painter->drawText ( QRectF ( painter->window().width() - 200, y, text_width - 10, text_height ), Qt::AlignRight, text );

    text = QString ( "%1 fps" ).arg ( _renderer->fps() );
    painter->drawText ( QRectF ( painter->window().width() - 200,  painter->window().height() - 30, text_width - 10, text_height ), Qt::AlignRight, text );
}
