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
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "ImageType.h"

// Local Typedefs --------------------------------------------------------------
typedef struct
{
  ImageType::PixelType type;
  const char  *str;
} PixelTypeTable;
typedef struct
{
  ImageType::BufferType type;
  const char  *str;
} BufferTypeTable;
typedef struct
{
  ImageType::DataType type;
  const char  *str;
} DataTypeTable;
typedef struct
{
  ImageType::EndianType type;
  const char  *str;
} EndianTypeTable;

// Local Tables ----------------------------------------------------------------
const PixelTypeTable  kPixelTypeTable[] =
{
  {ImageType::ImageType::PIXEL_TYPE_RAW,        "RAW"},
  {ImageType::PIXEL_TYPE_MONO,       "MONO"},
  {ImageType::PIXEL_TYPE_BAYER_GBRG, "BAYER_GBRG"},
  {ImageType::PIXEL_TYPE_BAYER_GRBG, "BAYER_GRBG"},
  {ImageType::PIXEL_TYPE_BAYER_BGGR, "BAYER_BGGR"},
  {ImageType::PIXEL_TYPE_BAYER_RGGB, "BAYER_RGGB"},
  {ImageType::PIXEL_TYPE_RGB,        "RGB"},
  {ImageType::PIXEL_TYPE_RGBA,       "RGBA"},
  {ImageType::PIXEL_TYPE_ARGB,       "ARGB"},
  {ImageType::PIXEL_TYPE_BGR,        "BGR"},
  {ImageType::PIXEL_TYPE_BGRA,       "BGRA"},
  {ImageType::PIXEL_TYPE_ABGR,       "ABGR"},
  {ImageType::PIXEL_TYPE_CMY,        "CMY"},
  {ImageType::PIXEL_TYPE_CMYK,       "CMYK"},
  {ImageType::PIXEL_TYPE_HSL,        "HSL"},
  {ImageType::PIXEL_TYPE_HSV,        "HSV"},
  {ImageType::PIXEL_TYPE_HSI,        "HSI"},
  {ImageType::PIXEL_TYPE_LUV,        "LUV"},
  {ImageType::PIXEL_TYPE_LAB,        "LAB"},
  {ImageType::PIXEL_TYPE_LCHAB,      "LCHAB"},
  {ImageType::PIXEL_TYPE_LCHUV,      "LCHUV"},
  {ImageType::PIXEL_TYPE_DIN99,      "DIN99"},
  {ImageType::PIXEL_TYPE_DIN99D,     "DIN99d"},
  {ImageType::PIXEL_TYPE_DIN99O,     "DIN99o"},
  {ImageType::PIXEL_TYPE_YUV410,     "YUV410"},
  {ImageType::PIXEL_TYPE_YUV411,     "YUV411"},
  {ImageType::PIXEL_TYPE_YUV420,     "YUV420"},
  {ImageType::PIXEL_TYPE_YUV422,     "YUV422"},
  {ImageType::PIXEL_TYPE_FOURCC,     "FORCC"},
  {ImageType::PIXEL_TYPE_MULTI_CH,   "MULTI_CH"},
  {ImageType::PIXEL_TYPE_JPEG,       "JPEG"},
  {ImageType::PIXEL_TYPE_ANY,        "ANY"},
  {ImageType::PIXEL_TYPE_NOT_SPECIFIED, ""},
};
const BufferTypeTable  kBufferTypeTable[] =
{
  {ImageType::BUFFER_TYPE_PIXEL_ALIGNED,                 "ALIGNED"},
  {ImageType::BUFFER_TYPE_PIXEL_PACKED,                  "PACKED"},
  {ImageType::BUFFER_TYPE_PIXEL_PACKED_CSI_2,            "PACKED_CSI_2"},
  {ImageType::BUFFER_TYPE_PLANAR_ALIGNED,                "PLANAR_ALIGNED"},
  {ImageType::BUFFER_TYPE_PLANAR_PACKED,                 "PLANAR_PACKED"},
  {ImageType::BUFFER_TYPE_PLANAR_PACKED_CSI_2,           "PLANAR_PACKED_CSI_2"},
  {ImageType::BUFFER_TYPE_LINE_INTERLEAVE_ALIGNED,       "LINE_INTERLEVE_ALIGNED"},
  {ImageType::BUFFER_TYPE_LINE_INTERLEAVE_PACKED,        "LINE_INTERLEVE_PACKED"},
  {ImageType::BUFFER_TYPE_LINE_INTERLEAVE_PACKED_CSI_2,  "LINE_INTERLEVE_PACKED_CSI_2"},
  {ImageType::BUFFER_TYPE_INTRA_LINE_ALIGNED,            "INTRA_LINE_ALIGNED"},
  {ImageType::BUFFER_TYPE_INTRA_LINE_PACKED,             "INTRA_LINE_PACKED"},
  {ImageType::BUFFER_TYPE_INTRA_LINE_PACKED_CSI_2,       "INTRA_LINE_PACKED_CSI_2"},
  {ImageType::BUFFER_TYPE_NOT_SPECIFIED, ""},
};
const DataTypeTable  kDataTypeTable[] =
{
  {ImageType::DATA_TYPE_1BIT,    "1BIT"},
  {ImageType::DATA_TYPE_4BIT,    "4BIT"},
  {ImageType::DATA_TYPE_8BIT,    "8BIT"},
  {ImageType::DATA_TYPE_10BIT,   "10BIT"},
  {ImageType::DATA_TYPE_12BIT,   "12BIT"},
  {ImageType::DATA_TYPE_14BIT,   "14BIT"},
  {ImageType::DATA_TYPE_16BIT,   "16BIT"},
  {ImageType::DATA_TYPE_24BIT,   "24BIT"},
  {ImageType::DATA_TYPE_32BIT,   "32BIT"},
  {ImageType::DATA_TYPE_40BIT,   "40BIT"},
  {ImageType::DATA_TYPE_48BIT,   "48BIT"},
  {ImageType::DATA_TYPE_56BIT,   "56BIT"},
  {ImageType::DATA_TYPE_64BIT,   "64BIT"},
  {ImageType::DATA_TYPE_FLOAT,   "FLOAT"},
  {ImageType::DATA_TYPE_DOUBLE,  "DOUBLE"},
  //
  {ImageType::DATA_TYPE_4BIT_SIGNED,   "4BIT_SIGNED"},
  {ImageType::DATA_TYPE_8BIT_SIGNED,   "8BIT_SIGNED"},
  {ImageType::DATA_TYPE_10BIT_SIGNED,  "10BIT_SIGNED"},
  {ImageType::DATA_TYPE_12BIT_SIGNED,  "12BIT_SIGNED"},
  {ImageType::DATA_TYPE_14BIT_SIGNED,  "14BIT_SIGNED"},
  {ImageType::DATA_TYPE_16BIT_SIGNED,  "16BIT_SIGNED"},
  {ImageType::DATA_TYPE_24BIT_SIGNED,  "24BIT_SIGNED"},
  {ImageType::DATA_TYPE_32BIT_SIGNED,  "32BIT_SIGNED"},
  {ImageType::DATA_TYPE_40BIT_SIGNED,  "40BIT_SIGNED"},
  {ImageType::DATA_TYPE_48BIT_SIGNED,  "48BIT_SIGNED"},
  {ImageType::DATA_TYPE_56BIT_SIGNED,  "56BIT_SIGNED"},
  {ImageType::DATA_TYPE_64BIT_SIGNED,  "64BIT_SIGNED"},
  //
  {ImageType::DATA_TYPE_ANY, "ANY"},
  {ImageType::DATA_TYPE_NOT_SPECIFIED, ""}
};
const EndianTypeTable  kEndianTypeTable[] =
{
  {ImageType::ENDIAN_LITTLE,     "LITTLE"},
  {ImageType::ENDIAN_BIG,        "BIG"},
  {ImageType::ENDIAN_TYPE_HOST,  "HOST"},
  {ImageType::ENDIAN_TYPE_NOT_SPECIFIED, ""}
};

