// =============================================================================
//  ImageWindow.cpp
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
  \file     ImageWindow.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

// Includes --------------------------------------------------------------------
#include "ImageWindow.h"

// -----------------------------------------------------------------------------
// ImageWindow
// -----------------------------------------------------------------------------
ImageWindow::ImageWindow(QWidget *parent, Qt::WindowFlags flags)
  : QMdiSubWindow(parent, flags),
    mImageScrollArea(this)
{
  setWidget(&mImageScrollArea);

  ImageType imageType(ImageType::PIXEL_TYPE_MONO, ImageType::BUFFER_TYPE_PIXEL_ALIGNED,
                      ImageType::DATA_TYPE_8BIT);
  ImageFormat format(imageType, 640, 480);
  mImageData.allocate(format);
  unsigned char *buf = (unsigned char *) mImageData.getData();

  for (int y = 0; y < 480; y++)
    for (int x = 0; x < 640; x++, buf++)
      *buf = x ^ y;

  mImageData.setImageModifiedFlag(true);
  mImageScrollArea.getImageView()->setImageData(&mImageData);
}
