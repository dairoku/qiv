// =============================================================================
//  ImageScrollArea.cpp
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
  \file     ImageScrollArea.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

// Includes --------------------------------------------------------------------
#include "ImageScrollArea.h"

// -----------------------------------------------------------------------------
// ImageScrollArea
// -----------------------------------------------------------------------------
ImageScrollArea::ImageScrollArea(QWidget *parent)
  : QScrollArea(parent),
    mImageView(this)
{
  setBackgroundRole(QPalette::Dark);
  setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  setWidget(&mImageView);
}

// -----------------------------------------------------------------------------
// getImageView
// -----------------------------------------------------------------------------
ImageView *ImageScrollArea::getImageView()
{
  return &mImageView;
}

// -----------------------------------------------------------------------------
// mousePressEvent
// -----------------------------------------------------------------------------
void ImageScrollArea::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    mMousePreviousPos = event->pos();
  }
}

// -----------------------------------------------------------------------------
// mouseMoveEvent
// -----------------------------------------------------------------------------
void ImageScrollArea::mouseMoveEvent(QMouseEvent *event)
{
  QPoint  diff = mMousePreviousPos - event->pos();
  setScrollBarValueDiff(horizontalScrollBar(), diff.x());
  setScrollBarValueDiff(verticalScrollBar(), diff.y());
  mMousePreviousPos = event->pos();
}

// -----------------------------------------------------------------------------
// mouseReleaseEvent
// -----------------------------------------------------------------------------
void ImageScrollArea::mouseReleaseEvent([[maybe_unused]]QMouseEvent *event)
{
}

// -----------------------------------------------------------------------------
// wheelEvent
// -----------------------------------------------------------------------------
void ImageScrollArea::wheelEvent(QWheelEvent *wEvent)
{
  QPoint delta = wEvent->angleDelta();
  QPoint pos = mImageView.mapFromGlobal(wEvent->globalPos());
  QSize size = mImageView.size();
  double hOffset = pos.x() * (1.0 / mImageView.getZoomScale()); // Offset from the origin
  double vOffset = pos.y() * (1.0 / mImageView.getZoomScale());
  int x_offset = pos.x() - horizontalScrollBar()->value();  // Offset on the display
  int y_offset = pos.y() - verticalScrollBar()->value();

  int step = delta.y() / MOUSE_WHEEL_ZOOM_STEP;
  double scale = mImageView.calcZoomScale(step);
  mImageView.setZoomScale(scale);

  if (pos.x() >= 0 && pos.x() < size.width() &&
    pos.y() >= 0 && pos.y() < size.height())
  {
    int h = (int)(hOffset * mImageView.getZoomScale()) - x_offset;
    int v = (int)(vOffset * mImageView.getZoomScale()) - y_offset;
    setScrollBarValue(horizontalScrollBar(), h);
    setScrollBarValue(verticalScrollBar(), v);
  }
}

// -----------------------------------------------------------------------------
// setScrollBarValue
// -----------------------------------------------------------------------------
void ImageScrollArea::setScrollBarValue(QScrollBar *inBar, int inNewValue)
{
  if (inNewValue < inBar->minimum())
    inNewValue = inBar->minimum();
  if (inNewValue > inBar->maximum())
    inNewValue = inBar->maximum();
  inBar->setValue(inNewValue);
}

// -----------------------------------------------------------------------------
// setScrollBarValueDiff
// -----------------------------------------------------------------------------
void ImageScrollArea::setScrollBarValueDiff(QScrollBar *inBar, int inDiff)
{
  setScrollBarValue(inBar, inBar->value() + inDiff);
}
