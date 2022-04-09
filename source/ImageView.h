// =============================================================================
//  ImageView.h
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
  \file     ImageView.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/
#ifndef QIV_IMAGE_VIEW_H
#define QIV_IMAGE_VIEW_H

// Includes --------------------------------------------------------------------
#include <QtWidgets>
#include "ImageData.h"

// -----------------------------------------------------------------------------
// ImageView class
// -----------------------------------------------------------------------------
class ImageView : public QWidget, virtual public ViewDataInterface
{
Q_OBJECT

public:
  // Constructors and Destructor -----------------------------------------------
  ImageView(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

  // Member functions ----------------------------------------------------------
  virtual void    updateWidget();
  virtual void    setImageSizeChangedFlag(bool inFlag);

  void setImageData(ImageData *inImageData);
  double getZoomScale();
  void setZoomScale(double inScale);
  double calcZoomScale(int inStep);

protected:
  // Member functions ----------------------------------------------------------
  bool  updateSizeUsingImageData();
  void paintEvent(QPaintEvent *event) override;

private:
  // Member variables ----------------------------------------------------------
  ImageData *mImageData;
  double    mZoomScale;
  bool mImageSizeChangedFlag;
};


#endif //QIV_IMAGE_VIEW_H
