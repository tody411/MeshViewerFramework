
//! SuperFaces definition.
/*!
  \file     SuperFaces.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef SUPERFACES_H
#define SUPERFACES_H

#include <Eigen/Dense>

//! SuperFaces implementation.
class SuperFaces
{
public :
    //! Constructor.
    SuperFaces() {}

    //! Destructor.
    virtual ~SuperFaces() {}


    //! Out centerNormals.
    const  Eigen::MatrixXd centerNormals() const { return _N_c;}

    //! Out clusterIDs.
    const  Eigen::VectorXi clusterIDs() const { return _clusterIDs;}

    void compute ( Eigen::MatrixXd N_f );

private:
    Eigen::MatrixXd _N_c;
    Eigen::VectorXi _clusterIDs;
};

#endif