// -----------------------------------------------------------------------------
// ImageType
// -----------------------------------------------------------------------------
ImageType::ImageType()
{
  invalidate();
}

// -----------------------------------------------------------------------------
// ImageType
// -----------------------------------------------------------------------------
ImageType::ImageType(PixelType inPixelType, BufferType inBufferType, DataType inDataType,
            EndianType inEndian,
            uint32_t inFourCC,
            unsigned int inComponentsPerPixel)
{
  set(inPixelType, inBufferType, inDataType, inEndian,
      inFourCC, inComponentsPerPixel);
}

// -----------------------------------------------------------------------------
// ~ImageType
// -----------------------------------------------------------------------------
ImageType::~ImageType()
{
}

// -----------------------------------------------------------------------------
// isValid
// -----------------------------------------------------------------------------
bool ImageType::isValid(bool inAllowAny) const
{
  if (mPixelType == ImageType::PIXEL_TYPE_NOT_SPECIFIED)
    return false;
  if (mPixelType == ImageType::PIXEL_TYPE_ANY && inAllowAny == false)
    return false;

  if (mBufferType == ImageType::BUFFER_TYPE_NOT_SPECIFIED)
    return false;
  if (mBufferType == ImageType::BUFFER_TYPE_ANY && inAllowAny == false)
    return false;

  if (mDataType == ImageType::DATA_TYPE_NOT_SPECIFIED)
    return false;
  if (mDataType == ImageType::DATA_TYPE_ANY && inAllowAny == false)
    return false;

  if (mComponentsPerPixel == 0)
    return false;

  return true;
}

