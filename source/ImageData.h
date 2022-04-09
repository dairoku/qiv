// =============================================================================
//  ImageData.h
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
  \file     ImageBuffer.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/26
*/
#ifndef QIV_IMAGE_DATA_H
#define QIV_IMAGE_DATA_H

// Includes --------------------------------------------------------------------
#include <vector>
#include <QImage>
#include <QPainter>
#include "ImageFormat.h"
#include "ViewDataInterface.h"

// -----------------------------------------------------------------------------
// ImageData class
// -----------------------------------------------------------------------------
class ImageData
{
public:
  // Constructors and Destructor -----------------------------------------------
  ImageData();
  virtual ~ImageData();

  // Member functions ----------------------------------------------------------
  bool allocate(const ImageFormat &inFormat);
  bool copy(const void *inImagePtr, const ImageFormat &inFormat);
  bool check() const;

  void *getData() const;
  const ImageFormat &getFormat() const;

  void setImageModifiedFlag(bool inFlag);
  bool getImageModifiedFlag() const;

  virtual bool  update(bool inForceUpdate = false);
  void draw(QPainter &inPainter, const QRect &rect);

  void  addWidget(ViewDataInterface *inWidget);
  void  removeWidget(ViewDataInterface *inWidget);
  void  redrawAllWidgets();

private:
  // Member variables ----------------------------------------------------------
  ImageFormat   mImageFormat;
  unsigned char *mImageBuffer;
  bool  mImageModifiedFlag;

  QImage  *mQImage;
  std::vector<ViewDataInterface *>  mWidgetList;

  // Member functions ----------------------------------------------------------
  void  parameterModified();
  void  disposeQImage();
};

#endif //QIV_IMAGE_DATA_H
