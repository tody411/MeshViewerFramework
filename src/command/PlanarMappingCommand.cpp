
//! PlanarMappingCommand definition.
/*!
  \file     PlanarMappingCommand.cpp
  \author       Tody
  \date     2016/02/29
*/

#include "PlanarMappingCommand.h"

#include <iostream>
#include <set>

#include "ListUtil.h"
#include "EigenUtil.h"

void PlanarMappingCommand::doImp ()
{
    Mesh* mesh = _scene->mesh();

    LabelData* labelData = _scene->labelData();

    if ( !labelData->empty() )
    {
        doLabel();
    }

    else if ( !_scene->selectionInfo()->emptyFace() )
    {
        doSelection();
    }

    else
    {
        doAll();
    }
}

void PlanarMappingCommand::doAll()
{
    Mesh* mesh = _scene->mesh();
    Eigen::MatrixXd V;
    mesh->points ( V );

    Eigen::MatrixXd UVs = V.block ( 0, 0, V.rows(), 2 );

    Eigen::VectorXd UV_min = UVs.colwise().minCoeff();
    Eigen::VectorXd UV_max = UVs.colwise().maxCoeff();

    UVs.rowwise() -= UV_min.transpose();
    UVs.block ( 0, 0, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 0 );
    UVs.block ( 0, 1, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 1 );

    mesh->setUVs ( UVs );
}

void PlanarMappingCommand::doSelection()
{
    std::vector<int> indices;
    _scene->selectionInfo()->faceSelection ( indices );

    int fID = indices[0];

    Mesh* mesh = _scene->mesh();

    Eigen::MatrixXd N;
    mesh->faceNormals ( N );

    Eigen::Vector3d z_proj = N.row ( fID );

    Eigen::Vector3d y_proj = z_proj.cross ( Eigen::Vector3d ( 1, 0, 0 ) );
    y_proj.normalize();

    Eigen::Vector3d x_proj = y_proj.cross ( z_proj );
    x_proj.normalize();

    Eigen::MatrixXd V;
    mesh->points ( V );

    int numVertices = mesh->numVertices();

    Eigen::MatrixXd UVs ( numVertices, 2 );

    UVs.col ( 0 ) = V * x_proj;
    UVs.col ( 1 ) = V * y_proj;

    Eigen::VectorXd UV_min = UVs.colwise().minCoeff();
    Eigen::VectorXd UV_max = UVs.colwise().maxCoeff();

    UVs.rowwise() -= UV_min.transpose();
    UVs.block ( 0, 0, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 0 );
    UVs.block ( 0, 1, V.rows(), 1 ) /= ( UV_max - UV_min ) ( 1 );

    mesh->setUVs ( UVs );
}

void projectDirection ( const std::vector<int>& shell, const Eigen::MatrixXd& N_f, int label,
                        Eigen::Vector3d& x_proj, Eigen::Vector3d& y_proj )
{
    Eigen::Vector3d n;

    for ( int fi = 0; fi < shell.size(); fi++ )
    {
        n += N_f.row ( shell[fi] );
    }

    n.normalize();

    y_proj = n.cross ( Eigen::Vector3d ( 1, 0, 0 ) );
    y_proj.normalize();

    x_proj = y_proj.cross ( n );
    x_proj.normalize();
}

void labelShell ( const std::vector<int>& faceLabels, int label, std::vector<int>& shell )
{
    for ( int fi = 0; fi < faceLabels.size(); fi++ )
    {
        if ( faceLabels[fi] != label ) continue;

        shell.push_back ( fi );
    }
}

void shellVertices ( const std::vector<int>& shell, const Eigen::MatrixXi& A_fv, std::vector<int>& vertices )
{
    for ( int si = 0; si < shell.size(); si++ )
    {
        int fi = shell[si];

        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            int fvID = A_fv ( fi, fvi );
            vertices.push_back ( fvID );
        }
    }

    std::set<int> verticesSet ( vertices.begin(), vertices.end() );

    vertices = std::vector<int> ( verticesSet.begin(), verticesSet.end() );
}

