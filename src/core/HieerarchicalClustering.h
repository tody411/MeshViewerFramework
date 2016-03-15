
/*!
  \file     HieerarchicalClustering.h
  \author   Tody
  HieerarchicalClustering definition.
  \date     2016/03/14
*/

#ifndef HIEERARCHICALCLUSTERING_H
#define HIEERARCHICALCLUSTERING_H

#include "Eigen/Dense"
#include <queue>

class HCQueData
{
public:
    double error;
    int c1;
    int c2;

    HCQueData()
        :  error ( 0 ), c1 ( -1 ), c2 ( -1 )
    {}

    HCQueData ( double error, int c1, int c2 )
        : error ( error ), c1 ( c1 ), c2 ( c2 )
    {}
};

//Overload the < operator.
bool operator< ( const HCQueData& data1, const HCQueData& data2 )
{
    return data1.error > data2.error;
}
//Overload the > operator.
bool operator> ( const HCQueData& data1, const HCQueData& data2 )
{
    return data1.error < data2.error;
}

typedef std::priority_queue< HCQueData, std::vector<HCQueData>, std::less<HCQueData> > HCQue;

//! HieerarchicalClustering implementation.
class HieerarchicalClustering
{
public :
    //! Constructor.
    HieerarchicalClustering ( const Eigen::MatrixXi& A_ef,
                              const Eigen::MatrixXd& N_f,
                              const Eigen::VectorXd& Area_f )
    {
        _A_ef = A_ef;
        _N_f = N_f;
        _Area_f = Area_f;
    }

    //! Destructor.
    virtual ~HieerarchicalClustering() {}

    void compute ( Eigen::VectorXi& clusterIDs );

private:
    void fit ( const Eigen::VectorXi& clusterIDs );

    void pushEdges ( const Eigen::VectorXi& clusterIDs, HCQue& edgeQue );

    void mergeClusters ( int c1, int c2, Eigen::VectorXi& clusterIDs );

private:
    Eigen::MatrixXi _A_ef;
    Eigen::MatrixXd _N_f;
    Eigen::VectorXd _Area_f;

    Eigen::MatrixXd _N_c;
    Eigen::VectorXd _Area_c;
    Eigen::VectorXd _E_c;
};

#endif

