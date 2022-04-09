// =============================================================================
//  ImageType.h
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
  \file     ImageType.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/26
*/

#ifndef QIV_IMAGE_TYPE_H
#define QIV_IMAGE_TYPE_H

// Includes --------------------------------------------------------------------
#include <cstdint>
#include <cstddef>

// -----------------------------------------------------------------------------
// ImageType class
// -----------------------------------------------------------------------------
class  ImageType
{
public:
  // Enum ----------------------------------------------------------------------
  enum  PixelType
  {
    PIXEL_TYPE_NOT_SPECIFIED  = 0,
    PIXEL_TYPE_RAW            = 0x10,
    PIXEL_TYPE_MONO,
    PIXEL_TYPE_BAYER_GBRG,
    PIXEL_TYPE_BAYER_GRBG,
    PIXEL_TYPE_BAYER_BGGR,
    PIXEL_TYPE_BAYER_RGGB,
    // TODO: Add followings
    //PIXEL_TYPE_BAYER_YCGM,
    //PIXEL_TYPE_BAYER_CYMG,
    //PIXEL_TYPE_BAYER_GMYC,
    //PIXEL_TYPE_BAYER_MGCY,
    // RGBW, RGBE, EXR, CYGW, XTRANS...
    //
    PIXEL_TYPE_RGB            = 0x2000,
    PIXEL_TYPE_BGR,
    PIXEL_TYPE_RGBA,
    PIXEL_TYPE_ARGB,
    PIXEL_TYPE_BGRA,
    PIXEL_TYPE_ABGR,
    PIXEL_TYPE_CMY            = 0x3000,
    PIXEL_TYPE_CMYK,
    PIXEL_TYPE_HSL            = 0x4000,
    PIXEL_TYPE_HSV,                       // HSB
    PIXEL_TYPE_HSI,
    PIXEL_TYPE_LUV,
    PIXEL_TYPE_LAB,
    PIXEL_TYPE_LCHAB,
    PIXEL_TYPE_LCHUV,
    PIXEL_TYPE_DIN99,
    PIXEL_TYPE_DIN99D,
    PIXEL_TYPE_DIN99O,
    PIXEL_TYPE_YUV410         = 0x5000,   // YUV9
    PIXEL_TYPE_YUV411,
    PIXEL_TYPE_YUV420,                    // YUV12
    PIXEL_TYPE_YUV422,
    PIXEL_TYPE_YUV444,
    PIXEL_TYPE_MULTI_CH       = 0x6000,
    PIXEL_TYPE_MULTI_CH_MONO,
    PIXEL_TYPE_MULTI_CH_RGB,
    PIXEL_TYPE_MULTI_CH_RGBA,
    PIXEL_TYPE_FOURCC         = 0x7000,
    PIXEL_TYPE_COMPRESSED     = 0x8000,
    PIXEL_TYPE_JPEG,
    PIXEL_TYPE_ANY            = 0xFFFF
  };

   enum  BufferType
  {
    BUFFER_TYPE_NOT_SPECIFIED                 = 0,
    BUFFER_TYPE_PIXEL_ALIGNED,
    BUFFER_TYPE_PIXEL_PACKED,
    BUFFER_TYPE_PIXEL_PACKED_CSI_2,
    BUFFER_TYPE_PLANAR_ALIGNED                = 0x1000,
    BUFFER_TYPE_PLANAR_PACKED,
    BUFFER_TYPE_PLANAR_PACKED_CSI_2,
    BUFFER_TYPE_LINE_INTERLEAVE_ALIGNED       = 0x2000,
    BUFFER_TYPE_LINE_INTERLEAVE_PACKED,
    BUFFER_TYPE_LINE_INTERLEAVE_PACKED_CSI_2,
    BUFFER_TYPE_INTRA_LINE_ALIGNED            = 0x3000,
    BUFFER_TYPE_INTRA_LINE_PACKED,
    BUFFER_TYPE_INTRA_LINE_PACKED_CSI_2,
    //
    BUFFER_TYPE_COMPRESSION                   = 0x8000,
    BUFFER_TYPE_ANY                           = 0xFFFF
  };

  enum  DataType
  {
    DATA_TYPE_NOT_SPECIFIED = 0,
    DATA_TYPE_1BIT          = 1,
    DATA_TYPE_4BIT          = 4,
    DATA_TYPE_8BIT          = 8,
    DATA_TYPE_10BIT         = 10,
    DATA_TYPE_12BIT         = 12,
    DATA_TYPE_14BIT         = 14,
    DATA_TYPE_16BIT         = 16,
    DATA_TYPE_24BIT         = 24,
    DATA_TYPE_32BIT         = 32,
    DATA_TYPE_40BIT         = 40,
    DATA_TYPE_48BIT         = 48,
    DATA_TYPE_56BIT         = 56,
    DATA_TYPE_64BIT         = 64,     // 0x40
    DATA_TYPE_FLOAT         = 0x200,  // 512
    DATA_TYPE_DOUBLE        = 0x400,  // 1024
    //
    DATA_TYPE_SIGNED_OFFSET = 0x1000,   // 4096
    DATA_TYPE_4BIT_SIGNED   = 4100,
    DATA_TYPE_8BIT_SIGNED   = 4104,
    DATA_TYPE_10BIT_SIGNED  = 4106,
    DATA_TYPE_12BIT_SIGNED  = 4108,
    DATA_TYPE_14BIT_SIGNED  = 4110,
    DATA_TYPE_16BIT_SIGNED  = 4112,
    DATA_TYPE_24BIT_SIGNED  = 4120,
    DATA_TYPE_32BIT_SIGNED  = 4128,
    DATA_TYPE_40BIT_SIGNED  = 4136,
    DATA_TYPE_48BIT_SIGNED  = 4144,
    DATA_TYPE_56BIT_SIGNED  = 4152,
    DATA_TYPE_64BIT_SIGNED  = 4160,   // 0x1040
    //
    DATA_TYPE_ANY           = 0xFFFF
  };

