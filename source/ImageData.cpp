// =============================================================================
//  ImageData.cpp
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
  \file     ImageBuffer.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/26
*/

// Includes --------------------------------------------------------------------
#include <cstring>
#include "ImageData.h"

// -----------------------------------------------------------------------------
// ImageData
// -----------------------------------------------------------------------------
ImageData::ImageData()
{
  mImageBuffer = nullptr;
  setImageModifiedFlag(false);
  mQImage = nullptr;
}

// -----------------------------------------------------------------------------
// ~ImageData
// -----------------------------------------------------------------------------
ImageData::~ImageData()
{
  disposeQImage();

  if (mImageBuffer != nullptr)
    delete mImageBuffer;
}

// Member functions ------------------------------------------------------------
// -----------------------------------------------------------------------------
// allocate
// -----------------------------------------------------------------------------
bool ImageData::allocate(const ImageFormat &inFormat)
{
  if (inFormat.isValid() == false)
    return false;

  if (mImageBuffer != nullptr)
  {
    if (mImageFormat.bufferSize() == inFormat.bufferSize())
    {
      mImageFormat = inFormat;
      return true;
    }
    delete mImageBuffer;
    mImageBuffer = nullptr;
  }

  mImageFormat = inFormat;
  mImageBuffer = new unsigned char[mImageFormat.bufferSize()];
  if (mImageBuffer == nullptr)
    return false;

  parameterModified();
  return true;
}

// -----------------------------------------------------------------------------
// copy
// -----------------------------------------------------------------------------
bool ImageData::copy(const void *inImagePtr, const ImageFormat &inFormat)
{
  if (allocate(inFormat) == false)
    return false;

  memcpy(mImageBuffer, inImagePtr, mImageFormat.bufferSize());

  setImageModifiedFlag(true);
  return true;
}

// -----------------------------------------------------------------------------
// check
// -----------------------------------------------------------------------------
bool ImageData::check() const
{
  if (getData() == nullptr || mQImage == nullptr || mImageFormat.isValid() == false)
    return false;
  return true;
}

// -----------------------------------------------------------------------------
// getData
// -----------------------------------------------------------------------------
void *ImageData::getData() const
{
  return mImageBuffer;
}

// -----------------------------------------------------------------------------
// getFormat
// -----------------------------------------------------------------------------
const ImageFormat &ImageData::getFormat() const
{
  return mImageFormat;
}

// -----------------------------------------------------------------------------
// setImageModifiedFlag
// -----------------------------------------------------------------------------
void  ImageData::setImageModifiedFlag(bool inFlag)
{
  mImageModifiedFlag = inFlag;
}

// -----------------------------------------------------------------------------
// getImageModifiedFlag
// -----------------------------------------------------------------------------
bool  ImageData::getImageModifiedFlag() const
{
  return mImageModifiedFlag;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
bool ImageData::update(bool inForceUpdate)
{
  if (inForceUpdate == false && getImageModifiedFlag() == false)
    return false;

  if (check() == false)
    return false;

  // Sanity check here
  if ((unsigned int )mQImage->width()  != mImageFormat.width() ||
      (unsigned int )mQImage->height() != mImageFormat.height())
    return false; // Should throw exception?

  // TODO: this code assumes that ImageType is PIXEL_TYPE_MONO
  unsigned char *src = (unsigned char *)mImageBuffer;
  unsigned char *dst = (unsigned char *)mQImage->bits();
  size_t bufSize = mImageFormat.bufferSize();

  for (size_t i = 0; i < bufSize; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      *dst = *src;
      dst++;
    }
    src++;
  }

  setImageModifiedFlag(false);
  return true;
}

// -----------------------------------------------------------------------------
// draw
// -----------------------------------------------------------------------------
void ImageData::draw(QPainter &inPainter, const QRect &rect)
{
  inPainter.drawImage(rect, *mQImage);
}

// -----------------------------------------------------------------------------
// addWidget
// -----------------------------------------------------------------------------
void  ImageData::addWidget(ViewDataInterface *inWidget)
{
  mWidgetList.push_back(inWidget);
}

// -----------------------------------------------------------------------------
// removeWidget
// -----------------------------------------------------------------------------
void  ImageData::removeWidget(ViewDataInterface *inWidget)
{
  auto it = std::find(mWidgetList.begin(), mWidgetList.end(), inWidget);
  if (it == mWidgetList.end())
    return;
  mWidgetList.erase(it);
}

// -----------------------------------------------------------------------------
// redrawAllWidgets
// -----------------------------------------------------------------------------
void  ImageData::redrawAllWidgets()
{
  for (auto it = mWidgetList.begin(); it != mWidgetList.end(); it++)
    (*it)->updateWidget();
}

// -----------------------------------------------------------------------------
// parameterModified
// -----------------------------------------------------------------------------
void  ImageData::parameterModified()
{
  disposeQImage();
  mQImage = new QImage(mImageFormat.width(), mImageFormat.height(),
                       QImage::Format_RGB888);

  setImageModifiedFlag(false);
  for (auto it = mWidgetList.begin(); it != mWidgetList.end(); it++)
    (*it)->setImageSizeChangedFlag(true);
}

// -----------------------------------------------------------------------------
// disposeQImage
// -----------------------------------------------------------------------------
void  ImageData::disposeQImage()
{
  if (mQImage == nullptr)
    return;
  delete mQImage;
  mQImage = nullptr;
}
