
/*!
  \file     PhongShaderCommand.h
  \author   Tody
  PhongShaderCommand definition.
  \date     2015/12/24
*/

#ifndef PHONGSHADERCOMMAND_H
#define PHONGSHADERCOMMAND_H

#include "BaseCommand.h"

//! PhongShaderCommand implementation.
class PhongShaderCommand : public BaseCommand
{
public :
    //! Constructor.
    PhongShaderCommand ( Scene* scene )
        :  BaseCommand ( "Phong Shader", scene )
    {}

    //! Destructor.
    virtual ~PhongShaderCommand() {}

    void doImp ();



};

#endif

