
//! KRegionFlooding definition.
/*!
  \file     KRegionFlooding.cpp
  \author       Tody
  \date     2016/03/17
*/

#include "KRegionFlooding.h"

#include "NormalClustering.h"

#include <queue>
#include <random>
#include <iostream>

KRegionFlooding::KRegionFlooding (  Mesh* mesh, int numCenters )
    : _mesh ( mesh ), _numCenters ( numCenters ), _norm ( 2.0 )
{
    _mesh->faceNormals ( _N_f );
}

class KRegionFloodingQueData
{
public:
    double error;
    int faceID;
    int clusterID;

    KRegionFloodingQueData()
        :  error ( 0 ), faceID ( 0 ), clusterID ( 0 )
    {}

    KRegionFloodingQueData ( double error, int faceID, int clusterID )
        : error ( error ), faceID ( faceID ), clusterID ( clusterID )
    {}
};

//Overload the < operator.
bool operator< ( const KRegionFloodingQueData& data1, const KRegionFloodingQueData& data2 )
{
    return data1.error > data2.error;
}
//Overload the > operator.
bool operator> ( const KRegionFloodingQueData& data1, const KRegionFloodingQueData& data2 )
{
    return data1.error < data2.error;
}


void KRegionFlooding::flood ( Eigen::VectorXi& clusterIDs )
{
    if ( clusterIDs.size() == 0 )
    {
        clusterIDs = randomIDs ( _N_f.rows(), _numCenters );
    }

    std::cout << "clusterIDs.size" << clusterIDs.size() << std::endl;
    std::cout << "clusterIDs.minCoeff" << clusterIDs.minCoeff() << std::endl;
    std::cout << "clusterIDs.maxCoeff" << clusterIDs.maxCoeff() << std::endl;

    NormalClustering normalClustering;
    normalClustering.updateCenters ( _N_f, clusterIDs, _N_c );

    std::cout << "updateCenters" << std::endl;

    Eigen::VectorXi seedFaces;
    normalClustering.centerSamples ( _N_c, _N_f, seedFaces );

    std::cout << "centerSamples" << std::endl;

    Eigen::VectorXd Area_f;
    _mesh->Area_f ( Area_f );

    MeshData* openMesh = _mesh->openMeshData();

    MeshData::FaceIter f_it, f_end ( openMesh->faces_end() );
    MeshData::FaceFaceIter ff_it;

    Eigen::VectorXd A_c = Eigen::VectorXd::Zero ( _N_c.rows() );
    Eigen::VectorXd E_c = Eigen::VectorXd::Zero ( _N_c.rows() );

    for ( int fi = 0; fi < clusterIDs.size(); fi++ )
    {
        clusterIDs[fi] = -1;
    }

    bool doneFlood = false;

    std::priority_queue< KRegionFloodingQueData, std::vector<KRegionFloodingQueData>, std::less<KRegionFloodingQueData> > face_queue;

    for ( int ci = 0; ci < seedFaces.size(); ci++ )
    {
        face_queue.push ( KRegionFloodingQueData ( 0.0, seedFaces[ci], ci ) );
    }

    _N_c = Eigen::MatrixXd::Zero ( _N_c.rows(), 3 );

    while ( !face_queue.empty() )
    {
        int faceID = face_queue.top().faceID;
        int clusterID = face_queue.top().clusterID;
        double error = face_queue.top().error;
        E_c[ clusterID ] = error;
        face_queue.pop();

        if ( clusterIDs[faceID] == -1 )
        {
            clusterIDs[faceID] = clusterID;

            Eigen::Vector3d N_fi = _N_f.row ( faceID );
            double A_fi = Area_f ( faceID );

            A_c[clusterID] += A_fi;
            double t = A_fi / A_c[clusterID];

            Eigen::Vector3d N_ci = _N_c.row ( clusterID );
            N_ci = ( 1.0 - t ) * N_ci + t * N_fi;
            N_ci.normalize();

            _N_c.row ( clusterID ) = N_ci;

            for ( ff_it = openMesh->ff_begin ( MeshData::FaceHandle ( faceID ) ); ff_it.is_valid(); ++ff_it )
            {
                int ffID = ff_it->idx();

                if ( clusterIDs[ffID] == -1 )
                {
                    Eigen::Vector3d N_ffi = _N_f.row ( ffID );
                    double A_ffi =  Area_f ( ffID );

                    double d_n = ( N_ffi - N_ci ).norm();
                    error = pow ( d_n, _norm );

                    error = E_c[ clusterID ] + A_ffi * error;

                    face_queue.push ( KRegionFloodingQueData ( error, ffID, clusterID ) );
                }
            }
        }
    }
}

const Eigen::VectorXi KRegionFlooding::randomIDs ( int numSamples, int numLabels )
{
    Eigen::VectorXi clusterIDs ( numSamples );

    std::random_device rd;
    std::mt19937 mt ( rd() );

    std::uniform_int_distribution<int> randomID ( 0, numLabels - 1 );

    for ( int i = 0; i < numSamples; i++ )
    {
        clusterIDs[i] = randomID ( mt );
    }
    return clusterIDs;
}