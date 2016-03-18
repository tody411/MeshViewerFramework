
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
#include "ListUtil.h"

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

    //! Set FaceNormals.
    void setFaceNormals ( const Eigen::MatrixXd& N_f ) { _N_f = N_f;}


    //! Set TargetFaces.
    void setTargetFaces ( const std::vector<int>& targetFaces )
    {
        ListUtil::copy ( targetFaces, _targetFaces );
    }

    void flood ( Eigen::VectorXi& clusterIDs );

private:
    void computeSeedFaces ( const Eigen::MatrixXd& N_c, const Eigen::MatrixXd& N_f, const  Eigen::VectorXi& clusterIDs, Eigen::VectorXi& seedFaces );

private:
    Mesh* _mesh;

    int             _numCenters;

    Eigen::MatrixXd _N_f;

    Eigen::MatrixXd _N_c;

    double _norm;

    std::vector<int> _targetFaces;
};

#endif

