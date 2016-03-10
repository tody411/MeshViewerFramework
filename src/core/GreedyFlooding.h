
//! GreedyFlooding definition.
/*!
  \file     GreedyFlooding.h
  \author   Tody
  \date     2016/03/10
*/

#ifndef GREEDYFLOODING_H
#define GREEDYFLOODING_H

#include "Eigen/Dense"

#include "Mesh.h"

//! GreedyFlooding implementation.
class GreedyFlooding
{
public :
    //! Constructor.
    GreedyFlooding ( Mesh* mesh )
        : _mesh ( mesh ), _tol ( 0.1 )
    {}

    //! Destructor.
    virtual ~GreedyFlooding() {}

    //! Set Tolerance.
    void setTolerance ( double tol ) { _tol = tol;}

    void flood ( Eigen::VectorXi& clusterIDs );

    void floodSeed ( int seedFaceID, int clusterID,  Eigen::VectorXi& clusterIDs );

private:
    double _tol;
    Mesh* _mesh;
};

#endif
