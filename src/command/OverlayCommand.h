
/*!
  \file     OverlayCommand.h
  \author   Tody
  OverlayCommand definition.
  \date     2015/12/17
*/

#ifndef OVERLAYCOMMAND_H
#define OVERLAYCOMMAND_H

#include "BaseOverlay.h"

//! OverlayCommand implementation.
class OverlayCommand: public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    OverlayCommand ( BaseOverlay* overlay )
        : _overlay ( overlay )
    {}

    //! Destructor.
    virtual ~OverlayCommand() {}

    const QString name() const
    {
        return _overlay->name();
    }

    bool isShow() const
    {
        return _overlay->isShow();
    }

public slots:
    void toggeldSlot ( bool checked )
    {
        _overlay->setIsShow ( checked );
    }

private:
    BaseOverlay* _overlay;



};

#endif

