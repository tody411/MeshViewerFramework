
/*!
  \file     CameraTool.h
  \author   Tody
  CameraTool definition.
  \date     2015/12/15
*/

#ifndef CAMERATOOL_H
#define CAMERATOOL_H

#include <QWidget>
#include <QVector2D>

//! CameraTool implementation.
class CameraTool : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    CameraTool ( QObject* parent = nullptr )
        : QObject ( parent )
    {
        reset();
    }

    //! Destructor.
    virtual ~CameraTool() {}

    void reset();

    void gl();

    void mousePressEvent ( QMouseEvent* event );
    void mouseMoveEvent ( QMouseEvent* event );
    void mouseReleaseEvent ( QMouseEvent* event );
    void wheelEvent ( QWheelEvent* event );

    void keyPressEvent ( QKeyEvent* event );
    void keyReleaseEvent ( QKeyEvent* event );

private:
    const QVector2D mousePosition ( QMouseEvent* event );
    const QVector2D mouseMovement ( QMouseEvent* event );

    void translateDrag ( QMouseEvent* event );

    void rotateDrag ( QMouseEvent* event );


private:
    double _scalingFactor;
    double _scale;

    double _rotationFactor;
    QVector2D _rotation;

    double _translateFactor;
    QVector2D _translation;

    QVector2D _presPos;

    double _speed;



};

#endif

