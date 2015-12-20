
/*!
  \file     Mesh.cpp
  \author       Tody
  Mesh definition.
  date      2015/12/16
*/

#include "Mesh.h"

#include <QtOpenGL>

#include <OpenMesh/Core/IO/MeshIO.hh>

bool Mesh::loadMesh ( const QString& filePath )
{
    _mesh.request_face_normals();
    _mesh.request_face_colors();
    _mesh.request_vertex_normals();
    _mesh.request_vertex_colors();
    _mesh.request_vertex_texcoords2D();

    std::string file = filePath.toStdString();

    if ( !OpenMesh::IO::read_mesh ( _mesh, file ) )
    {
        std::cerr << "read error" << std::endl;
        return false;
    }

    _mesh.update_normals();

    if ( !_mesh.is_triangles() )
    {
        _mesh.triangulate();
    }

    if ( !_mesh.has_vertex_normals() )
    {
        std::cout << "No vertex normals" << std::endl;
    }

    updateBoundingBox();

    computeIndices();
    return true;
}

bool Mesh::saveMesh ( const QString& filePath )
{
    std::string file = filePath.toStdString();
    if ( !OpenMesh::IO::write_mesh ( _mesh, file ) )
    {
        std::cerr << "write error" << std::endl;
        return false;
    }
    return true;
}


void Mesh::points ( Eigen::MatrixXd& V )
{
    V.resize ( numVertices(), 3 );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p = _mesh.point ( *v_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            V ( v_it->idx(), ci ) = p[ci];
        }
    }
}

void Mesh::setPoints ( const Eigen::MatrixXd& V )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Point p;
        for ( int ci = 0; ci < 3; ci++ )
        {
            p[ci] = V ( v_it->idx(), ci );
        }

        _mesh.point ( *v_it ) = p;
    }

    _mesh.update_normals();

    updateBoundingBox();

    emit updated();
}

void Mesh::facePoints ( Eigen::MatrixXd& V )
{
    V.resize ( 3 * numFaces(), 3 );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceVertexIter fv_it;

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        int vi = 0;
        for ( fv_it = _mesh.fv_begin ( f_it ); fv_it.is_valid(); ++fv_it )
        {
            MeshData::Point p = _mesh.point ( *fv_it );
            for ( int ci = 0; ci < 3; ci++ )
            {
                V ( 3 * f_it->idx() + vi, ci ) = p[ci];
            }
            ++vi;
        }
    }
}

void Mesh::vertexNormals ( Eigen::MatrixXd& N )
{
    N .resize ( numVertices(), 3 );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Normal n = _mesh.normal ( *v_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            N ( v_it->idx(), ci ) = n[ci];
        }

    }
}

void Mesh::setVertexNormals ( const Eigen::MatrixXd& N )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Normal n;
        for ( int ci = 0; ci < 3; ci++ )
        {
            n[ci] = N ( v_it->idx(), ci );
        }

        _mesh.set_normal ( *v_it, n );
    }

    emit updated();
}

void Mesh::vertexColors ( Eigen::MatrixXd& C )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Color c = _mesh.color ( *v_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            C ( v_it->idx(), ci ) = c[ci] / 255.0;
        }
    }
}

void Mesh::setVertexColors ( const Eigen::MatrixXd& C )
{
    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        MeshData::Color c;
        for ( int ci = 0; ci < 3; ci++ )
        {
            c[ci] = 255 * C ( v_it->idx(), ci );
        }

        _mesh.set_color ( *v_it, c );
    }

    emit updated();
}

void Mesh::faceColors ( Eigen::MatrixXd& C )
{
    C.resize ( numFaces(), 3 );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        MeshData::Color c = _mesh.color ( *f_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            C ( f_it->idx(), ci ) = c[ci] / 255.0;
        }

    }
}

void Mesh::setFaceColors ( const Eigen::MatrixXd& C )
{
    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        MeshData::Color c;

        for ( int ci = 0; ci < 3; ci++ )
        {

            c[ci] = 255 * C ( f_it->idx(), ci );
        }

        _mesh.set_color ( *f_it, c );

    }
}

void Mesh::faceNormals ( Eigen::MatrixXd& N )
{
    N .resize ( numFaces(), 3 );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        MeshData::Normal n = _mesh.normal ( *f_it );

        for ( int ci = 0; ci < 3; ci++ )
        {
            N ( f_it->idx(), ci ) = n[ci];
        }

    }
}