// -----------------------------------------------------------------------------
// hasMacroPixelStructure
// -----------------------------------------------------------------------------
bool ImageType::hasMacroPixelStructure() const
{
  return hasMacroPixelStructure(mPixelType, mFourCC);
}

// -----------------------------------------------------------------------------
// isPlanar
// -----------------------------------------------------------------------------
bool ImageType::isPlanar() const
{
  return isPlanar(mBufferType);
}

// -----------------------------------------------------------------------------
// isPacked
// -----------------------------------------------------------------------------
bool ImageType::isPacked() const
{
  return isPacked(mBufferType);
}

// -----------------------------------------------------------------------------
// isSigned
// -----------------------------------------------------------------------------
bool  ImageType::isSigned() const
{
  return isSigned(mDataType);
}

// -----------------------------------------------------------------------------
// isByteAligned
// -----------------------------------------------------------------------------
bool ImageType::isByteAligned() const
{
  return isByteAlgned(mDataType);
}

// -----------------------------------------------------------------------------
// sizeOfData
// -----------------------------------------------------------------------------
size_t ImageType::sizeOfData() const
{
  return sizeOfData(mDataType);
}

// -----------------------------------------------------------------------------
// check
// -----------------------------------------------------------------------------
bool ImageType::check(PixelType inPixelType, BufferType inBufferType,
                          DataType inDataType) const
{
  return check(*this, inPixelType, inBufferType, inDataType);
}

// -----------------------------------------------------------------------------
// invalidate
// -----------------------------------------------------------------------------
void ImageType::invalidate()
{
  mPixelType              = ImageType::PIXEL_TYPE_NOT_SPECIFIED;
  mBufferType             = ImageType::BUFFER_TYPE_NOT_SPECIFIED;
  mDataType               = ImageType::DATA_TYPE_NOT_SPECIFIED;
  mEndian                 = ImageType::ENDIAN_TYPE_NOT_SPECIFIED;
  mFourCC                 = 0;
  mComponentsPerPixel     = 0;
}

// -----------------------------------------------------------------------------
// set
// -----------------------------------------------------------------------------
void ImageType::set(PixelType inPixelType, BufferType inBufferType,
            DataType inDataType,
            EndianType inEndian,
            uint32_t inFourCC,
            unsigned int inComponentsPerPixel)
{
  setPixelType(inPixelType, inComponentsPerPixel);
  setBufferType(inBufferType);
  setDataType(inDataType);
  setEndianType(inEndian);
  mFourCC = inFourCC;
}

// -----------------------------------------------------------------------------
// pixelType
// -----------------------------------------------------------------------------
ImageType::PixelType ImageType::pixelType() const
{
  return mPixelType;
}

