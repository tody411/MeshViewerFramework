
//! GreedyFlooding definition.
/*!
  \file     GreedyFlooding.cpp
  \author       Tody
  \date     2016/03/10
*/

#include "GreedyFlooding.h"

#include <queue>

bool findSeed ( Eigen::VectorXi& clusterIDs, int& seedFaceID )
{
    int numFaces = clusterIDs.size();

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        if ( clusterIDs[fi] == -1 )
        {
            seedFaceID = fi;

            return true;
        }
    }

    return false;
}

void GreedyFlooding::flood ( Eigen::VectorXi& clusterIDs )
{
    int numFaces = clusterIDs.size();
    bool doneFlood = false;

    int seedFaceID = 0;

    int clusterID = clusterIDs.maxCoeff() + 1;

    findSeed ( clusterIDs, seedFaceID );

    while ( !doneFlood )
    {
        doneFlood = true;

        floodSeed ( seedFaceID, clusterID, clusterIDs );

        doneFlood = !findSeed ( clusterIDs, seedFaceID );
        clusterID += 1;

        if ( clusterID > _maxClusterSize )
        {
            clusterID = _maxClusterSize;
        }
    }
}

class FloodQueData
{
public:
    double error;
    int faceID;

    FloodQueData()
        :  error ( 0 ), faceID ( 0 )
    {}

    FloodQueData ( double error, int faceID )
        : error ( error ), faceID ( faceID )
    {}
};

//Overload the < operator.
bool operator< ( const FloodQueData& data1, const FloodQueData& data2 )
{
    return data1.error > data2.error;
}
//Overload the > operator.
bool operator> ( const FloodQueData& data1, const FloodQueData& data2 )
{
    return data1.error < data2.error;
}


void GreedyFlooding::floodSeed ( int seedFaceID, int clusterID, Eigen::VectorXi& clusterIDs )
{
    std::priority_queue< FloodQueData, std::vector<FloodQueData>, std::less<FloodQueData> > face_queue;
    face_queue.push ( FloodQueData ( 0.0, seedFaceID ) );

    MeshData* openMesh = _mesh->openMeshData();

    MeshData::FaceIter f_it, f_end ( openMesh->faces_end() );
    MeshData::FaceFaceIter ff_it;

    Eigen::MatrixXd N;
    Eigen::VectorXd Area_f;

    _mesh->Area_f ( Area_f );
    _mesh->faceNormals ( N );

    Eigen::Vector3d N_c = N.row ( seedFaceID );
    double A_c = 0.0;

    while ( !face_queue.empty() )
    {
        int faceID = face_queue.top().faceID;
        double error = face_queue.top().error;

        if ( error < _tol &&
                clusterIDs[faceID] == -1 )
        {
            clusterIDs[faceID] = clusterID;

            Eigen::Vector3d N_fi = N.row ( faceID );
            double A_fi = Area_f ( faceID );

            A_c += A_fi;
            double t = A_fi / A_c;

            N_c = ( 1.0 - t ) * N_c + t * N_fi;
            N_c.normalize();

            face_queue.pop();

            for ( ff_it = openMesh->ff_begin ( MeshData::FaceHandle ( faceID ) ); ff_it.is_valid(); ++ff_it )
            {
                int ffID = ff_it->idx();

                if ( clusterIDs[ffID] == -1 )
                {
                    Eigen::Vector3d N_ffi = N.row ( ffID );
                    double A_ffi =  Area_f ( ffID );

                    double error = ( N_ffi - N_c ).norm();

                    face_queue.push ( FloodQueData ( error, ffID ) );
                }
            }
        }

        else
        {
            face_queue.pop();
        }
    }
}
