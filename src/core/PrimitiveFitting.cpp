
//! PrimitiveFitting definition.
/*!
  \file     PrimitiveFitting.cpp
  \author       Tody
  \date     2016/03/03
*/

#include "PrimitiveFitting.h"

#include <random>
#include <iostream>

#include "EigenUtil.h"

PrimitiveKMeans::~PrimitiveKMeans()
{
    _primitives.clear();
}

void PrimitiveKMeans::fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N )
{
    Eigen::MatrixXd V_normalized = ( V.array() - V.minCoeff() ) / ( V.maxCoeff() - V.minCoeff() );
    int numData = V.rows();

    computeRandomCenters ( _numCenters, numData, _clusterIDs );

    for ( int ci = 0; ci < _numCenters; ci++ )
    {
        _primitives.push_back ( PrimitivePtr ( new QuadricSurfaceFitting() ) );
    }

    for ( int i = 0; i < _numIterations; i++ )
    {
        fitPrimitives ( V_normalized, N );
        updateClusters ( V_normalized, N );
    }
}

void PrimitiveKMeans::computeRandomCenters ( int numCenters, int numData, Eigen::VectorXi& clusterIDs )
{
    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_int_distribution<int> randCenter ( 0, numCenters - 1 );

    clusterIDs.resize ( numData );

    for ( int i = 0; i < numData; i++ )
    {
        clusterIDs ( i ) = randCenter ( mt );
    }
}

void PrimitiveKMeans::clusterData ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N, int clusterID, Eigen::MatrixXd& V_c, Eigen::MatrixXd& N_c )
{
    Eigen::VectorXi faceIDs;

    std::cout << "clusterData"  << std::endl;
    EigenUtil::isValue ( _clusterIDs, clusterID, faceIDs );

    std::cout << "isValue"  << std::endl;

    if ( faceIDs.size() == 0 ) return;

    std::cout << "slice"  << std::endl;
    EigenUtil::slice ( V, faceIDs, V_c );
    EigenUtil::slice ( N, faceIDs, N_c );
}

void PrimitiveKMeans::fitPrimitives ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N )
{
    for ( int ci = 0; ci < _numCenters; ci++ )
    {
        Eigen::MatrixXd V_c, N_c;

        std::cout << "fitPrimitives" << ci << std::endl;

        clusterData ( V, N, ci, V_c, N_c );

        if ( V_c.size() == 0 ) continue;

        _primitives[ci]->fit ( V_c, N_c );

        _primitives[ci]->info();
    }
}

void PrimitiveKMeans::updateClusters ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N )
{
    int numData = V.rows();

    Eigen::MatrixXd E = 1e10 * Eigen::MatrixXd::Ones ( numData, _numCenters );

    for ( int ci = 0; ci < _numCenters; ci++ )
    {
        Eigen::VectorXd e;
        _primitives[ci]->error ( V, N, e );

        E.col ( ci ) = e;
    }

    for ( int di = 0; di < numData; di++ )
    {
        int clusterID = 0;
        E.row ( di ).minCoeff ( &clusterID );

        if ( clusterID > -1 && clusterID < _numCenters )
        {
            _clusterIDs ( di ) = clusterID;
        }
    }
}

void PlaneFitting::fitPosition ( const Eigen::MatrixXd& V )
{
    Eigen::Vector3d V_g = V.colwise().sum();
    V_g *= 1.0 / ( double ) V.rows();

    Eigen::MatrixXd T = V - V_g;

    Eigen::Matrix3d TtT = T.transpose() * T;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver ( TtT );

    if ( eigensolver.info() != Eigen::Success ) return;

    Eigen::Vector3d eigenValues =  eigensolver.eigenvalues();
    Eigen::Matrix3d eigenVectors = eigensolver.eigenvectors();

    _center = V_g;
    _normal = eigenVectors.col ( 0 );
    _normal.normalize();
}

void PlaneFitting::fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N )
{
    if ( V.size() == 0 ) return;

    Eigen::Vector3d V_g = V.colwise().mean();

    Eigen::Vector3d N_g = N.colwise().mean();
    N_g.normalize();

    _center = V_g;
    _normal = N_g;
}

void PlaneFitting::error ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E )
{
    Eigen::MatrixXd D_v = V;
    D_v.rowwise() -=  _center.transpose();

    Eigen::MatrixXd D_n = N;
    D_n.rowwise() -=  _normal.transpose();

    Eigen::VectorXd E_v = D_v.rowwise().norm();
    Eigen::VectorXd E_n = D_n.rowwise().norm();
    Eigen::VectorXd E_fit = ( D_v * _normal ).rowwise().norm();

    E = E_v + E_n + E_fit;
}

void PlaneFitting::project ( const Eigen::MatrixXd& V, Eigen::MatrixXd& V_proj )
{
    Eigen::MatrixXd D_v = V - _center;
    Eigen::VectorXd d_vn = D_v * _normal;

    Eigen::MatrixXd d_vn3 ( V.rows(), V.cols() );
    d_vn3 = d_vn;

    Eigen::MatrixXd D_n = d_vn3 * _normal;

    V_proj = D_n + _center;
}

