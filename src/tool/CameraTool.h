
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

#include <Eigen/Dense>

//! CameraTool implementation.
class CameraTool : public QObject
{
    Q_OBJECT
public :
    //! Constructor.
    CameraTool ( QObject* parent = nullptr )
        : QObject ( parent )
    {
        _aspect = 1.0;
        reset();
    }

    //! Destructor.
    virtual ~CameraTool() {}

    void reset();

    void setAspect ( double aspect )
    {
        _aspect = aspect;
    }

    double aspect() const
    {
        return _aspect;
    }

    void gl();

    //! Return the current rotation.
    Eigen::Vector2f rotation() const
    {
        return _rotation;
    }

    //-----------------------
    //  Mouse events.
    //=======================
    void mousePressEvent ( QMouseEvent* event );
    void mouseMoveEvent ( QMouseEvent* event );
    void mouseReleaseEvent ( QMouseEvent* event );
    void wheelEvent ( QWheelEvent* event );

    //-----------------------
    //  Key events.
    //=======================
    void keyPressEvent ( QKeyEvent* event );
    void keyReleaseEvent ( QKeyEvent* event );

private:
    //! Return the current mouse position.
    const Eigen::Vector2f mousePosition ( QMouseEvent* event );

    //! Return the current mouse movement.
    const Eigen::Vector2f mouseMovement ( QMouseEvent* event );

    void translateDrag ( QMouseEvent* event );

    void rotateDrag ( QMouseEvent* event );


private:
    double _aspect;

    double _scalingFactor;
    double _scale;

    double _rotationFactor;
    Eigen::Vector2f _rotation;

    double _translateFactor;
    Eigen::Vector2f _translation;

    Eigen::Vector2f _presPos;

    double _speed;

};

#endif

