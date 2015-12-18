
/*!
  \file     RayCasting.cpp
  \author       Tody
  RayCasting definition.
  date      2015/12/18
*/

#include "RayCasting.h"

bool intersection ( const Eigen::Vector3f& raySource, const  Eigen::Vector3f& rayDirection,
                    MeshData::FaceIter& fIt, MeshData* mesh,
                    float& o_dist,
                    PointOnFace& o_point )
{
    /*OpenMesh::Vec3f rs ( raySource[0], raySource[1], raySource[2] );
    OpenMesh::Vec3f rd ( rayDirection[0], rayDirection[1], rayDirection[2] );

    OpenMesh::Vec3f e1, e2, pvec, tvec, qvec;
    float epsilon = 1.0e-10f;
    MeshData::FaceVertexIter fvIt;
    MeshData::Point point;

    fvIt = mesh->fv_iter ( fIt );

    OpenMesh::Vec3f v0 = mesh->point ( fvIt );
    ++fvIt;
    OpenMesh::Vec3f v1 = mesh->point ( fvIt );
    ++fvIt;
    OpenMesh::Vec3f v2 = mesh->point ( fvIt );
    ++fvIt;

    float det;
    float t, u, v;
    float inv_det;

    e1 = v1 - v0;
    e2 = v2 - v0;

    pvec = OpenMesh::cross ( rd, e2 );
    det = OpenMesh::dot ( e1, pvec );

    if ( det > epsilon )
    {
        tvec = rs - v0;
        u = OpenMesh::dot ( tvec, pvec );

        if ( u < 0.0f || u > det ) return false;

        qvec = OpenMesh::cross ( tvec , e1 );

        v = OpenMesh::dot ( rd, qvec );
        if ( v < 0.0 || u + v > det ) return false;

    }

    else if ( det < -epsilon )
    {
        tvec = rs - v0;

        u = OpenMesh::dot ( tvec, pvec );

        if ( u > 0.0 || u < det ) return false;

        qvec = OpenMesh::cross ( tvec, e1 );

        v = OpenMesh::dot ( rd, qvec );

        if ( v > 0.0 || u + v < det ) return false;

    }

    else
    {
        return false;
    }

    inv_det = 1.0f / det;

    t = dot ( e2, qvec );
    t *= inv_det;
    u *= inv_det;
    v *= inv_det;

    o_dist = t;
    o_point.fh = *fIt;
    o_point.w1 = u;
    o_point.w2 = v;
    o_point.mesh = mesh;*/

    return true;    //hit!!

}

bool RayCasting::closestIntersection ( const Eigen::Vector3f& raySource, const  Eigen::Vector3f& rayDirection, PointOnFace& o_point )
{
    float  Infinity = 1.0e10f;
    MeshData::FaceIter fIt;

    float minDist = Infinity;
    bool intersected = false;

    for ( fIt = _mesh->faces_begin(); fIt != _mesh->faces_end(); ++fIt )
    {
        PointOnFace point;
        float dist;
        if ( intersection ( raySource, rayDirection, fIt, _mesh, dist, point ) )
        {
            if ( dist < minDist )
            {
                minDist = dist;
                o_point = point;
            }
            intersected = true;
        }

    }

    return intersected;
}