
/*!
  \file     ExportSeamDataCommand.cpp
  \author       Tody
  ExportSeamDataCommand definition.
  date      2016/02/27
*/

#include "ExportSeamDataCommand.h"

#include <QFileDialog>
#include <fstream>

void ExportSeamDataCommand::doImp ()
{
    if ( _outputFile == "" )
    {
        QFileDialog().setDirectory ( _scene->project()->dataDir() );
        _outputFile = QFileDialog::getSaveFileName ( nullptr,
                      "Export Seam Data", QString(),
                      "Seam Data (*.dat)" );
    }

    if ( _outputFile == "" ) return;

    std::vector<int> faceLabels;
    _scene->labelData()->faceLabelData ( faceLabels );

    Eigen::MatrixXi A;
    _scene->mesh()->Adj_ef ( A );

    std::vector<int> seamEdges;

    for ( int ei = 0; ei < A.rows(); ei++ )
    {
        int label1 = faceLabels[A ( ei, 0 )];
        int label2 = faceLabels[A ( ei, 1 )];

        if ( label1 != label2 )
        {
            seamEdges.push_back ( ei );
        }

    }

    std::ofstream  ofs ( _outputFile.toStdString() );

    for ( int i = 0; i < seamEdges.size(); i++ )
    {
        ofs << seamEdges[i] << std::endl;
    }

    _outputFile = "";
}