
/*!
  \file     LabelData.h
  \author   Tody
  LabelData definition.
  \date     2016/02/26
*/

#ifndef LABELDATA_H
#define LABELDATA_H

#include "SceneObject.h"

#include <Eigen/Dense>
#include <vector>

//! LabelData implementation.
class LabelData : public SceneObject
{
public :
    static const int UNLABELED = -1;

    //! Constructor.
    LabelData ( Scene* scene )
        : SceneObject ( scene )
    {}

    //! Destructor.
    virtual ~LabelData() {}

    bool empty() const;

    void clear();

    void resize ( int size );

    int numLabels();

    void setFaceLabelData ( const std::vector<int>& faceLabels );

    void setFaceLabelData ( const Eigen::VectorXi& faceLabels );

    void setFaceLabelData ( const std::vector<int>& indices, int label );

    void setFaceLabelConfidents ( const std::vector<double>& labelConfidents );

    void setFaceLabelConfidents ( const std::vector<int>& indices, double w );

    int getFaceLabel ( int index );

    void faceLabelData ( std::vector<int>& faceLabels ) const;

    void labelShell ( int label,  std::vector<int>& shellFaces ) const;

    void faceLabelConfidentsData ( std::vector<double>& faceLabelConfidents ) const;

    void gl();

private:

private:
    std::vector<int> _faceLabels;
    std::vector<double> _faceLabelConfidents;

};

#endif