// -----------------------------------------------------------------------------
// setPixelType
// -----------------------------------------------------------------------------
void ImageType::setPixelType(PixelType inPixelType,
                              unsigned int inComponentsPerPixel)
{
  mPixelType  = inPixelType;
  if (inComponentsPerPixel == 0)
    mComponentsPerPixel   = componentsPerPixel(inPixelType);
  else
    mComponentsPerPixel   = inComponentsPerPixel;
}

// -----------------------------------------------------------------------------
// bufferType
// -----------------------------------------------------------------------------
ImageType::BufferType ImageType::bufferType() const
{
  return mBufferType;
}

// -----------------------------------------------------------------------------
// setBufferType
// -----------------------------------------------------------------------------
void ImageType::setBufferType(BufferType inType)
{
  mBufferType = inType;
}

// -----------------------------------------------------------------------------
// dataType
// -----------------------------------------------------------------------------
ImageType::DataType ImageType::dataType() const
{
  return mDataType;
}

// -----------------------------------------------------------------------------
// setDataType
// -----------------------------------------------------------------------------
void ImageType::setDataType(DataType inType)
{
  mDataType = inType;
}

// -----------------------------------------------------------------------------
// setDataType
// -----------------------------------------------------------------------------
void ImageType::setDataType(unsigned int inBitWidth, bool inIsSigned)
{
  setDataType(dataTypeFromParams(inBitWidth, inIsSigned));
}

// -----------------------------------------------------------------------------
// endianType
// -----------------------------------------------------------------------------
ImageType::EndianType  ImageType::endianType() const
{
  return mEndian;
}

// -----------------------------------------------------------------------------
// setEndianType
// -----------------------------------------------------------------------------
void ImageType::setEndianType(EndianType inEndian)
{
  if (inEndian == ImageType::ENDIAN_TYPE_HOST)
    mEndian               = getHostEndian();
  else
    mEndian               = inEndian;
}

// -----------------------------------------------------------------------------
// fourCC
// -----------------------------------------------------------------------------
uint32_t ImageType::fourCC() const
{
  return mFourCC;
}

// -----------------------------------------------------------------------------
// setEndianType
// -----------------------------------------------------------------------------
void ImageType::setFourCC(uint32_t inFourCC)
{
  mFourCC = inFourCC;
}

// -----------------------------------------------------------------------------
// componentsPerPixel
// -----------------------------------------------------------------------------
unsigned int ImageType::componentsPerPixel() const
{
  return mComponentsPerPixel;
}

// -----------------------------------------------------------------------------
// dump
// -----------------------------------------------------------------------------
void ImageType::dump(const char *inLeadingStr)
{
  printf("%smPixelType  : 0x%X (%s)\n", inLeadingStr, mPixelType, pixelTypeToString(mPixelType));
  printf("%smBufferType : 0x%X (%s)\n", inLeadingStr, mBufferType, bufferTypeToString(mBufferType));
  printf("%smDataType   : 0x%X (%s)\n", inLeadingStr, mDataType, dataTypeToString(mDataType));
  printf("%smEndian     : 0x%X (%s)\n", inLeadingStr, mEndian, endianTypeToString(mEndian));
  printf("%smFourCC     : 0x%04X\n", inLeadingStr, mFourCC);
  printf("%smComponentsPerPixel : %d\n", inLeadingStr, mComponentsPerPixel);
}

// Static Functions ------------------------------------------------------------
// -----------------------------------------------------------------------------
// componentsPerPixel
// -----------------------------------------------------------------------------
unsigned int ImageType::componentsPerPixel(PixelType inType)
{
  switch (inType)
  {
    case ImageType::PIXEL_TYPE_RAW:
    case ImageType::PIXEL_TYPE_MONO:
    case ImageType::PIXEL_TYPE_BAYER_GBRG:
    case ImageType::PIXEL_TYPE_BAYER_GRBG:
    case ImageType::PIXEL_TYPE_BAYER_BGGR:
    case ImageType::PIXEL_TYPE_BAYER_RGGB:
      return 1;
    case ImageType::PIXEL_TYPE_RGB:
    case ImageType::PIXEL_TYPE_BGR:
    case ImageType::PIXEL_TYPE_CMY:
    case ImageType::PIXEL_TYPE_HSL:
    case ImageType::PIXEL_TYPE_HSV:
    case ImageType::PIXEL_TYPE_HSI:
    case ImageType::PIXEL_TYPE_LUV:
    case ImageType::PIXEL_TYPE_LAB:
    case ImageType::PIXEL_TYPE_YUV444:
      return 3;
    case ImageType::PIXEL_TYPE_RGBA:
    case ImageType::PIXEL_TYPE_BGRA:
    case ImageType::PIXEL_TYPE_CMYK:
      return 4;
    default:
      break;
  }
  return 0;
}

