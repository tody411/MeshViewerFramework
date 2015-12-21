
/*!
  \file     NormalKmeansCommand.h
  \author   Tody
  NormalKmeansCommand definition.
  \date     2015/12/20
*/

#ifndef NORMALKMEANSCOMMAND_H
#define NORMALKMEANSCOMMAND_H

#include "BaseCommand.h"

//! NormalKmeansCommand implementation.
class NormalKmeansCommand : public BaseCommand
{
public :
    //! Constructor.
    NormalKmeansCommand ( Scene* scene )
        :  BaseCommand ( "Normal Kmeans", scene ), _numCenters ( "numCenters", 2, 20, 6 )
    {
        _params.addInt ( &_numCenters );
    }

    //! Destructor.
    virtual ~NormalKmeansCommand() {}

    void doImp ();

private:
    //! Compute random centers.
    void computeRandomCenters ( int numCenters, Eigen::MatrixXd& N_centers );

    void clustering ( const Eigen::MatrixXd& N_centers, Eigen::MatrixXd& N, Eigen::VectorXi& ID );

    void project ( const Eigen::MatrixXd& N_centers, const Eigen::VectorXi& ID, Eigen::MatrixXd& N );

    void updateCenters ( const Eigen::MatrixXd& N, const Eigen::VectorXi& ID, Eigen::MatrixXd& N_centers );


private:
    IntParameter _numCenters;
};

#endif

