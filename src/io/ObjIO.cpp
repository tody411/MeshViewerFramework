
/*!
  \file     ObjIO.cpp
  \author       Tody
  ObjIO definition.
  date      2016/02/29
*/

#include "ObjIO.h"

#include <QElapsedTimer>

#include <string>

#include <iostream>
#include <fstream>

#include "Mesh.h"

//! fprintf version is much faster than ostream version.
void saveMeshFprintf ( const std::string& filePath, const Mesh& mesh )
{
    FILE* pFile = fopen ( filePath.c_str(), "w" );
    if ( NULL == pFile )
    {
        std::string openError ( "Could not open: " );
        openError += filePath;
        std::cerr << openError << std::endl;
        return;
    }

    Eigen::MatrixXd V;
    mesh.points ( V );

    int numVertices =  mesh.numVertices();
    int numFaces = mesh.numFaces();

    fprintf ( pFile, "# %u vertices\n", numVertices );

    for ( int vi = 0; vi <  numVertices; vi++ )
    {
        fprintf ( pFile, "v %0.15g %0.15g %0.15g\n",
                  V ( vi, 0 ),
                  V ( vi, 1 ),
                  V ( vi, 2 )
                );
    }

    if ( mesh.hasUVs() )
    {
        Eigen::MatrixXd UVs;
        mesh.UVs ( UVs );

        int numUVs = mesh.numUVs();

        fprintf ( pFile, "# %u uvs\n", numUVs );

        for ( int uvi = 0; uvi < numUVs; uvi++ )
        {
            fprintf ( pFile, "vt %0.15g %0.15g\n",
                      UVs ( uvi, 0 ),
                      UVs ( uvi, 1 )
                    );
        }
    }

    Eigen::MatrixXi A_fv;
    mesh.Adj_fv ( A_fv );

    fprintf ( pFile, "# %u faces\n", numFaces );

    std::cout << "A_fv: " << A_fv.rows() << ", " << A_fv.cols() << std::endl;

    Eigen::MatrixXi UVIDs;

    if ( mesh.hasUVs() )
    {
        //! Vertex UV mode.
        mesh.Adj_fv ( UVIDs );
    }

    if ( mesh.hasUVIDs() )
    {
        mesh.UVIDs ( UVIDs );
    }

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        fprintf ( pFile, "f" );

        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            fprintf ( pFile, " %u", A_fv ( fi, fvi ) + 1 );

            if ( mesh.hasUVIDs() )
            {
                fprintf ( pFile, "/%u", UVIDs ( fi, fvi ) + 1 );
            }
        }
        fprintf ( pFile, "\n" );
    }

    fclose ( pFile );
}

//! ostream version is much slower than fprintf version.
void saveMeshOStream ( const std::string& filePath, const Mesh& mesh )
{
    std::ofstream  ofs ( filePath );
    if ( !ofs )
    {
        std::string openError ( "Could not open: " );
        openError += filePath;
        std::cerr << openError << std::endl;
        return;
    }

    Eigen::MatrixXd V;
    mesh.points ( V );

    int numVertices =  mesh.numVertices();
    int numFaces = mesh.numFaces();

    ofs << "# " << numVertices << " vertices" <<  std::endl;
    for ( int vi = 0; vi <  numVertices; vi++ )
    {
        ofs << "v";

        for ( int ci = 0; ci < 3; ci++ )
        {
            ofs << " " << V ( vi, ci ) ;
        }

        ofs << std::endl;
    }

    if ( mesh.hasUVs() )
    {
        Eigen::MatrixXd UVs;
        mesh.UVs ( UVs );

        int numUVs = mesh.numUVs();

        ofs << "# " << numUVs << " uvs" <<  std::endl;

        for ( int uvi = 0; uvi < numUVs; uvi++ )
        {
            ofs << "vt";

            for ( int ci = 0; ci < UVs.cols(); ci++ )
            {
                ofs << " " << UVs ( uvi, ci ) ;
            }

            ofs << std::endl;
        }
    }

    Eigen::MatrixXi A_fv;
    mesh.Adj_fv ( A_fv );
    ofs << "# " << numFaces << " faces" << std::endl;

    std::cout << "A_fv: " << A_fv.rows() << ", " << A_fv.cols() << std::endl;

    Eigen::MatrixXi UVIDs;

    if ( mesh.hasUVs() )
    {
        //! Vertex UV mode.
        mesh.Adj_fv ( UVIDs );
    }

    if ( mesh.hasUVIDs() )
    {
        mesh.UVIDs ( UVIDs );
    }

    for ( int fi = 0; fi < numFaces; fi++ )
    {
        ofs << "f";

        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            ofs << " " << A_fv ( fi, fvi ) + 1;

            if ( mesh.hasUVIDs() )
            {
                ofs << "/" << UVIDs ( fi, fvi ) + 1;
            }
        }
        ofs << std::endl;
    }
}

void ObjIO::saveMesh ( const QString& filePath, const Mesh& mesh )
{
    /* QElapsedTimer timer;
     timer.start();
     saveMeshOStream ( filePath.toStdString(), mesh );
     std::cout << "saveMeshOStream" <<  timer.elapsed() / 1000.0f << " sec" << std::endl;

     timer.start();*/
    saveMeshFprintf ( filePath.toStdString(), mesh );
    //std::cout << "saveMeshFprintfs" <<  timer.elapsed() / 1000.0f << " sec" << std::endl;

}