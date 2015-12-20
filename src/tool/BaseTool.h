
/*!
  \file     BaseTool.h
  \author   Tody
  BaseTool definition.
  \date     2015/12/18
*/

#ifndef BASETOOL_H
#define BASETOOL_H

#include <QWidget>

#include <Eigen/Dense>

class Scene;
class ModelView;

//! BaseTool implementation.
class BaseTool  : public QObject
{
public :
    //! Constructor.
    BaseTool ( const QString& name, Scene* scene, ModelView* view, QObject* parent = nullptr )
        : _name ( name ), _scene ( scene ), _view ( view ), QObject ( parent )
    {}

    //! Destructor.
    virtual ~BaseTool() {}

    const QString name() const
    {
        return _name;
    }

    //! Set scene.
    void setScene ( Scene* scene );

    //! Set view.
    void setView ( ModelView* view );

    //! Activate this tool.
    void activate();

    //! Deactivate this tool.
    void deactivate();

    //-----------------------
    //  Mouse events.
    //=======================
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) {}
    virtual void mousePressEvent ( QMouseEvent* event ) ;

    virtual void mouseMoveEvent ( QMouseEvent* event ) {}
    virtual void mouseReleaseEvent ( QMouseEvent* event ) {}
    virtual void wheelEvent ( QWheelEvent* event ) {}

    //-----------------------
    //  Key events.
    //=======================
    virtual void keyPressEvent ( QKeyEvent* event ) {}
    virtual void keyReleaseEvent ( QKeyEvent* event ) {}

    //-----------------------
    //  Overlay.
    //=======================
    virtual void renderSceneOverlay() {}

    virtual void renderViewOverlay() {}

    virtual void renderPainter ( QPainter* painter ) {}


    //! Return the current mouse position.
    const Eigen::Vector2d mousePosition ( QMouseEvent* event );

    //! Unproject the screen postion.
    void unproject ( const Eigen::Vector2d& p, Eigen::Vector3d& pNear,  Eigen::Vector3d& ray );

protected:
    QString _name;

    Scene* _scene;
    ModelView* _view;


};

#endif

