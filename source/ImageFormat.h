// =============================================================================
//  ImageFormat.h
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
  \file     ImageFormat.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/26
*/

#ifndef QIV_IMAGE_FORMAT_H
#define QIV_IMAGE_FORMAT_H

// Includes --------------------------------------------------------------------
#include "ImageType.h"

// -----------------------------------------------------------------------------
// ImageFormat class
// -----------------------------------------------------------------------------
class  ImageFormat
{
public:
  ImageFormat();
  ImageFormat(const ImageType &inType,
              unsigned int inWidth, unsigned int inHeight,
              bool inIsBottomUp = false,
              size_t inBufferSize = 0,
              size_t inHeaderOffset = 0,
              size_t inPixelStep = 0,
              size_t inLineStep = 0,
              size_t inChannelStep = 0);
  virtual ~ImageFormat();

  // Member functions ----------------------------------------------------------
  bool isValid() const;
  const ImageType &type() const;
  unsigned int width() const;
  unsigned int height() const;
  bool  isBottomUp() const;
  size_t  bufferSize() const;
  size_t headerOffset() const;
  size_t pixelStep() const;
  size_t lineStep() const;
  size_t channelStep() const;
  size_t pixelAreaSize() const;

  size_t planeOffset(unsigned int inPlaneIndex = 0) const;
  size_t lineOffset(unsigned int inY = 0, unsigned int inPlaneIndex = 0) const;
  size_t pixelOffset(unsigned int inX = 0, unsigned int inY = 0, unsigned int inPlaneIndex = 0) const;

  void *planePtr(void *inBufferPtr, unsigned int inPlaneIndex = 0) const;
  const void *planePtr(const void *inBufferPtr, unsigned int inPlaneIndex = 0) const;
  void *linePtr(void *inBufferPtr, unsigned int inY, unsigned int inPlaneIndex = 0) const;
  const void *linePtr(const void *inBufferPtr, unsigned int inY, unsigned int inPlaneIndex = 0) const;
  void *pixelPtr(void *inBufferPtr, unsigned int inX, unsigned int inY, unsigned int inPlaneIndex = 0) const;
  const void *pixelPtr(const void *inBufferPtr, unsigned int inX, unsigned int inY, unsigned int inPlaneIndex = 0) const;
  void *pixelPtr(void *inBufferPtr) const;
  const void *pixelPtr(const void *inBufferPtr) const;

  void invalidate();
  void  set(const ImageType &inType,
              unsigned int inWidth, unsigned int inHeight,
              bool inIsBottomUp = false,
              size_t inBufferSize = 0,
              size_t inHeaderOffset = 0,
              size_t inPixelStep = 0,
              size_t inLineStep = 0,
              size_t inChannelStep = 0);
  void  set(unsigned int inWidth, unsigned int inHeight,
              bool inIsBottomUp = false,
              size_t inBufferSize = 0,
              size_t inHeaderOffset = 0,
              size_t inPixelStep = 0,
              size_t inLineStep = 0,
              size_t inChannelStep = 0);

  void  dump(const char *inLeadringStr = "");

  // Static Functions ----------------------------------------------------------
  static void *getPixelPtr(const ImageFormat &inFormat, void *inBufferPtr);
  static const void *getPixelPtr(const ImageFormat &inFormat, const void *inBufferPtr);
  static size_t calculatePlaneOffset(
                          const ImageFormat &inFormat,
                          unsigned int inPlaneIndex = 0);
  static size_t calculateLineOffsetFromPlaneOffset(
                            const ImageFormat &inFormat,
                            size_t inPlaneOffset,
                            unsigned int inY);
  static size_t calculateLineOffset(
                            const ImageFormat &inFormat,
                            unsigned int inY,
                            unsigned int inPlaneIndex);
  static size_t calculatePixelOffsetFromLineOffset(
                            const ImageFormat &inFormat,
                            size_t inLineOffset,
                            unsigned int inX);
  static size_t calculatePixelOffsetFromPlaneOffset(
                            const ImageFormat &inFormat,
                            size_t inPlaneOffset,
                            unsigned int inX,
                            unsigned int inY);
  static size_t calculatePixelOffset(
                            const ImageFormat &inFormat,
                            unsigned int inX,
                            unsigned int inY,
                            unsigned int inPlaneIndex = 0);

private:
  // Member variables ----------------------------------------------------------
  ImageType       mImageType;
  unsigned int    mWidth;
  unsigned int    mHeight;
  bool            mIsBottomUp;
  size_t          mBufferSize;
  size_t          mHeaderOffset;
  size_t          mPixelStep;
  size_t          mLineStep;
  size_t          mChannelStep;
  size_t          mPixelAreaSize;
};

#endif //QIV_IMAGE_FORMAT_H
