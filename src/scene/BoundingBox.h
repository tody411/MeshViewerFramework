
/*!
  \file     BoundingBox.h
  \author   Tody
  BoundingBox definition.
  \date     2015/12/15
*/

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QString>

#include <Eigen/Dense>

#include "MeshData.h"



//! BoundingBox implementation.
class BoundingBox
{
public :
    //! Constructor.
    BoundingBox()
    {
        clear();
    }

    //! Constructor.
    BoundingBox ( const BoundingBox& bb )
    {
        _min = bb._min;
        _max = bb._max;
    }

    //! Destructor.
    virtual ~BoundingBox() {}

    void clear()
    {
        float fLarge = 1e6;
        _min = Eigen::Vector3f ( fLarge, fLarge, fLarge );
        _max = Eigen::Vector3f ( -fLarge, -fLarge, -fLarge );
    }

    //! Expand the bounding box to include the given point.
    void expand ( const Eigen::Vector3f& p );

    //! Expand the bounding box to include the given mesh.
    void expand ( const MeshData& mesh );

    //! Returns the minimum point for the bounding box.
    const Eigen::Vector3f min() const { return _min;}

    //! Returns the minimum point for the bounding box.
    const Eigen::Vector3f max() const { return _max;}

    //! Returns the center of the bounding box.
    const Eigen::Vector3f center() const { return 0.5 * ( _max + _min );}

    //! Return the width of the bounding box.
    float width() const
    {
        return ( _max - _min ) ( 0 );
    }

    //! Return the height of the bounding box.
    float height() const
    {
        return ( _max - _min ) ( 1 );
    }

    //! Return the depth of the bounding box.
    float depth() const
    {
        return ( _max - _min ) ( 2 );
    }

    //! Return the size of the bounding box.
    float size() const
    {
        return ( _max - _min ).norm();
    }

    void focusGL();

    const QString dump()
    {
        QString log = "";
        log += QString ( "Min: (%1 %2 %3)" ).arg ( _min ( 0 ) ).arg ( _min ( 1 ) ).arg ( _min ( 2 ) );
        log += QString ( "Max: (%1 %2 %3)" ).arg ( _max ( 0 ) ).arg ( _max ( 1 ) ).arg ( _max ( 2 ) );
        log += QString ( "size: %1" ).arg ( size() );
        return log;
    }

private:
    Eigen::Vector3f _min;
    Eigen::Vector3f _max;



};

#endif