void Mesh::vertexLaplacian ( Eigen::SparseMatrix<double>& L )
{
    int numRows = numVertices();
    int numCols = numRows;

    L.resize ( numRows, numCols );

    L.reserve ( Eigen::VectorXi::Constant ( numCols, 8 ) );

    MeshData::VertexIter v_it, v_end ( _mesh.vertices_end() );
    MeshData::VertexVertexIter vv_it;

    for ( v_it = _mesh.vertices_begin(); v_it != v_end; ++v_it )
    {
        double w_sum = 0.0;
        for ( vv_it = _mesh.vv_begin ( v_it ); vv_it.is_valid(); ++vv_it )
        {
            double w = 1.0;
            L.insert ( v_it->idx(), vv_it->idx() ) = -w;
            w_sum += w;
        }

        L.insert ( v_it->idx(), v_it->idx() ) = w_sum;
    }

    L.makeCompressed();
}

void Mesh::gl ( DisplayMode displayMode )
{
    if ( _mesh.vertices_empty() ) return;

    switch ( displayMode )
    {
    case Mesh::SHADING:
        glShadingMode ();
        break;
    case Mesh::GLSL:
        glShadingMode ();
        break;
    case Mesh::VERTEX_COLOR:
        glVertexColorMode();
        break;
    case Mesh::FACE_COLOR:
        glFaceColorMode();
        break;
    case Mesh::WIREFRAME:
        glWireframeMode ( );
        break;
    case Mesh::POINTS:
        glPoints();
        break;
    default:
        glShadingMode ();
        break;
    }
}

void Mesh::glShadingMode ()
{
    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    glEnableClientState ( GL_VERTEX_ARRAY );

    glVertexPointer ( 3, GL_FLOAT, 0, _mesh.points() );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, 0, _mesh.vertex_normals() );

    glDrawElements ( GL_TRIANGLES,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     &_indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
}

void Mesh::glVertexColorMode ()
{
    if ( !_mesh.has_vertex_colors() )
    {
        glShadingMode();
        return;
    }

    glDisable ( GL_LIGHTING );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, _mesh.points() );

    glEnableClientState ( GL_COLOR_ARRAY );
    glColorPointer ( 3, GL_UNSIGNED_BYTE, 0, _mesh.vertex_colors() );

    glDrawElements ( GL_TRIANGLES,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     &_indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_COLOR_ARRAY );
}

void Mesh::glFaceColorMode ( )
{
    if ( !_mesh.has_face_colors() )
    {
        glShadingMode();
        return;
    }

    glDisable ( GL_LIGHTING );

    MeshData::FaceIter f_it, f_end ( _mesh.faces_end() );
    MeshData::FaceVertexIter fv_it;

    glBegin ( GL_TRIANGLES );

    for ( f_it = _mesh.faces_begin(); f_it != f_end; ++f_it )
    {
        MeshData::Color c = _mesh.color ( *f_it );

        for ( fv_it = _mesh.fv_begin ( f_it ); fv_it.is_valid(); ++fv_it )
        {
            MeshData::Point p =  _mesh.point ( *fv_it );
            glColor3ubv ( c.data() );
            glVertex3fv ( p.data() );
        }
    }

    glEnd();
}

void Mesh::glPoints ( )
{
    glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, _mesh.points() );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, 0, _mesh.vertex_normals() );

    glDrawElements ( GL_TRIANGLES,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     &_indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
}

void Mesh::glWireframeMode ( )
{
    glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, 0, _mesh.points() );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, 0, _mesh.vertex_normals() );

    glDrawElements ( GL_TRIANGLES,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     &_indices [0] );

    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
}

void Mesh::updateBoundingBox()
{
    _bb.clear();
    _bb.expand ( * ( openMeshData() ) );
}

void Mesh::computeIndices()
{
    int numFaces = _mesh.n_faces();
    _indices.resize ( 3 * numFaces );

    MeshData::ConstFaceIter    fIt ( _mesh.faces_begin() ),
             fEnd ( _mesh.faces_end() );
    MeshData::ConstFaceVertexIter fvIt;

    int triID = 0;

    for ( ; fIt != fEnd; ++fIt )
    {
        fvIt = _mesh.cfv_iter ( *fIt );
        _indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        _indices[triID] = fvIt->idx();
        ++triID;
        ++fvIt;

        _indices[triID] = fvIt->idx();
        ++triID;
    }
}