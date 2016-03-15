
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
        :  BaseCommand ( "Normal Kmeans", scene ),
           _numCenters ( "numCenters", 2, 50, 6 ),
           _withPosition ( "withPosition", false ),
           _prefilterNormal ( "prefilterNormal", 0.0, 10.0, 1.0 ),
           _postfilterWeight ( "postfilterWeight", 0.0, 10.0, 1.0 )
    {
        _params.addInt ( &_numCenters );
        _params.addDouble ( &_prefilterNormal );
        _params.addDouble ( &_postfilterWeight );
        _params.addBool ( &_withPosition );
    }

    //! Destructor.
    virtual ~NormalKmeansCommand() {}

    void setupImp();

    void doImp ();

private:
    //! Compute random centers.
    void computeRandomCenters ( int numCenters, Eigen::MatrixXd& N_centers );

    void clustering ( const Eigen::MatrixXd& N_centers, Eigen::MatrixXd& N, Eigen::VectorXi& ID );

    void project ( const Eigen::MatrixXd& N_centers, const Eigen::VectorXi& ID, Eigen::MatrixXd& N );

    void updateCenters ( const Eigen::MatrixXd& N, const Eigen::VectorXi& ID, const Eigen::VectorXd& A_f, Eigen::MatrixXd& N_centers );

    void prefilterNormal ( const Eigen::MatrixXd& N, double lambda, Eigen::MatrixXd& N_smooth );

    void smoothingWeights ( double lambda, Eigen::VectorXi& clusterIDs );

    void doAll();

    void doSelectedLabel();


private:
    IntParameter _numCenters;
    BoolParameter _withPosition;
    DoubleParameter _prefilterNormal;
    DoubleParameter _postfilterWeight;

    Eigen::SparseMatrix<double> _M;
};

#endif

