// =============================================================================
//  ImageScrollArea.h
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
  \file     ImageScrollArea.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

#ifndef QIV_IMAGE_SCROLL_AREA_H
#define QIV_IMAGE_SCROLL_AREA_H

// Includes --------------------------------------------------------------------
#include <QtWidgets>
#include "ImageView.h"

// -----------------------------------------------------------------------------
// ImageScrollArea class
// -----------------------------------------------------------------------------
class ImageScrollArea : public QScrollArea
{
Q_OBJECT

public:
  // Constants -----------------------------------------------------------------
  //const static int    ZOOM_STEP_DEFAULT     = 1;
  const static int    MOUSE_WHEEL_ZOOM_STEP = 60;

  // Constructors and Destructor -----------------------------------------------
  ImageScrollArea(QWidget *parent = Q_NULLPTR);

  // Member functions ----------------------------------------------------------
  ImageView *getImageView();

protected:
  // Member variables ----------------------------------------------------------
  ImageView mImageView;
  QPoint  mMousePreviousPos;

  // Member functions ----------------------------------------------------------
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *wEvent) override;

private:
  // Member functions ----------------------------------------------------------
  void setScrollBarValue(QScrollBar *inBar, int inNewValue);
  void setScrollBarValueDiff(QScrollBar *inBar, int inDiff);
};

#endif //QIV_IMAGE_SCROLL_AREA_H