void PlaneFitting::info()
{
    std::cout << "center" << _center << std::endl;
    std::cout << "normal" << _normal << std::endl;
}



void QuadricSurfaceFitting::fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N )
{
    Eigen::MatrixXd F_zero;
    computeF ( V, F_zero );

    Eigen::MatrixXd F_out;
    double f_out = 0.05;
    computeF ( V + f_out * N, F_out );

    Eigen::MatrixXd F_in;
    double f_in = - 0.05;
    computeF ( V + f_in * N, F_in );

    Eigen::MatrixXd FtF_zero = F_zero.transpose() * F_zero;
    Eigen::MatrixXd FtF_out = F_out.transpose() * F_out;
    Eigen::MatrixXd FtF_in = F_in.transpose() * F_in;

    std::cout << EigenUtil::info ( FtF_zero, "FtF_zero" ) << std::endl;
    std::cout << EigenUtil::info ( FtF_out, "FtF_out" ) << std::endl;

    double w_out = 0.01;
    double w_in = 0.01;
    double w_R = 0.0;
    Eigen::MatrixXd I_A = Eigen::MatrixXd::Zero ( FtF_zero.rows(), FtF_zero.cols() );
    Eigen::MatrixXd A = FtF_zero + w_out * FtF_out + w_in * FtF_in + w_R * I_A;

    Eigen::VectorXd I_b = Eigen::VectorXd::Ones ( V.rows() );
    Eigen::VectorXd b = w_out * f_out * F_out.transpose() * I_b + w_in * f_in * F_in.transpose() * I_b;

    std::cout << EigenUtil::info ( F_out.transpose(), "F_out_t" ) << std::endl;
    std::cout << EigenUtil::info ( F_out.transpose() * I_b, "F_out_tb" ) << std::endl;

    std::cout << EigenUtil::info ( b , "b " ) << std::endl;

    _C = A.ldlt().solve ( b );

    std::cout << EigenUtil::info ( _C, "C" ) << std::endl;
}

void QuadricSurfaceFitting::error ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E )
{
    Eigen::MatrixXd F;
    computeF ( V, F );

    Eigen::VectorXd E_v;

    positionError ( V, E_v );

    Eigen::VectorXd E_n;
    normalError ( V, N, E_n );

    E = E_n + 0.1 * E_v;

    std::cout << "error: " << E_v.mean() << std::endl;
}

void QuadricSurfaceFitting::computeF ( const Eigen::MatrixXd& V, Eigen::MatrixXd& F )
{
    F.resize ( V.rows(), 10 );

    F.col ( 0 ) = Eigen::VectorXd::Ones ( V.rows() );

    Eigen::ArrayXd x = V.col ( 0 );
    Eigen::ArrayXd y = V.col ( 1 );
    Eigen::ArrayXd z = V.col ( 2 );


    F.col ( 1 ) = x;
    F.col ( 2 ) = y;
    F.col ( 3 ) = z;

    F.col ( 4 ) = x * x;
    F.col ( 5 ) = y * y;
    F.col ( 6 ) = z * z;

    F.col ( 7 ) = x * y;
    F.col ( 8 ) = y * z;
    F.col ( 9 ) = z * x;

    std::cout << EigenUtil::info ( V , "V" ) << std::endl;
    std::cout << EigenUtil::info ( F , "F" ) << std::endl;
}

void QuadricSurfaceFitting::positionError ( const Eigen::MatrixXd& V, Eigen::VectorXd& E )
{
    Eigen::MatrixXd F;
    computeF ( V, F );

    E = ( F * _C ).rowwise().norm();
}

void QuadricSurfaceFitting::normalError ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E )
{
    Eigen::MatrixXd N_fit ( N.rows(), N.cols() );

    Eigen::ArrayXd x = V.col ( 0 );
    Eigen::ArrayXd y = V.col ( 1 );
    Eigen::ArrayXd z = V.col ( 2 );

    N_fit.col ( 0 ) =  _C ( 1 ) + 2 * _C ( 4 ) * x + _C ( 7 ) * y + _C ( 9 ) * z;
    N_fit.col ( 1 ) =  _C ( 2 ) + 2 * _C ( 5 ) * x + _C ( 7 ) * y + _C ( 8 ) * z;
    N_fit.col ( 2 ) =  _C ( 3 ) + 2 * _C ( 6 ) * x + _C ( 8 ) * y + _C ( 9 ) * z;

    N_fit.rowwise().normalize();

    E = ( N_fit - N ).rowwise().norm();
}

void QuadricSurfaceFitting::A_n ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::MatrixXd& A )
{
    Eigen::ArrayXd x = V.col ( 0 );
    Eigen::ArrayXd y = V.col ( 1 );
    Eigen::ArrayXd z = V.col ( 2 );

    Eigen::MatrixXd F = Eigen::MatrixXd::Zero ( V.rows(), 10 );
}

void QuadricSurfaceFitting::info()
{
    std::cout << "C" << _C << std::endl;
}