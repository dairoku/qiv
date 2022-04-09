// =============================================================================
//  ImageView.cpp
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
  \file     ImageView.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

// Includes --------------------------------------------------------------------
#include <cmath>
#include "ImageView.h"

// -----------------------------------------------------------------------------
// ImageView
// -----------------------------------------------------------------------------
ImageView::ImageView(QWidget *parent, Qt::WindowFlags flags) :
        QWidget(parent, flags),
        mImageData(nullptr),
        mZoomScale(1.0),
        mImageSizeChangedFlag(false)
{
}

// -------------------------------------------------------------------------
// setImageData
// -------------------------------------------------------------------------
void ImageView::setImageData(ImageData *inImageData)
{
  if (mImageData != nullptr)
    mImageData->removeWidget(this);
  mImageData = inImageData;
  mImageData->addWidget(this);
  updateSizeUsingImageData();
}

// -------------------------------------------------------------------------
// updateWidget (from ViewDataInterface class)
// -------------------------------------------------------------------------
void ImageView::updateWidget()
{
  update();
}

// -------------------------------------------------------------------------
// setImageSizeChangedFlag (from ViewDataInterface class)
// -------------------------------------------------------------------------
void ImageView::setImageSizeChangedFlag(bool inFlag)
{
  mImageSizeChangedFlag = inFlag;
  update();
}

// -------------------------------------------------------------------------
// getZoomScale
// -------------------------------------------------------------------------
double ImageView::getZoomScale()
{
  return mZoomScale;
};

// -------------------------------------------------------------------------
// setZoomScale
// -------------------------------------------------------------------------
void ImageView::setZoomScale(double inScale)
{
  if (mImageData == nullptr)
    return;
  if (mImageData->getData() == nullptr)
    return;

  if (inScale <= 0.01)
    inScale = 0.01;
  mZoomScale = inScale;

  double scale = mZoomScale;
  int width = (int )(mImageData->getFormat().width() * scale);
  int height = (int )(mImageData->getFormat().height() * scale);
  resize(width, height);

  mZoomScale = inScale;
}

// -------------------------------------------------------------------------
// calcZoomScale
// -------------------------------------------------------------------------
double ImageView::calcZoomScale(int inStep)
{
  double  scale = mZoomScale * pow(10, inStep / 100.0);

  // 100% snap & 1% limit (just in case...)
  if (fabs(scale - 1.0) <= 0.01)
    scale = 1.0;
  if (scale <= 0.01)
    scale = 0.01;

  return scale;
}

// -----------------------------------------------------------------------------
// updateSizeUsingImageData
// -----------------------------------------------------------------------------
bool ImageView::updateSizeUsingImageData()
{
  if (mImageData == nullptr)
    return false;
  if (mImageData->getData() == nullptr)
    return false;

  setZoomScale(mZoomScale);
  return true;
}

// -----------------------------------------------------------------------------
// paintEvent
// -----------------------------------------------------------------------------
void ImageView::paintEvent([[maybe_unused]] QPaintEvent *event)
{
  if (mImageData == nullptr)
    return;
  if (mImageData->check() == false)
    return;
  if (mImageSizeChangedFlag)
  {
    updateSizeUsingImageData();
    mImageSizeChangedFlag = false;
  }

  mImageData->update();
  QRect rect(0, 0, size().width(), size().height());
  QPainter painter(this);
  mImageData->draw(painter, rect);
  //painter.drawText(rect, Qt::AlignCenter, "Hello, world");
}

