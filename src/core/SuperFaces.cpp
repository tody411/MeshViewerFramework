
//! SuperFaces definition.
/*!
  \file     SuperFaces.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "SuperFaces.h"

#include "NormalSampling.h"
#include "NormalClustering.h"

void SuperFaces::compute ( Eigen::MatrixXd N_f )
{
    NormalSampling normalSampling;

    _N_c = normalSampling.samples();

    NormalClustering normalClustering;
    normalClustering.clustering ( _N_c, N_f, _clusterIDs );
}