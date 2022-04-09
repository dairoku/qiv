/// =============================================================================
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
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "ImageFormat.h"


// -----------------------------------------------------------------------------
// ImageFormat
// -----------------------------------------------------------------------------
ImageFormat::ImageFormat()
{
  invalidate();
}

// -----------------------------------------------------------------------------
// ImageFormat
// -----------------------------------------------------------------------------
ImageFormat::ImageFormat(const ImageType &inType,
            unsigned int inWidth, unsigned int inHeight,
            bool inIsBottomUp,
            size_t inBufferSize,
            size_t inHeaderOffset,
            size_t inPixelStep,
            size_t inLineStep,
            size_t inChannelStep)
{
  set(inType,
      inWidth, inHeight,
      inIsBottomUp,
      inBufferSize, inHeaderOffset,
      inPixelStep, inLineStep, inChannelStep);
}

// -----------------------------------------------------------------------------
// ~ImageFormat
// -----------------------------------------------------------------------------
ImageFormat::~ImageFormat()
{
}

// -----------------------------------------------------------------------------
// isValid
// -----------------------------------------------------------------------------
bool ImageFormat::isValid() const
{
  if (mWidth == 0 || mHeight == 0 || mBufferSize == 0 || mPixelStep == 0 ||
      mLineStep == 0 || mChannelStep == 0 || mPixelAreaSize == 0)
    return false;

  return mImageType.isValid();
}

// -----------------------------------------------------------------------------
// type
// -----------------------------------------------------------------------------
const ImageType &ImageFormat::type() const
{
  return mImageType;
}

// -----------------------------------------------------------------------------
// width
// -----------------------------------------------------------------------------
unsigned int ImageFormat::width() const
{
  return mWidth;
}

// -----------------------------------------------------------------------------
// height
// -----------------------------------------------------------------------------
unsigned int ImageFormat::height() const
{
  return mHeight;
}

// -----------------------------------------------------------------------------
// isBottomUp
// -----------------------------------------------------------------------------
bool ImageFormat::isBottomUp() const
{
  return mIsBottomUp;
}

// -----------------------------------------------------------------------------
// bufferSize
// -----------------------------------------------------------------------------
size_t ImageFormat::bufferSize() const
{
  return mBufferSize;
}

// -----------------------------------------------------------------------------
// headerOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::headerOffset() const
{
  return mHeaderOffset;
}

// -----------------------------------------------------------------------------
// pixelStep
// -----------------------------------------------------------------------------
size_t ImageFormat::pixelStep() const
{
  return mPixelStep;
}

// -----------------------------------------------------------------------------
// lineStep
// -----------------------------------------------------------------------------
size_t ImageFormat::lineStep() const
{
  return mLineStep;
}

// -----------------------------------------------------------------------------
// channelStep
// -----------------------------------------------------------------------------
size_t ImageFormat::channelStep() const
{
  return mChannelStep;
}

// -----------------------------------------------------------------------------
// pixelAreaSize
// -----------------------------------------------------------------------------
size_t ImageFormat::pixelAreaSize() const
{
  return mPixelAreaSize;
}