// -----------------------------------------------------------------------------
// hasMacroPixelStructure
// -----------------------------------------------------------------------------
bool ImageType::hasMacroPixelStructure(PixelType inType, uint32_t inFourCC)
{
  switch (inType)
  {
    case ImageType::PIXEL_TYPE_YUV410:
    case ImageType::PIXEL_TYPE_YUV411:
    case ImageType::PIXEL_TYPE_YUV420:
    case ImageType::PIXEL_TYPE_YUV422:
      return true;
    case ImageType::PIXEL_TYPE_FOURCC:
      // TODO : We need to check inFourCC here
      if (inFourCC == 0)
        return false;
      break;
    default:
      break;
  }
  return false;
}

// -----------------------------------------------------------------------------
// isSigned
// -----------------------------------------------------------------------------
size_t ImageType::isSigned(DataType inType)
{
  if (inType < 0x1000)
    return false;
  return true;
}

// -----------------------------------------------------------------------------
// isByteAlgned
// -----------------------------------------------------------------------------
bool ImageType::isByteAlgned(DataType inType)
{
  switch (inType)
  {
    case ImageType::DATA_TYPE_8BIT:
    case ImageType::DATA_TYPE_8BIT_SIGNED:
    case ImageType::DATA_TYPE_16BIT:
    case ImageType::DATA_TYPE_16BIT_SIGNED:
    case ImageType::DATA_TYPE_24BIT:
    case ImageType::DATA_TYPE_24BIT_SIGNED:
    case ImageType::DATA_TYPE_32BIT:
    case ImageType::DATA_TYPE_32BIT_SIGNED:
    case ImageType::DATA_TYPE_40BIT:
    case ImageType::DATA_TYPE_40BIT_SIGNED:
    case ImageType::DATA_TYPE_48BIT:
    case ImageType::DATA_TYPE_48BIT_SIGNED:
    case ImageType::DATA_TYPE_56BIT:
    case ImageType::DATA_TYPE_56BIT_SIGNED:
    case ImageType::DATA_TYPE_64BIT:
    case ImageType::DATA_TYPE_64BIT_SIGNED:
    case ImageType::DATA_TYPE_FLOAT:
    case ImageType::DATA_TYPE_DOUBLE:
      return true;
    default:
      break;
  }
  return false;
}

// -----------------------------------------------------------------------------
// sizeOfData
// -----------------------------------------------------------------------------
size_t ImageType::sizeOfData(DataType inType)
{
  switch (inType)
  {
    case ImageType::DATA_TYPE_8BIT:
    case ImageType::DATA_TYPE_8BIT_SIGNED:
      return 1;
    case ImageType::DATA_TYPE_16BIT:
    case ImageType::DATA_TYPE_16BIT_SIGNED:
      return 2;
    case ImageType::DATA_TYPE_24BIT:
    case ImageType::DATA_TYPE_24BIT_SIGNED:
      return 3;
    case ImageType::DATA_TYPE_32BIT:
    case ImageType::DATA_TYPE_32BIT_SIGNED:
      return 4;
    case ImageType::DATA_TYPE_40BIT:
    case ImageType::DATA_TYPE_40BIT_SIGNED:
      return 5;
    case ImageType::DATA_TYPE_48BIT:
    case ImageType::DATA_TYPE_48BIT_SIGNED:
      return 6;
    case ImageType::DATA_TYPE_56BIT:
    case ImageType::DATA_TYPE_56BIT_SIGNED:
      return 7;
    case ImageType::DATA_TYPE_64BIT:
    case ImageType::DATA_TYPE_64BIT_SIGNED:
      return 8;
    default:
      break;
  }
  return 0;
}

