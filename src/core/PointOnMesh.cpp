
/*!
  \file     PointOnMesh.cpp
  \author       Tody
  PointOnMesh definition.
  date      2015/12/18
*/

#include "PointOnMesh.h"


bool PointOnFace::isValid() const { return ( mesh != nullptr );}


const Eigen::Vector3f PointOnFace::point() const
{
    Eigen::Vector3f p;
    if ( !isValid() )
    {
        return p;
    }

    MeshData::FaceVertexIter fvIt = mesh->fv_begin ( fh );
    OpenMesh::Vec3f v1, v2, v3;

    v1 = mesh->point ( *fvIt );
    ++fvIt;
    v2 = mesh->point ( *fvIt );
    ++fvIt;
    v3 = mesh->point ( *fvIt );
    ++fvIt;

    OpenMesh::Vec3f p_om = ( 1.0f - w1 - w2 ) * v1 + w1 * v2 + w2 * v3;

    for ( int i = 0; i < 3; i++ )
    {
        p[i] = p_om[i];
    }
    return p;
}

const Eigen::Vector3f PointOnFace::normal() const
{
    Eigen::Vector3f n;
    if ( !isValid() )
    {
        return n;
    }

    MeshData::FaceVertexIter fvIt = mesh->fv_begin ( fh );
    OpenMesh::Vec3f n1, n2, n3;

    n1 = mesh->normal (  *fvIt );
    ++fvIt;
    n2 = mesh->normal (  *fvIt );
    ++fvIt;
    n3 = mesh->normal (  *fvIt );
    ++fvIt;

    OpenMesh::Vec3f n_om = ( 1.0f - w1 - w2 ) * n1 + w1 * n2 + w2 * n3;

    for ( int i = 0; i < 3; i++ )
    {
        n[i] = n_om[i];
    }
    return n;
}

const Eigen::Vector2f PointOnFace::uv() const
{
    Eigen::Vector2f u;
    if ( !isValid() )
    {
        return u;
    }

    MeshData::FaceVertexIter fvIt = mesh->fv_begin ( fh );
    OpenMesh::Vec2f u1, u2, u3;

    u1 = mesh->texcoord2D (  *fvIt );
    ++fvIt;
    u2 = mesh->texcoord2D (  *fvIt );
    ++fvIt;
    u3 = mesh->texcoord2D (  *fvIt );
    ++fvIt;

    OpenMesh::Vec2f u_om = ( 1.0f - w1 - w2 ) * u1 + w1 * u2 + w2 * u3;

    for ( int i = 0; i < 2; i++ )
    {
        u[i] = u_om[i];
    }
    return u;
}