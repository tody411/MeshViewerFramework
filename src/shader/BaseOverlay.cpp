
/*!
  \file		BaseOverlay.cpp
  \author		Tody
  BaseOverlay definition.
  date		2015/12/16
*/

#include "BaseOverlay.h"


void BaseOverlay::setAttr1(int attr1)
{
	_attr1 = attr1;
}
void BaseOverlay::setAttr2(double attr2)
{
	_attr2 = attr2;
}
void BaseOverlay::setAttr2(const cv::Mat& attr2)
{
	_attr2 = attr2;
}
