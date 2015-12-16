
/*!
  \file     BoundingBox.h
  \author   Tody
  BoundingBox definition.
  \date     2015/12/15
*/

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <Eigen/Dense>
#include "MeshData.h"

#include <QString>

//! BoundingBox implementation.
class BoundingBox
{
public :
    //! Constructor.
    BoundingBox()
    {
        clear();
    }

    //! Destructor.
    virtual ~BoundingBox() {}

    void clear()
    {
        float fLarge = 1e6;
        _pMin = Eigen::Vector3f ( fLarge, fLarge, fLarge );
        _pMax = Eigen::Vector3f ( -fLarge, -fLarge, -fLarge );
    }

    //! Add point to the bounding box.
    void addPoint ( const Eigen::Vector3f& p );

    //! Add mesh to the bounding box.
    void addMesh ( const MeshData& mesh );

    //! Get min xyz of the bounding box.
    const Eigen::Vector3f pMin() const { return _pMin;}

    //! Get max xyz of the bounding box.
    const Eigen::Vector3f pMax() const { return _pMax;}

    //! Get mean xyz of the bounding box.
    const Eigen::Vector3f pMean() const { return 0.5 * ( _pMax + _pMin );}

    float range()
    {
        return ( _pMax - _pMin ).norm();
    }

    const QString dump()
    {
        QString log = "";
        log += QString ( "Min: (%1 %2 %3)" ).arg ( _pMin ( 0 ) ).arg ( _pMin ( 1 ) ).arg ( _pMin ( 2 ) );
        log += QString ( "Max: (%1 %2 %3)" ).arg ( _pMax ( 0 ) ).arg ( _pMax ( 1 ) ).arg ( _pMax ( 2 ) );
        log += QString ( "Range: %1" ).arg ( range() );
        return log;
    }

private:
    Eigen::Vector3f _pMin;
    Eigen::Vector3f _pMax;



};

#endif

