
//! PrimitiveFitting definition.
/*!
  \file     PrimitiveFitting.h
  \author   Tody
  \date     2016/03/03
*/

#ifndef PRIMITIVEFITTING_H
#define PRIMITIVEFITTING_H

#include "Eigen/Dense"

#include <memory>
#include <vector>

class BasePrimitiveFitting
{
public :
    //! Constructor.
    BasePrimitiveFitting() {}

    //! Destructor.
    virtual ~BasePrimitiveFitting() {}

    virtual void fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N ) {}

    virtual void error ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E ) {}

    virtual void project ( const Eigen::MatrixXd& V, Eigen::MatrixXd& V_proj ) {}

    virtual void info() {}
};

class PrimitiveKMeans
{
public:
    //! Constructor.
    PrimitiveKMeans ()
        : _numIterations ( 1 )
    {}

    //! Destructor.
    virtual ~PrimitiveKMeans();

    void fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N );

    //! Set NumIterations.
    void setNumIterations ( int numIterations ) { _numIterations = numIterations;}

    //! Set NumCenters.
    void setNumCenters ( int numCenters ) { _numCenters = numCenters;}

    //! Out clusterIDs.
    const Eigen::VectorXi clusterIDs() const { return _clusterIDs;}

private:
    void computeRandomCenters ( int numCenters, int numData, Eigen::VectorXi& clusterIDs );

    void clusterData ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N, int clusterID, Eigen::MatrixXd& V_c, Eigen::MatrixXd& N_c );

    void fitPrimitives ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N );

    void updateClusters ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N );

private:
    //! Number of iterations.
    int _numIterations;

    //! Number of cluster centers.
    int             _numCenters;

    //! Cluster ids.
    Eigen::VectorXi _clusterIDs;

    typedef std::shared_ptr<BasePrimitiveFitting> PrimitivePtr;

    std::vector<PrimitivePtr> _primitives;
};


//! PlaneFitting implementation.
class PlaneFitting : public BasePrimitiveFitting
{
public :
    //! Constructor.
    PlaneFitting()
        : _center ( 0, 0, 0 ), _normal ( 1, 0, 0 )
    {}

    //! Destructor.
    virtual ~PlaneFitting() {}

    void fitPosition ( const Eigen::MatrixXd& V );

    virtual void fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N );

    virtual void error ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E );

    virtual void project ( const Eigen::MatrixXd& V, Eigen::MatrixXd& V_proj );

    virtual void info();

private:
    Eigen::Vector3d _center;
    Eigen::Vector3d _normal;
};


//! QuadricSurfaceFitting implementation.
class QuadricSurfaceFitting : public BasePrimitiveFitting
{
public :
    //! Constructor.
    QuadricSurfaceFitting()
    {}

    //! Destructor.
    virtual ~QuadricSurfaceFitting() {}

    virtual void fit ( const Eigen::MatrixXd& V,  const Eigen::MatrixXd& N );

    virtual void error ( const Eigen::MatrixXd& V, const Eigen::MatrixXd& N, Eigen::VectorXd& E );

    virtual void project ( const Eigen::MatrixXd& V, Eigen::MatrixXd& V_proj ) {}

    virtual void info() ;

private:
    void computeF ( const Eigen::MatrixXd& V, Eigen::MatrixXd& F );

private:
    Eigen::VectorXd _C;
};


#endif