// -----------------------------------------------------------------------------
// dataTypeFromParams
// -----------------------------------------------------------------------------
ImageType::DataType ImageType::dataTypeFromParams(unsigned int inBitWidth,
                                                  bool inIsSigned)
{
  DataType  type;

  switch (inBitWidth)
  {
    case 1:
      return ImageType::DATA_TYPE_1BIT;
    case 4:
      type = ImageType::DATA_TYPE_4BIT;
      break;
    case 8:
      type = ImageType::DATA_TYPE_8BIT;
      break;
    case 10:
      type = ImageType::DATA_TYPE_10BIT;
      break;
    case 12:
      type = ImageType::DATA_TYPE_12BIT;
      break;
    case 14:
      type = ImageType::DATA_TYPE_14BIT;
      break;
    case 16:
      type = ImageType::DATA_TYPE_16BIT;
      break;
    case 24:
      type = ImageType::DATA_TYPE_24BIT;
      break;
    case 32:
      type = ImageType::DATA_TYPE_32BIT;
      break;
    case 40:
      type = ImageType::DATA_TYPE_40BIT;
      break;
    case 48:
      type = ImageType::DATA_TYPE_48BIT;
      break;
    case 56:
      type = ImageType::DATA_TYPE_56BIT;
      break;
    case 64:
      type = ImageType::DATA_TYPE_64BIT;
      break;
    default:
      return ImageType::DATA_TYPE_NOT_SPECIFIED;
  }
  if (inIsSigned)
    type = (DataType )((int )type + (int )ImageType::DATA_TYPE_SIGNED_OFFSET);
  return type;
}

// -----------------------------------------------------------------------------
// isPlanar
// -----------------------------------------------------------------------------
bool ImageType::isPlanar(BufferType inBufferType)
{
  if (inBufferType == ImageType::BUFFER_TYPE_PLANAR_ALIGNED ||
      inBufferType == ImageType::BUFFER_TYPE_PLANAR_PACKED)
    return true;
  return false;
}

// -----------------------------------------------------------------------------
// isPacked
// -----------------------------------------------------------------------------
bool ImageType::isPacked(BufferType inBufferType)
{
  if (inBufferType == ImageType::BUFFER_TYPE_PIXEL_PACKED ||
      inBufferType == ImageType::BUFFER_TYPE_PLANAR_PACKED)
    return true;
  return false;
}

// -----------------------------------------------------------------------------
// check
// -----------------------------------------------------------------------------
bool ImageType::check(const ImageType &inType, PixelType inPixelType,
                          BufferType inBufferType, DataType inDataType)
{
  if (inPixelType != ImageType::PIXEL_TYPE_ANY && inType.mPixelType != inPixelType)
    return false;
  if (inBufferType != ImageType::BUFFER_TYPE_ANY && inType.mBufferType != inBufferType)
    return false;
  if (inDataType != ImageType::DATA_TYPE_ANY && inType.mDataType != inDataType)
    return false;
  return true;
}

// -----------------------------------------------------------------------------
// getHostEndian
// -----------------------------------------------------------------------------
ImageType::EndianType ImageType::getHostEndian()
{
#ifdef __LITTLE_ENDIAN__
    return ImageType::ENDIAN_LITTLE;
#else
    return ImageType::ENDIAN_BIG;
#endif
}

// -----------------------------------------------------------------------------
// pixelTypeToString
// -----------------------------------------------------------------------------
const char *ImageType::pixelTypeToString(PixelType inType)
{
  const PixelTypeTable  *tablePtr = kPixelTypeTable;
  while (tablePtr->type != ImageType::PIXEL_TYPE_NOT_SPECIFIED)
  {
    if (tablePtr->type == inType)
      return tablePtr->str;
    tablePtr++;
  }
  return "Unknown Type";
}