void PlanarMappingCommand::doLabel()
{
    LabelData* labelData = _scene->labelData();

    int numLabels = labelData->numLabels();

    Mesh* mesh = _scene->mesh();

    int numVertices = mesh->numVertices();
    int numFaces = mesh->numFaces();

    std::vector<Eigen::Vector2d> UVs ( numVertices );
    ListUtil::fill ( UVs, Eigen::Vector2d() );

    Eigen::MatrixXi UVIDs = Eigen::MatrixXi::Zero ( mesh->numFaces(), 3 );

    Eigen::MatrixXi A_fv;

    std::vector<bool> visited ( numVertices );
    ListUtil::fill ( visited, false );

    std::vector<int> faceLabels;
    labelData->faceLabelData ( faceLabels );

    mesh->Adj_fv ( A_fv );

    Eigen::MatrixXd N_f;

    mesh->faceNormals ( N_f );

    Eigen::MatrixXd V;
    mesh->points ( V );

    int shell_cols = sqrt ( numLabels );

    if ( shell_cols * shell_cols < numLabels )
    {
        shell_cols += 1;
    }

    for ( int label = 0; label < numLabels; label++ )
    {
        std::cout << "label: " << label << std::endl;
        std::vector<int> shell;
        labelShell ( faceLabels, label, shell );

        std::cout << "shell size: " << shell.size() << std::endl;

        Eigen::Vector3d x_proj, y_proj;
        projectDirection ( shell, N_f, label, x_proj, y_proj );

        Eigen::Vector2d uv_min ( 1e10, 1e10 );
        Eigen::Vector2d uv_max ( -1e10, -1e10 );

        std::vector<int> shell_vertices;
        shellVertices ( shell, A_fv, shell_vertices );

        std::vector<int> shell_vertices_uvids ( numVertices );

        for ( int svi = 0; svi < shell_vertices.size(); svi++ )
        {
            int vi = shell_vertices[svi];

            Eigen::Vector2d uv;

            uv ( 0 ) = V.row ( vi ) * x_proj;
            uv ( 1 ) = V.row ( vi ) * y_proj;

            for ( int ci = 0; ci < 2; ci++ )
            {
                if ( uv_min ( ci ) > uv ( ci ) )
                {
                    uv_min ( ci ) = uv ( ci );
                }

                if ( uv_max ( ci ) < uv ( ci ) )
                {
                    uv_max ( ci ) = uv ( ci );
                }
            }

            if ( visited[vi] )
            {
                UVs.push_back ( uv );
                shell_vertices_uvids[vi] = UVs.size() - 1;
            }

            else
            {
                UVs[vi] = uv;
                shell_vertices_uvids[vi] = vi;
            }
        }

        int shell_row = label / shell_cols;
        int shell_col = label % shell_cols;
        Eigen::Vector2d uv_shell_min ( shell_col / ( double ) shell_cols, shell_row / ( double ) shell_cols );
        Eigen::Vector2d uv_shell_max = uv_shell_min + Eigen::Vector2d ( 1.0 / ( double ) shell_cols, 1.0 / ( double ) shell_cols );

        for ( int svi = 0; svi < shell_vertices.size(); svi++ )
        {
            int vi = shell_vertices[svi];
            int uvid = shell_vertices_uvids[vi];
            Eigen::Vector2d uv = UVs[uvid];
            uv = ( uv - uv_min ).array() / ( uv_max - uv_min ).array();
            uv = uv_shell_min.array() + ( uv_shell_max - uv_shell_min ).array() * uv.array();
            UVs[uvid] = uv;

            visited[vi] = true;
        }

        for ( int si = 0; si < shell.size(); si++ )
        {
            int fi = shell[si];

            for ( int fvi = 0; fvi < 3; fvi++ )
            {
                int vi = A_fv ( fi, fvi );
                UVIDs ( fi, fvi ) = shell_vertices_uvids[vi];
            }
        }

        std::cout << "uv_min: " << uv_min << std::endl;
        std::cout << "uv_max: " << uv_max << std::endl;
    }

    Eigen::MatrixXd UVs_mat ( UVs.size(), 2 );

    for ( int uvi = 0; uvi < UVs.size(); uvi++ )
    {
        UVs_mat.row ( uvi ) = UVs[uvi];
    }

    std::cout << EigenUtil::info ( UVs_mat, "UVs" ) << std::endl;
    std::cout << EigenUtil::info ( UVIDs, "UVIDs" ) << std::endl;

    mesh->setUVs ( UVs_mat );
    mesh->setUVIDs ( UVIDs );
}