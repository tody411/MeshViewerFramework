
//! KRegionFlooding definition.
/*!
  \file     KRegionFlooding.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef KREGIONFLOODING_H
#define KREGIONFLOODING_H

#include "Eigen/Dense"
#include "Mesh.h"

//! KRegionFlooding implementation.
class KRegionFlooding
{
public :
    //! Constructor.
    KRegionFlooding (  Mesh* mesh, int numCenters );

    //! Destructor.
    virtual ~KRegionFlooding() {}


    //! Set Norm.
    void setNorm ( double norm ) { _norm = norm;}

    void flood ( Eigen::VectorXi& clusterIDs );

private:
    const Eigen::VectorXi randomIDs ( int numSamples, int numLabels );

private:
    Mesh* _mesh;

    int             _numCenters;

    Eigen::MatrixXd _N_f;

    Eigen::MatrixXd _N_c;

    double _norm;
};

#endif