// -----------------------------------------------------------------------------
// bufferTypeToString
// -----------------------------------------------------------------------------
const char *ImageType::bufferTypeToString(BufferType inType)
{
  const BufferTypeTable  *tablePtr = kBufferTypeTable;
  while (tablePtr->type != ImageType::BUFFER_TYPE_NOT_SPECIFIED)
  {
    if (tablePtr->type == inType)
      return tablePtr->str;
    tablePtr++;
  }
  return "Unknown Type";
}

// -----------------------------------------------------------------------------
// dataTypeToString
// -----------------------------------------------------------------------------
const char *ImageType::ImageType::dataTypeToString(DataType inType)
{
  const DataTypeTable  *tablePtr = kDataTypeTable;
  while (tablePtr->type != ImageType::DATA_TYPE_NOT_SPECIFIED)
  {
    if (tablePtr->type == inType)
      return tablePtr->str;
    tablePtr++;
  }
  return "Unknown Type";
}

// -----------------------------------------------------------------------------
// endianTypeToString
// -----------------------------------------------------------------------------
const char *ImageType::ImageType::endianTypeToString(EndianType inType)
{
  const EndianTypeTable  *tablePtr = kEndianTypeTable;
  while (tablePtr->type != ImageType::ENDIAN_TYPE_NOT_SPECIFIED)
  {
    if (tablePtr->type == inType)
      return tablePtr->str;
    tablePtr++;
  }
  return "Unknown Type";
}

// -----------------------------------------------------------------------------
// stringToPixelType
// -----------------------------------------------------------------------------
ImageType::PixelType ImageType::stringToPixelType(const char *inString,
                                                  PixelType inDefault)
{
  const PixelTypeTable  *tablePtr = kPixelTypeTable;
  while (tablePtr->type != ImageType::PIXEL_TYPE_NOT_SPECIFIED)
  {
#ifndef WIN32
    if (::strncasecmp(inString, tablePtr->str, ::strlen(tablePtr->str)) == 0)
#else
    if (::stricmp(inString, tablePtr->str) == 0)
#endif
      return tablePtr->type;
    tablePtr++;
  }
  return inDefault;
}

// -----------------------------------------------------------------------------
// stringToBufferType
// -----------------------------------------------------------------------------
ImageType::BufferType ImageType::stringToBufferType(const char *inString,
                                                     BufferType inDefault)
{
  const BufferTypeTable  *tablePtr = kBufferTypeTable;
  while (tablePtr->type != ImageType::BUFFER_TYPE_NOT_SPECIFIED)
  {
#ifndef WIN32
    if (::strncasecmp(inString, tablePtr->str, ::strlen(tablePtr->str)) == 0)
#else
    if (::stricmp(inString, tablePtr->str) == 0)
#endif
      return tablePtr->type;
    tablePtr++;
  }
  return inDefault;
}

// -----------------------------------------------------------------------------
// stringToDataType
// -----------------------------------------------------------------------------
ImageType::DataType ImageType::stringToDataType(const char *inString, DataType inDefault)
{
  const DataTypeTable  *tablePtr = kDataTypeTable;
  while (tablePtr->type != ImageType::DATA_TYPE_NOT_SPECIFIED)
  {
#ifndef WIN32
    if (::strncasecmp(inString, tablePtr->str, ::strlen(tablePtr->str)) == 0)
#else
    if (::stricmp(inString, tablePtr->str) == 0)
#endif
      return tablePtr->type;
    tablePtr++;
  }
  return inDefault;
}

// -----------------------------------------------------------------------------
// stringToEndianType
// -----------------------------------------------------------------------------
ImageType::EndianType ImageType::stringToEndianType(const char *inString,
                                                    EndianType inDefault)
{
  const EndianTypeTable  *tablePtr = kEndianTypeTable;
  while (tablePtr->type != ImageType::ENDIAN_TYPE_NOT_SPECIFIED)
  {
#ifndef WIN32
    if (::strncasecmp(inString, tablePtr->str, ::strlen(tablePtr->str)) == 0)
#else
    if (::stricmp(inString, tablePtr->str) == 0)
#endif
      return tablePtr->type;
    tablePtr++;
  }
  return inDefault;
}
