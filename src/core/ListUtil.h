
/*!
  \file     ListUtil.h
  \author   Tody
  ListUtil definition.
  \date     2016/03/01
*/

#ifndef LISTUTIL_H
#define LISTUTIL_H

#include <vector>

//! ListUtil implementation.
namespace ListUtil
{
    template<typename DataType>
    void fill ( std::vector<DataType>& list, DataType data )
    {
        for ( int i = 0; i < list.size(); i++ )
        {
            list[i] = data;
        }
    }
};

#endif

