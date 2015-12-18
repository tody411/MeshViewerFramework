
/*!
  \file     NoiseCommand.cpp
  \author       Tody
  NoiseCommand definition.
  date      2015/12/18
*/

#include "NoiseCommand.h"

#include <random>

void NoiseCommand::setupImp()
{
    Mesh* mesh = _scene->mesh();
    mesh->points ( _V );

    Eigen::SparseMatrix<double> L;
}

void NoiseCommand::doImp ()
{
    double sigma = _sigma.value();

    Eigen::MatrixXd V_new = _V;

    std::random_device rd;
    std::mt19937 mt ( rd() );

    Mesh* mesh = _scene->mesh();

    BoundingBox bb = mesh->boundingBox();
    double bbSize = bb.size();

    double d = 0.5 * sigma * bbSize;

    std::uniform_real_distribution<double> randPosition ( -d, d );

    for ( int vi = 0; vi < V_new.rows(); vi++ )
    {
        V_new.row ( vi ) += Eigen::Vector3d ( randPosition ( mt ), randPosition ( mt ), randPosition ( mt ) );
    }


    mesh->setPoints ( V_new );
}