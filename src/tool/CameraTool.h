
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

#include "BaseTool.h"

#include "Camera.h"

//! CameraTool implementation.
class CameraTool : public BaseTool
{
    Q_OBJECT
public :
    //! Constructor.
    CameraTool ( Scene* scene, ModelView* view, QObject* parent = nullptr )
        : BaseTool ( "Camera Tool", scene, view, parent )
    {
        reset();
    }

    //! Destructor.
    virtual ~CameraTool() {}

    void reset();

    //-----------------------
    //  Mouse events.
    //=======================
    void mousePressEvent ( QMouseEvent* event );
    void mouseMoveEvent ( QMouseEvent* event );

    void wheelEvent ( QWheelEvent* event );

    //-----------------------
    //  Key events.
    //=======================
    void keyPressEvent ( QKeyEvent* event );

private slots:
    //! Animate camera.
    void animate();

private:
    Camera* camera();

    //! Return the current mouse movement.
    const Eigen::Vector2d mouseMovement ( QMouseEvent* event );

    void translateDrag ( QMouseEvent* event );

    void rotateDrag ( QMouseEvent* event );


private:
    double _scalingFactor;
    //double _scale;

    double _rotationFactor;
    //Eigen::Vector3f _rotation;

    double _translateFactor;
    //Eigen::Vector3f _translation;

    Eigen::Vector2d _presPos;

    double _speed;

};

#endif

