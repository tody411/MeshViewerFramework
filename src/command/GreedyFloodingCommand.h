
//! GreedyFloodingCommand definition.
/*!
  \file     GreedyFloodingCommand.h
  \author   Tody
  \date     2016/03/10
*/

#ifndef GREEDYFLOODINGCOMMAND_H
#define GREEDYFLOODINGCOMMAND_H

#include "BaseCommand.h"

//! GreedyFloodingCommand implementation.
class GreedyFloodingCommand: public BaseCommand
{
public :
    //! Constructor.
    GreedyFloodingCommand ( Scene* scene )
        :  BaseCommand ( "Greedy Flooding", scene ),
           _tolerance ( "tolerance", 0.0, 1.0, 0.1 ),
           _prefilterNormal ( "prefilterNormal", 0.0, 10.0, 1.0 )

    {
        _params.addDouble ( &_prefilterNormal );
        _params.addDouble ( &_tolerance );

    }

    void setupImp();

    void doImp ();

private:
    void prefilterNormal ( const Eigen::MatrixXd& N, double lambda, Eigen::MatrixXd& N_smooth );

    void smoothingWeights ( double lambda, Eigen::VectorXi& clusterIDs );

private:
    DoubleParameter _tolerance;
    DoubleParameter _prefilterNormal;
    Eigen::SparseMatrix<double> _M;
};

#endif