  enum  EndianType
  {
    ENDIAN_TYPE_NOT_SPECIFIED = 0,
    ENDIAN_LITTLE,
    ENDIAN_BIG,
    ENDIAN_TYPE_HOST,
    ENDIAN_TYPE_ANY           = 0xFFFF
  };

  enum  ChannelType       // We are not using this for now...
  {
    CH_TYPE_NOT_SPECIFIED   = 0,
    CH_TYPE_RAW             = 0x1000,
    CH_TYPE_DATA,
    CH_TYPE_LUMINANCE       = 0x2000,
    CH_TYPE_RED             = 0x4000,
    CH_TYPE_GREEN,
    CH_TYPE_BLUE,
    CH_TYPE_ALPHA,
    CH_TYPE_WHITE,
    CH_TYPE_IR,
    CH_TYPE_CYAN            = 0x5000,
    CH_TYPE_MAGENTA,
    CH_TYPE_YELLOW,
    CH_TYPE_KEY_PLATE,
    CH_TYPE_HUE             = 0x6000,
    CH_TYPE_SATURATION,
    CH_TYPE_VALUE,
    CH_TYPE_L_STAR,
    CH_TYPE_U_STAR,
    CH_TYPE_V_STAR,
    CH_TYPE_A_STAR,
    CH_TYPE_B_STAR,
    CH_TYPE_Y               = 0x7000,
    CH_TYPE_U,
    CH_TYPE_V,
    //
    CH_TYPE_MULTI_0         = 0x8000,
    CH_TYPE_MULTI_1,
    CH_TYPE_MULTI_2,
    CH_TYPE_MULTI_3,
    CH_TYPE_MULTI_4,
    CH_TYPE_MULTI_5,
    CH_TYPE_MULTI_6,
    CH_TYPE_MULTI_7,
    CH_TYPE_MULTI_8,
    //
    CH_TYPE_ANY             = 0xFFFF
  };

  // Constructors and Destructor -----------------------------------------------
  ImageType();
  ImageType(PixelType inPixelType, BufferType inBufferType, DataType inDataType,
              EndianType inEndian = ENDIAN_TYPE_HOST,
              uint32_t inFourCC = 0,
              unsigned int inComponentsPerPixel = 0);
  virtual ~ImageType();

  // Member functions ----------------------------------------------------------
  bool isValid(bool inAllowAny = false) const;
  bool hasMacroPixelStructure() const;
  bool isPlanar() const;
  bool isPacked() const;
  bool isSigned() const;
  bool isByteAligned() const;
  size_t sizeOfData() const;
  bool check(PixelType inPixelType, BufferType inBufferType, DataType inDataType) const;
  void invalidate();
  PixelType pixelType() const;
  BufferType bufferType() const;
  DataType dataType() const;
  EndianType endianType() const;
  uint32_t fourCC() const;
  unsigned int componentsPerPixel() const;

  void set(PixelType inPixelType, BufferType inBufferType, DataType inDataType,
              EndianType inEndian = ENDIAN_TYPE_HOST,
              uint32_t inFourCC = 0,
              unsigned int inComponentsPerPixel = 0);
  void setPixelType(PixelType inPixelType, unsigned int inComponentsPerPixel = 0);
  void setBufferType(BufferType inType);
  void setDataType(DataType inType);
  void setDataType(unsigned int inBitWidth, bool inIsSigned = false);
  void setEndianType(EndianType inEndian = ENDIAN_TYPE_HOST);
  void setFourCC(uint32_t inFourCC);

  void dump(const char *inLeadingStr = "");

  // Static Functions ----------------------------------------------------------
  static unsigned int componentsPerPixel(PixelType inType);
  static bool hasMacroPixelStructure(PixelType inType, uint32_t inFourCC = 0);
  static size_t isSigned(DataType inType);
  static bool isByteAlgned(DataType inType);
  static size_t sizeOfData(DataType inType);
  static DataType dataTypeFromParams(unsigned int inBitWidth, bool inIsSigned = false);
  static bool isPlanar(BufferType inBufferType);
  static bool isPacked(BufferType inBufferType);
  static bool check(const ImageType &inType, PixelType inPixelType, BufferType inBufferType, DataType inDataType);
  static EndianType getHostEndian();
  static const char *pixelTypeToString(PixelType inType);
  static const char *bufferTypeToString(BufferType inType);
  static const char *dataTypeToString(DataType inType);
  static const char *endianTypeToString(EndianType inType);
  static PixelType stringToPixelType(const char *inString, PixelType inDefault = PIXEL_TYPE_NOT_SPECIFIED);
  static BufferType stringToBufferType(const char *inString, BufferType inDefault = BUFFER_TYPE_NOT_SPECIFIED);
  static DataType stringToDataType(const char *inString, DataType inDefault = DATA_TYPE_NOT_SPECIFIED);
  static EndianType stringToEndianType(const char *inString, EndianType inDefault = ENDIAN_TYPE_NOT_SPECIFIED);

private:
  // Member variables ----------------------------------------------------------
  PixelType       mPixelType;
  BufferType      mBufferType;
  DataType        mDataType;
  EndianType      mEndian;
  uint32_t        mFourCC;
  unsigned int    mComponentsPerPixel;
};

#endif //QIV_IMAGE_TYPE_H
