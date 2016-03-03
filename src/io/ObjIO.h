
/*!
  \file     ObjIO.h
  \author   Tody
  ObjIO definition.
  \date     2016/02/29
*/

#ifndef OBJIO_H
#define OBJIO_H

#include <QString>

class Mesh;

//! ObjIO implementation.
class ObjIO
{
public :
    //! Constructor.
    ObjIO() {}

    //! Destructor.
    virtual ~ObjIO() {}

    void saveMesh ( const QString& filePath, const Mesh& mesh );

private:



};

#endif

