
//! NormalSampling definition.
/*!
  \file     NormalSampling.h
  \author   Tody
  \date     2016/03/17
*/

#ifndef NORMALSAMPLING_H
#define NORMALSAMPLING_H

#include <Eigen/Dense>

//! NormalSampling implementation.
class NormalSampling
{
public :
    //! Constructor.
    NormalSampling()
        : _numSamples ( 20 ), _numLearnSamples ( 2000 ), _numIterations ( 40 )
    {}

    //! Destructor.
    virtual ~NormalSampling() {}


    //! Set NumSamples.
    void setNumSamples ( int numSamples ) { _numSamples = numSamples;}

    const Eigen::MatrixXd samples ();

private:
    const Eigen::MatrixXd randomNormals ( int numSamples );

private:
    int _numSamples;
    int _numLearnSamples;
    int _numIterations;
};

#endif