// -----------------------------------------------------------------------------
// planeOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::planeOffset(unsigned int inPlaneIndex) const
{
  return calculatePlaneOffset(*this, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// lineOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::lineOffset(unsigned int inY, unsigned int inPlaneIndex) const
{
  return calculateLineOffset(*this, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// pixelOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::pixelOffset(unsigned int inX, unsigned int inY,
                                unsigned int inPlaneIndex) const
{
  return calculatePixelOffset(*this, inX, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// planePtr
// -----------------------------------------------------------------------------
void *ImageFormat::planePtr(void *inBufferPtr, unsigned int inPlaneIndex) const
{
  return ((unsigned char *)inBufferPtr) + calculatePlaneOffset(*this, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// planePtr
// -----------------------------------------------------------------------------
const void *ImageFormat::planePtr(const void *inBufferPtr,
                                  unsigned int inPlaneIndex) const
{
  return ((const unsigned char *)inBufferPtr) + calculatePlaneOffset(*this, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// linePtr
// -----------------------------------------------------------------------------
void *ImageFormat::linePtr(void *inBufferPtr, unsigned int inY,
                           unsigned int inPlaneIndex) const
{
  return ((unsigned char *)inBufferPtr) + calculateLineOffset(*this, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// linePtr
// -----------------------------------------------------------------------------
const void *ImageFormat::linePtr(const void *inBufferPtr, unsigned int inY,
                                 unsigned int inPlaneIndex) const
{
  return ((const unsigned char *)inBufferPtr) + calculateLineOffset(*this, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
void *ImageFormat::pixelPtr(void *inBufferPtr, unsigned int inX, unsigned int inY,
                            unsigned int inPlaneIndex) const
{
  return ((unsigned char *)inBufferPtr) + calculatePixelOffset(*this, inX, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
const void *ImageFormat::pixelPtr(const void *inBufferPtr, unsigned int inX,
                                  unsigned int inY, unsigned int inPlaneIndex) const
{
  return ((const unsigned char *)inBufferPtr) + calculatePixelOffset(*this, inX, inY, inPlaneIndex);
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
void *ImageFormat::pixelPtr(void *inBufferPtr) const
{
  return getPixelPtr(*this, inBufferPtr);
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
const void *ImageFormat::pixelPtr(const void *inBufferPtr) const
{
  return getPixelPtr(*this, inBufferPtr);
}

// -----------------------------------------------------------------------------
// invalidate
// -----------------------------------------------------------------------------
void ImageFormat::invalidate()
{
  mImageType.invalidate();

  mWidth          = 0;
  mHeight         = 0;
  mIsBottomUp     = false;
  mBufferSize     = 0;
  mHeaderOffset   = 0;
  mPixelStep      = 0;
  mLineStep       = 0;
  mChannelStep    = 0;
  mPixelAreaSize  = 0;
}

// -----------------------------------------------------------------------------
// set
// -----------------------------------------------------------------------------
void ImageFormat::set(const ImageType &inType,
            unsigned int inWidth, unsigned int inHeight,
            bool inIsBottomUp,
            size_t inBufferSize,
            size_t inHeaderOffset,
            size_t inPixelStep,
            size_t inLineStep,
            size_t inChannelStep)
{
  mImageType = inType;
  set(inWidth, inHeight,
      inIsBottomUp,
      inBufferSize, inHeaderOffset,
      inPixelStep, inLineStep, inChannelStep);
}

// -----------------------------------------------------------------------------
// set
// -----------------------------------------------------------------------------
void ImageFormat::set(unsigned int inWidth, unsigned int inHeight,
            bool inIsBottomUp,
            size_t inBufferSize,
            size_t inHeaderOffset,
            size_t inPixelStep,
            size_t inLineStep,
            size_t inChannelStep)
{
  mWidth          = inWidth;
  mHeight         = inHeight;
  mIsBottomUp     = inIsBottomUp;
  mHeaderOffset   = inHeaderOffset;
  if (inPixelStep != 0)
    mPixelStep = inPixelStep; // TODO: Add a sanity check here...
  else
  {
    if (mImageType.isPacked() || mImageType.hasMacroPixelStructure())
      mPixelStep = 0;
    else
    {
      mPixelStep = mImageType.sizeOfData();
      if (mImageType.isPlanar() == false)
        mPixelStep *= mImageType.componentsPerPixel();
    }
  }
  if (inLineStep != 0)
    mLineStep = inLineStep; // TODO: Add a sanity check here...
  else
    mLineStep = mPixelStep * mWidth;
  if (inChannelStep != 0)
    mChannelStep = inChannelStep;  // TODO: Add a sanity check here...
  else
    mChannelStep = mLineStep * mHeight;  // TODO: this assumption doesn't cover everything...
  //
  if (mImageType.isPlanar())
    mPixelAreaSize = mChannelStep * mImageType.componentsPerPixel();
  else
    mPixelAreaSize = mChannelStep;
  //
  if (inBufferSize != 0)
    mBufferSize = inBufferSize;
  else
    mBufferSize = mHeaderOffset + mPixelAreaSize;
}

// -----------------------------------------------------------------------------
// dump
// -----------------------------------------------------------------------------
void  ImageFormat::dump(const char *inLeadringStr)
{
  char  buf[256];
  if (strlen(inLeadringStr) < (sizeof(buf) - 10))
    sprintf(buf, "%s  ", inLeadringStr);
  else
    sprintf(buf, "  ");
  //
  printf("%smImageType:\n", inLeadringStr);
  mImageType.dump(buf);
  printf("%smWidth          : %d\n", inLeadringStr, mWidth);
  printf("%smHeight         : %d\n", inLeadringStr, mHeight);
  printf("%smIsBottomUp     : %d\n", inLeadringStr, mIsBottomUp);
  printf("%smBufferSize     : %zu\n", inLeadringStr, mBufferSize);
  printf("%smHeaderOffset   : %zu\n", inLeadringStr, mHeaderOffset);
  printf("%smPixelStep      : %zu\n", inLeadringStr, mPixelStep);
  printf("%smLineStep       : %zu\n", inLeadringStr, mLineStep);
  printf("%smChannelStep    : %zu\n", inLeadringStr, mChannelStep);
  printf("%smPixelAreaSize  : %zu\n", inLeadringStr, mPixelAreaSize);
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
void *ImageFormat::getPixelPtr(const ImageFormat &inFormat, void *inBufferPtr)
{
  unsigned char *pixelPtr = (unsigned char *)inBufferPtr;
  pixelPtr += inFormat.mHeaderOffset;
  return pixelPtr;
}

// -----------------------------------------------------------------------------
// pixelPtr
// -----------------------------------------------------------------------------
const void *ImageFormat::getPixelPtr(const ImageFormat &inFormat, const void *inBufferPtr)
{
  unsigned char *pixelPtr = (unsigned char *)inBufferPtr;
  pixelPtr += inFormat.mHeaderOffset;
  return pixelPtr;
}

// -----------------------------------------------------------------------------
// calculatePlaneOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculatePlaneOffset(
                        const ImageFormat &inFormat,
                        unsigned int inPlaneIndex)
{
  if (inFormat.mImageType.isPlanar() == false)
    return inFormat.mHeaderOffset;
  if (inPlaneIndex >= inFormat.mImageType.componentsPerPixel())
    inPlaneIndex = inFormat.mImageType.componentsPerPixel() - 1;
  // TODO : we need to think about a format that has MacroPixel Structure with a planner buffer
  return inFormat.mChannelStep * inPlaneIndex + inFormat.mHeaderOffset;
}

// -----------------------------------------------------------------------------
// calculateLineOffsetFromPlaneOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculateLineOffsetFromPlaneOffset(
                          const ImageFormat &inFormat,
                          size_t inPlaneOffset,
                          unsigned int inY)
{
  if (inY >= inFormat.mHeight)
    inY = inFormat.mHeight - 1;
  if (inY == 0)
    return inPlaneOffset;
  return inPlaneOffset + inFormat.mLineStep * inY;
}

// -----------------------------------------------------------------------------
// calculateLineOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculateLineOffset(
                          const ImageFormat &inFormat,
                          unsigned int inY,
                          unsigned int inPlaneIndex)
{
  return calculateLineOffsetFromPlaneOffset(
                              inFormat,
                              calculatePlaneOffset(inFormat, inPlaneIndex),
                              inY);
}

// -----------------------------------------------------------------------------
// calculatePixelOffsetFromLineOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculatePixelOffsetFromLineOffset(
                          const ImageFormat &inFormat,
                          size_t inLineOffset,
                          unsigned int inX)
{
  if (inX >= inFormat.mWidth)
    inX = inFormat.mWidth - 1;
  return inLineOffset + inFormat.mPixelStep * inX;
}

// -----------------------------------------------------------------------------
// calculatePixelOffsetFromPlaneOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculatePixelOffsetFromPlaneOffset(
                          const ImageFormat &inFormat,
                          size_t inPlaneOffset,
                          unsigned int inX,
                          unsigned int inY)
{
  return calculatePixelOffsetFromLineOffset(
                              inFormat,
                              calculateLineOffsetFromPlaneOffset(inFormat, inPlaneOffset, inY),
                              inX);
}

// -----------------------------------------------------------------------------
// calculatePixelOffset
// -----------------------------------------------------------------------------
size_t ImageFormat::calculatePixelOffset(
                          const ImageFormat &inFormat,
                          unsigned int inX,
                          unsigned int inY,
                          unsigned int inPlaneIndex)
{
  return calculatePixelOffsetFromLineOffset(
                              inFormat,
                              calculateLineOffset(inFormat, inY, inPlaneIndex),
                              inX);
}
