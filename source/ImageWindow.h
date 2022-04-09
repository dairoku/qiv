// =============================================================================
//  ImageWindow.h
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
  \file     ImageWindow.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

#ifndef QIV_IMAGE_WINDOW_H
#define QIV_IMAGE_WINDOW_H

// Includes --------------------------------------------------------------------
#include <QtWidgets>
#include "ImageScrollArea.h"

// -----------------------------------------------------------------------------
// ImageWindow class
// -----------------------------------------------------------------------------
class ImageWindow : public QMdiSubWindow
{
Q_OBJECT

public:
  // Constructors and Destructor -----------------------------------------------
  ImageWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private:
  // Member variables ----------------------------------------------------------
  ImageScrollArea mImageScrollArea;
  // TODO: We should separate the following object
  ImageData mImageData;
};

#endif //QIV_IMAGE_WINDOW_H
