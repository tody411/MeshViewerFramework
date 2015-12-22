
/*!
  \file     SpectralClusteringCommand.h
  \author   Tody
  SpectralClusteringCommand definition.
  \date     2015/12/20
*/

#ifndef SPECTRALCLUSTERINGCOMMAND_H
#define SPECTRALCLUSTERINGCOMMAND_H

#include "BaseCommand.h"

//! SpectralClusteringCommand implementation.
class SpectralClusteringCommand: public BaseCommand
{
public :
    //! Constructor.
    SpectralClusteringCommand ( Scene* scene )
        :  BaseCommand ( "Spectral Clustering", scene ),
           _numCenters ( "numCenters", 2, 20, 6 ),
           _clusterID ( "clusterID", 0, 20, 0 ),
           _isSparse ( "isSparse", true )
    {
        _params.addInt ( &_numCenters );
        _params.addInt ( &_clusterID );
        _params.addBool ( &_isSparse );

        _isSparseOld = true;

        setInteractive ( true );
    }

    //! Destructor.
    virtual ~SpectralClusteringCommand() {}

    void setupImp();

    void doImp ();

private:
    void computeDense ( const Eigen::SparseMatrix<double>& L, int numCenters );

    void computeSparse ( const Eigen::SparseMatrix<double>& L, int numCenters );

    void fullWeightMatrix ( const  Eigen::MatrixXd& N, Eigen::MatrixXd& W );

private:
    IntParameter _numCenters;
    IntParameter _clusterID;
    BoolParameter _isSparse;

    Eigen::MatrixXd _U;

    bool _isSparseOld;
};

#endif

