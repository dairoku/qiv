// =============================================================================
//  ViewDataInterface.h
//
//  Written in 2022 by Dairoku Sekiguchi (sekiguchi at acm dot org)
//
//  To the extent possible under law, the author(s) have dedicated all copyright
//  and related and neighboring rights to this software to the public domain worldwide.
//  This software is distributed without any warranty.
//
//  You should have received a copy of the CC0 Public Domain Dedication along with
//  this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
// =============================================================================
/*!
  \file     ViewDataInterface.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/04/03
*/
#ifndef QIB_VIEW_DATA_INTERFACE_H
#define QIB_VIEW_DATA_INTERFACE_H

// Includes --------------------------------------------------------------------
#include <vector>

// -----------------------------------------------------------------------------
// ViewDataInterface interface class
// -----------------------------------------------------------------------------
class ViewDataInterface
{
public:
  // Member functions ----------------------------------------------------------
  virtual void    updateWidget()   = 0;
  virtual void    setImageSizeChangedFlag(bool inFlag)   = 0;
};

#endif //QIB_VIEW_DATA_INTERFACE_H
