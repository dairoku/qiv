// =============================================================================
//  ColorMap.cpp
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
  \file     ColorMap.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2/27/22
*/

// Includes --------------------------------------------------------------------
#include <cmath>
#include <string.h>
#include <strings.h>
#include "ColorMap.h"

// Local Macros ----------------------------------------------------------------
enum ColorMapType
{
  CMType_Linear       = 1,
  CMType_Diverging
};

// Local Typedefs --------------------------------------------------------------
typedef struct
{
  unsigned char  R;
  unsigned char  G;
  unsigned char  B;
} ColorMapRGB;
typedef struct
{
  ColorMap::ColorMapIndex  index;
  double      ratio;
  ColorMapType  type;
  ColorMapRGB    rgb;
} ColorMapData;
typedef struct
{
  ColorMap::ColorMapIndex index;
  const char  *str;
} ColorMapIndexTable;

// Local static functions ------------------------------------------------------
static void clearColorMap(unsigned int inColorNum,  unsigned char *outColorMap);
static const double *getD50WhitePointInXyz();
static const double *getD65WhitePointInXyz();
static double labSubFunc(double inT);
static double labSubInvFunc(double inT);
static void getMultiColorMapData(ColorMap::ColorMapIndex inIndex,
          unsigned int inMultiNum, std::vector<ColorMapData> &outData);
static const ColorMapData *getColorMapData(ColorMap::ColorMapIndex inIndex);

// Local static constants ------------------------------------------------------
static const ColorMapData    kColorMapData[] =
{
  // GrayScale
  { ColorMap::CMI_GrayScale, 0.0, CMType_Linear, {0, 0, 0}},
  { ColorMap::CMI_GrayScale, 1.0, CMType_Linear, {255, 255, 255}},
  // Jet
  { ColorMap::CMI_Jet, 0.0, CMType_Linear,{ 0, 0, 127 } },
  { ColorMap::CMI_Jet, 0.1, CMType_Linear,{ 0, 0, 255 } },
  { ColorMap::CMI_Jet, 0.35, CMType_Linear,{ 0, 255, 255 } },
  { ColorMap::CMI_Jet, 0.5, CMType_Linear,{ 0, 255, 0 } },
  { ColorMap::CMI_Jet, 0.65, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_Jet, 0.9, CMType_Linear,{ 255, 0, 0 } },
  { ColorMap::CMI_Jet, 1.0, CMType_Linear,{ 127, 0, 0 } },
  // Rainbow
  { ColorMap::CMI_Rainbow, 0.0, CMType_Linear,{ 0, 0, 255 } },
  { ColorMap::CMI_Rainbow, 0.25, CMType_Linear,{ 0, 255, 255 } },
  { ColorMap::CMI_Rainbow, 0.5, CMType_Linear,{ 0, 255, 0 } },
  { ColorMap::CMI_Rainbow, 0.75, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_Rainbow, 1.0, CMType_Linear,{ 255, 0, 0 } },
  // Rainbow Wide
  { ColorMap::CMI_RainbowWide, 0.0, CMType_Linear,{ 0, 0, 0 } },
  { ColorMap::CMI_RainbowWide, 0.1, CMType_Linear,{ 0, 0, 255 } },
  { ColorMap::CMI_RainbowWide, 0.3, CMType_Linear,{ 0, 255, 255 } },
  { ColorMap::CMI_RainbowWide, 0.5, CMType_Linear,{ 0, 255, 0 } },
  { ColorMap::CMI_RainbowWide, 0.7, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_RainbowWide, 0.9, CMType_Linear,{ 255, 0, 0 } },
  { ColorMap::CMI_RainbowWide, 1.0, CMType_Linear,{ 255, 255, 255 } },
  // Spectrum
  { ColorMap::CMI_Spectrum, 0.0, CMType_Linear,{ 255, 0, 255 } },
  { ColorMap::CMI_Spectrum, 0.1, CMType_Linear,{ 0, 0, 255 } },
  { ColorMap::CMI_Spectrum, 0.3, CMType_Linear,{ 0, 255, 255 } },
  { ColorMap::CMI_Spectrum, 0.45, CMType_Linear,{ 0, 255, 0 } },
  { ColorMap::CMI_Spectrum, 0.6, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_Spectrum, 1.0, CMType_Linear,{ 255, 0, 0 } },
  // Spectrum Wide
  { ColorMap::CMI_SpectrumWide, 0.0, CMType_Linear,{ 0, 0, 0 } },
  { ColorMap::CMI_SpectrumWide, 0.1, CMType_Linear,{ 150, 0, 150 } },
  { ColorMap::CMI_SpectrumWide, 0.2, CMType_Linear,{ 0, 0, 255 } },
  { ColorMap::CMI_SpectrumWide, 0.35, CMType_Linear,{ 0, 255, 255 } },
  { ColorMap::CMI_SpectrumWide, 0.5, CMType_Linear,{ 0, 255, 0 } },
  { ColorMap::CMI_SpectrumWide, 0.6, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_SpectrumWide, 0.9, CMType_Linear,{ 255, 0, 0 } },
  { ColorMap::CMI_SpectrumWide, 1.0, CMType_Linear,{ 255, 255, 255 } },
  // Thermal
  { ColorMap::CMI_Thermal, 0.0, CMType_Linear,{  0, 0, 255 } },
  { ColorMap::CMI_Thermal, 0.5, CMType_Linear,{ 255, 0, 255 } },
  { ColorMap::CMI_Thermal, 1.0, CMType_Linear,{ 255, 255, 0 } },
  // Thermal Wide
  { ColorMap::CMI_ThermalWide, 0.0, CMType_Linear,{  0, 0, 0 } },
  { ColorMap::CMI_ThermalWide, 0.05, CMType_Linear,{  0, 0, 255 } },
  { ColorMap::CMI_ThermalWide, 0.5, CMType_Linear,{ 255, 0, 255 } },
  { ColorMap::CMI_ThermalWide, 0.95, CMType_Linear,{ 255, 255, 0 } },
  { ColorMap::CMI_ThermalWide, 1.0, CMType_Linear,{ 255, 255, 255 } },

  // Cool Warm
  { ColorMap::CMI_CoolWarm, 0.0, CMType_Diverging,{ 59, 76, 192 } },
  { ColorMap::CMI_CoolWarm, 1.0, CMType_Diverging,{ 180, 4, 38 } },
  // PurpleOrange
  { ColorMap::CMI_PurpleOrange, 0.0, CMType_Diverging,{ 111, 78, 161 } },
  { ColorMap::CMI_PurpleOrange, 1.0, CMType_Diverging,{ 193, 85, 11 } },
  // GreenPurple
  { ColorMap::CMI_GreenPurple, 0.0, CMType_Diverging,{ 21, 135, 51 } },
  { ColorMap::CMI_GreenPurple, 1.0, CMType_Diverging,{ 111, 78, 161 } },
  // Blue DarkYellow
  { ColorMap::CMI_BlueDarkYellow, 0.0, CMType_Diverging,{ 55, 133, 232 } },
  { ColorMap::CMI_BlueDarkYellow, 1.0, CMType_Diverging,{ 172, 125, 23 } },
  // Green Red
  { ColorMap::CMI_GreenRed, 0.0, CMType_Diverging,{ 21, 135, 51 } },
  { ColorMap::CMI_GreenRed, 1.0, CMType_Diverging,{ 193, 54, 59 } },

  // End mark (Don't remove this)
  {ColorMap::CMI_End, 0.0, CMType_Linear,{ 0, 0, 0 }}
};

const static ColorMapIndexTable  kColorMapIndexTable[] =
{
  { ColorMap::CMI_GrayScale, "GrayScale" },
  { ColorMap::CMI_Jet, "Jet" },
  { ColorMap::CMI_Rainbow, "Rainbow" },
  { ColorMap::CMI_RainbowWide, "RainbowWide" },
  { ColorMap::CMI_Spectrum, "Spectrum" },
  { ColorMap::CMI_SpectrumWide, "SpectrumWide" },
  { ColorMap::CMI_Thermal, "Thermal" },
  { ColorMap::CMI_ThermalWide, "ThermalWide" },
  { ColorMap::CMI_CoolWarm, "CoolWarm" },
  { ColorMap::CMI_PurpleOrange, "PurpleOrange" },
  { ColorMap::CMI_GreenPurple, "GreenPurple" },
  { ColorMap::CMI_BlueDarkYellow, "BlueDarkYellow" },
  { ColorMap::CMI_GreenRed, "GreenRed" },
  { ColorMap::CMI_ANY, "ANY" },
  { ColorMap::CMI_NOT_SPECIFIED, "" }
};

// -----------------------------------------------------------------------------
// getColorMap
// -----------------------------------------------------------------------------
void ColorMap::getColorMap(ColorMapIndex inIndex, unsigned int inColorNum,
                          unsigned char *outColorMap,
                          unsigned int inMultiNum,
                          double inGain, int inOffset)
{
  unsigned int  i, index, num, total, offset, numAll;
  std::vector<ColorMapData> colorMapData;
  double  ratio0, ratio1, offsetRatio;
  const unsigned char    *rgb0 = nullptr, *rgb1 = nullptr;

  getMultiColorMapData(inIndex, inMultiNum, colorMapData);
  if (colorMapData.size() < 2 || inGain <= 0.0 || inColorNum == 0)
  {
    clearColorMap(inColorNum, outColorMap);
    return;
  }

  total = 0;
  index = 0;
  num = 0;
  offsetRatio = (double )inOffset / (double )inColorNum;
  ratio0 = colorMapData[index].ratio / inGain - offsetRatio;
  if (ratio0 > 0)
  {
    num = (int )((double )inColorNum * ratio0);
    for (i = 0; i < num; i++)
    {
      outColorMap[0] = colorMapData[index].rgb.R;
      outColorMap[1] = colorMapData[index].rgb.G;
      outColorMap[2] = colorMapData[index].rgb.B;
      outColorMap += 3;
      total++;
    }
  }

  while (index + 1 < colorMapData.size())
  {
    ratio1 = colorMapData[index+1].ratio / inGain - offsetRatio;
    rgb0 = (const unsigned char *)&(colorMapData[index].rgb);
    rgb1 = (const unsigned char *)&(colorMapData[index+1].rgb);
    if (ratio1 > 0)
    {
      if (ratio1 == 1.0)  // <- this is to absorb calculation error
        numAll = inColorNum - total;
      else
        numAll = (int )(ratio1 * inColorNum)- (int )(ratio0 * inColorNum);  // Do not use (ratio1 - ratio0) * inColorNum
      if (ratio0 < 0.0)
      {
        if (ratio1 < 1.0)
          num = (unsigned int)((double )inColorNum * ratio1);
        else
          num = inColorNum;
        offset = (unsigned int )((0.0 - ratio0) * (double )inColorNum);
      }
      else
      {
        num = numAll;
        offset = 0;
      }
      if (num > inColorNum - total)
        num = inColorNum - total;
      switch (colorMapData[index].type)
      {
        case CMType_Linear:
          calcLinearColorMap(rgb0, rgb1, offset, numAll, num, outColorMap);
          break;
        case CMType_Diverging:
          calcDivergingColorMap(rgb0, rgb1, offset, numAll, num, outColorMap);
          break;
      }
    }
    ratio0 = ratio1;
    outColorMap += num * 3;
    total += num;
    index++;
    if (total == inColorNum)
      break;
  }

  if (total < inColorNum)
  {
    num = inColorNum - total;
    for (i = 0; i < num; i++)
    {
      outColorMap[0] = rgb1[0];
      outColorMap[1] = rgb1[1];
      outColorMap[2] = rgb1[2];
      outColorMap += 3;
    }
  }
}

// -----------------------------------------------------------------------------
// getMonoMap
// -----------------------------------------------------------------------------
void ColorMap::getMonoMap(int inColorNum,  unsigned char *outColorMap, double inGamma,
                        double inGain, int inOffset)
{
  if (inGamma <= 0.0 || inColorNum == 0 || inGain <= 0.0)
  {
    clearColorMap(inColorNum, outColorMap);
    return;
  }

  double pitch = 1.0 / (double )(inColorNum - 1.0);
  inGamma = 1.0 / inGamma;
  for (int i = 0; i < inColorNum; i++)
  {
    double v = pitch * (i + inOffset) * inGain;
    if (v < 0.0)
      v = 0.0;
    if (v > 1.0)
      v = 1.0;
    v = pow(v, inGamma);
    v = v * 255.0;
    if (v >= 255)
      v = 255;
    outColorMap[0] = (unsigned char)v;
    outColorMap[1] = (unsigned char)v;
    outColorMap[2] = (unsigned char)v;
    outColorMap += 3;
  }
}

// -----------------------------------------------------------------------------
// calcLinearColorMap
// -----------------------------------------------------------------------------
void ColorMap::calcLinearColorMap(const unsigned char *inRgb0, const unsigned char *inRgb1,
                                  unsigned int inOffset, unsigned int inColorNumAll,
                                  unsigned int inMapNum, unsigned char *outColorMap)
{
  double  interp, k, v;
  
  k = 1.0 / (double )(inColorNumAll - 1.0);
  for (unsigned int i = 0; i < inMapNum; i++)
  {
    unsigned int t = i + inOffset;
    if (t >= inColorNumAll)   // Sanity check
      t = inColorNumAll - 1;
    interp = (double )t * k;
    for (int j = 0; j < 3; j++)
    {
      v = (1.0 - interp) * inRgb0[j] + interp * inRgb1[j];
      if (v > 255)
        v = 255;
      outColorMap[i * 3 + j] = (unsigned char)v;
    }
  }
}

// -----------------------------------------------------------------------------
// calcDivergingColorMap
// -----------------------------------------------------------------------------
void ColorMap::calcDivergingColorMap(const unsigned char *inRgb0, const unsigned char *inRgb1,
                                     unsigned int inOffset, unsigned int inColorNumAll,
                                     unsigned int inMapNum, unsigned char *outColorMap)
{
  double  interp, k;
  
  k = 1.0 / (double )(inColorNumAll - 1.0);
  for (unsigned int i = 0; i < inMapNum; i++)
  {
    unsigned int t = i + inOffset;
    if (t >= inColorNumAll)   // Sanity check
      t = inColorNumAll - 1;
    interp = (double )t * k;
    interpolateColor(inRgb0, inRgb1, interp, &(outColorMap[i * 3]));
  }
}

// -----------------------------------------------------------------------------
// interpolateColor
// -----------------------------------------------------------------------------
void ColorMap::interpolateColor(const unsigned char *inRgb0, const unsigned char *inRgb1,
                 double inInterp, unsigned char *outRgb)
{
  double  msh0[3], msh1[3], msh[3], m;
  
  convRgbToMsh(inRgb0, msh0);
  convRgbToMsh(inRgb1, msh1);
  
  if ((msh0[1] > 0.05 && msh1[1] > 0.05) && fabs(msh0[2] - msh1[2]) > 1.0472)
  {
    if (msh0[0] > msh1[0])
      m = msh0[0];
    else
      m = msh1[0];
    if (m < 88)
      m = 88;
    if (inInterp < 0.5)
    {
      msh1[0] = m;
      msh1[1] = 0;
      msh1[2] = 0;
      inInterp = 2 * inInterp;
    }
    else
    {
      msh0[0] = m;
      msh0[1] = 0;
      msh0[2] = 0;
      inInterp = 2 * inInterp - 1;
    }
  }
  
  if (msh0[1] < 0.05 && msh1[1] > 0.05)
    msh0[2] =  adjustHue(msh1, msh0[0]);
  else if (msh0[1] > 0.05 && msh1[1] < 0.05)
    msh1[2] =  adjustHue(msh0, msh1[0]);
  
  for (int i = 0; i < 3; i++)
    msh[i] = (1 - inInterp) * msh0[i] + inInterp * msh1[i];
  
  convMshToRgb(msh, outRgb);
}

// -----------------------------------------------------------------------------
// adjustHue
// -----------------------------------------------------------------------------
double ColorMap::adjustHue(const double *inMsh, double inMunsat)
{
  if (inMsh[0] >= inMunsat)
    return inMsh[2];
  
  double  hSpin = inMsh[1] * sqrt(inMunsat * inMunsat - inMsh[0] * inMsh[0]) /
              (inMsh[0] * sin(inMsh[1]));

  if (inMsh[2] > -1.0472)
    return inMsh[2] + hSpin;
  return inMsh[2] - hSpin;
}

// -----------------------------------------------------------------------------
// convRgbToMsh
// -----------------------------------------------------------------------------
void ColorMap::convRgbToMsh(const unsigned char *inRgb, double *outMsh)
{
  double  rgbL[3];
  double  xyz[3];
  double  lab[3];
  
  convRgbToLinRGB(inRgb, rgbL);
#ifdef BLEU_COLORMAP_USE_D50
  convLinRgbToXyzD50(rgbL, xyz);
  convXyzD50ToLab(xyz, lab);
#else
  convLinRgbToXyz(rgbL, xyz);
  convXyzD65ToLab(xyz, lab);
#endif
  convLabToMsh(lab, outMsh);
}

// -----------------------------------------------------------------------------
// convMshToRgb
// -----------------------------------------------------------------------------
void ColorMap::convMshToRgb(const double *inMsh, unsigned char *outRgb)
{
  double  lab[3];
  double  xyz[3];
  double  rgbL[3];
  
  convMshToLab(inMsh, lab);
#ifdef BLEU_COLORMAP_USE_D50
  convLabToXyzD50(lab, xyz);
  convXyzD50ToLinRgb(xyz, rgbL);
#else
  convLabToXyzD65(lab, xyz);
  convXyzToLinRgb(xyz, rgbL);
#endif
  convLinRgbToRGB(rgbL, outRgb);
}

// -----------------------------------------------------------------------------
// convLabToMsh
// -----------------------------------------------------------------------------
void ColorMap::convLabToMsh(const double *inLab, double *outMsh)
{
  outMsh[0] = sqrt(inLab[0] * inLab[0] + inLab[1] * inLab[1] + inLab[2] * inLab[2]);
  outMsh[1] = acos(inLab[0] / outMsh[0]);
  outMsh[2] = atan2(inLab[2], inLab[1]);
}

// -----------------------------------------------------------------------------
// convMshToLab
// -----------------------------------------------------------------------------
void ColorMap::convMshToLab(const double *inMsh, double *outLab)
{
  outLab[0] = inMsh[0] * cos(inMsh[1]);
  outLab[1] = inMsh[0] * sin(inMsh[1]) * cos(inMsh[2]);
  outLab[2] = inMsh[0] * sin(inMsh[1]) * sin(inMsh[2]);
}

// -----------------------------------------------------------------------------
// convXyzD50ToLab
// -----------------------------------------------------------------------------
void ColorMap::convXyzD50ToLab(const double *inXyz, double *outLab)
{
  const double  *wpXyz = getD50WhitePointInXyz();
  
  outLab[0] = 116 *  labSubFunc(inXyz[1] / wpXyz[1]) - 16.0;
  outLab[1] = 500 * (labSubFunc(inXyz[0] / wpXyz[0]) - labSubFunc(inXyz[1] / wpXyz[1]));
  outLab[2] = 200 * (labSubFunc(inXyz[1] / wpXyz[1]) - labSubFunc(inXyz[2] / wpXyz[2]));
}

// -----------------------------------------------------------------------------
// convLabToXyzD50
// ------------------------------------------------------------------------
void ColorMap::convLabToXyzD50(const double *inLab, double *outXyz)
{
  const double  *wpXyz = getD50WhitePointInXyz();
  
  outXyz[0] = labSubInvFunc((inLab[0] + 16) / 116.0 + (inLab[1] / 500.0)) * wpXyz[0];
  outXyz[1] = labSubInvFunc((inLab[0] + 16) / 116.0) * wpXyz[1];
  outXyz[2] = labSubInvFunc((inLab[0] + 16) / 116.0 - (inLab[2] / 200.0)) * wpXyz[2];
}

// -----------------------------------------------------------------------------
// convXyzD65ToLab
// -----------------------------------------------------------------------------
void ColorMap::convXyzD65ToLab(const double *inXyz, double *outLab)
{
  const double  *wpXyz = getD65WhitePointInXyz();
  
  outLab[0] = 116 *  labSubFunc(inXyz[1] / wpXyz[1]) - 16.0;
  outLab[1] = 500 * (labSubFunc(inXyz[0] / wpXyz[0]) - labSubFunc(inXyz[1] / wpXyz[1]));
  outLab[2] = 200 * (labSubFunc(inXyz[1] / wpXyz[1]) - labSubFunc(inXyz[2] / wpXyz[2]));
}

// -----------------------------------------------------------------------------
// convLabToXyzD65
// -----------------------------------------------------------------------------
void ColorMap::convLabToXyzD65(const double *inLab, double *outXyz)
{
  const double  *wpXyz = getD65WhitePointInXyz();
  
  outXyz[0] = labSubInvFunc((inLab[0] + 16) / 116.0 + (inLab[1] / 500.0)) * wpXyz[0];
  outXyz[1] = labSubInvFunc((inLab[0] + 16) / 116.0) * wpXyz[1];
  outXyz[2] = labSubInvFunc((inLab[0] + 16) / 116.0 - (inLab[2] / 200.0)) * wpXyz[2];
}

// -----------------------------------------------------------------------------
// convLinRgbToXyz (from sRGB linear (D65) to XYZ (D65) color space)
// -----------------------------------------------------------------------------
void ColorMap::convLinRgbToXyz(const double *inRgbL, double *outXyz)
{
  outXyz[0] = 0.412391 * inRgbL[0] + 0.357584 * inRgbL[1] +  0.180481 * inRgbL[2];
  outXyz[1] = 0.212639 * inRgbL[0] + 0.715169 * inRgbL[1] +  0.072192 * inRgbL[2];
  outXyz[2] = 0.019331 * inRgbL[0] + 0.119195 * inRgbL[1] +  0.950532 * inRgbL[2];
}

// -----------------------------------------------------------------------------
// convXyzToLinRgb (from XYZ (D65) to sRGB linear (D65) color space)
// -----------------------------------------------------------------------------
void ColorMap::convXyzToLinRgb(const double *inXyz, double *outRgbL)
{
  outRgbL[0] =  3.240970 * inXyz[0] - 1.537383 * inXyz[1] - 0.498611 * inXyz[2];
  outRgbL[1] = -0.969244 * inXyz[0] + 1.875968 * inXyz[1] + 0.041555 * inXyz[2];
  outRgbL[2] =  0.055630 * inXyz[0] - 0.203977 * inXyz[1] + 1.056972 * inXyz[2];
}

// -----------------------------------------------------------------------------
// convLinRgbToXyzD50 (from sRGB linear (D65) to XYZ (D50) color space)
// -----------------------------------------------------------------------------
void ColorMap::convLinRgbToXyzD50(const double *inRgbL, double *outXyz)
{
  outXyz[0] = 0.436041 * inRgbL[0] +  0.385113 * inRgbL[1] +  0.143046 * inRgbL[2];
  outXyz[1] = 0.222485 * inRgbL[0] +  0.716905 * inRgbL[1] +  0.060610 * inRgbL[2];
  outXyz[2] = 0.013920 * inRgbL[0] +  0.097067 * inRgbL[1] +  0.713913 * inRgbL[2];
}

// -----------------------------------------------------------------------------
// convXyzD50ToLinRgb (from XYZ (D50) to sRGB linear (D65) color space)
// -----------------------------------------------------------------------------
void ColorMap::convXyzD50ToLinRgb(const double *inXyz, double *outRgbL)
{
  outRgbL[0] =  3.134187 * inXyz[0] - 1.617209 * inXyz[1] - 0.490694 * inXyz[2];
  outRgbL[1] = -0.978749 * inXyz[0] + 1.916130 * inXyz[1] + 0.033433 * inXyz[2];
  outRgbL[2] =  0.071964 * inXyz[0] - 0.228994 * inXyz[1] + 1.405754 * inXyz[2];
}

// -----------------------------------------------------------------------------
// convRgbToLinRGB (from sRGB to linear sRGB)
// -----------------------------------------------------------------------------
void ColorMap::convRgbToLinRGB(const unsigned char *inRgb, double *outRgbL)
{
  double  value;
  
  for (int i = 0; i < 3; i++)
  {
    value = (double )inRgb[i] / 255.0;
    if (value <= 0.040450)
      value = value / 12.92;
    else
      value = pow((value + 0.055) / 1.055, 2.4);
    outRgbL[i] = value;
  }
}

// -----------------------------------------------------------------------------
// convLinRgbToRGB (from linear sRGB to sRGB)
// -----------------------------------------------------------------------------
void ColorMap::convLinRgbToRGB(const double *inRgbL, unsigned char *outRgb)
{
  double  value;
  
  for (int i = 0; i < 3; i++)
  {
    value = inRgbL[i];
    if (value <= 0.0031308)
      value =  value * 12.92;
    else
      value = 1.055 * pow(value, 1.0 / 2.4) - 0.055;
    
    value = value * 255;
    if (value < 0)
      value = 0;
    if (value > 255)
      value = 255;
    outRgb[i] = (unsigned char)value;
  }
}

// -----------------------------------------------------------------------------
// stringToColorMapIndex
// -----------------------------------------------------------------------------
ColorMap::ColorMapIndex ColorMap::stringToColorMapIndex(const char *inString,
                                                        ColorMapIndex inDefault)
{
  const ColorMapIndexTable  *tablePtr = kColorMapIndexTable;
  while (tablePtr->index != CMI_NOT_SPECIFIED)
  {
#ifndef WIN32
    if (::strncasecmp(inString, tablePtr->str, ::strlen(tablePtr->str)) == 0)
#else
    if (::stricmp(inString, tablePtr->str) == 0)
#endif
      return tablePtr->index;
    tablePtr++;
  }
  return inDefault;
}

// -----------------------------------------------------------------------------
// getColorMapNameTable
// -----------------------------------------------------------------------------
void ColorMap::getColorMapNameTable( std::vector<std::string> *outStrTable,
                                  std::vector<ColorMapIndex> *outIndexTable)
{
  const ColorMapIndexTable  *tablePtr = kColorMapIndexTable;
  while (tablePtr->index != CMI_ANY)
  {
    outStrTable->push_back(std::string(tablePtr->str));
    outIndexTable->push_back(tablePtr->index);
    tablePtr++;
  }
}

// Local static functions ------------------------------------------------------
// -----------------------------------------------------------------------------
// clearColorMap
// -----------------------------------------------------------------------------
static void clearColorMap(unsigned int inColorNum,  unsigned char *outColorMap)
{
  if (inColorNum == 0)
    return;
  memset(outColorMap, 0, inColorNum * 3);
}

// -----------------------------------------------------------------------------
// getD50WhitePointInXyz
// -----------------------------------------------------------------------------
static const double *getD50WhitePointInXyz()
{
  static const double  sD50WhitePoint[3] = {0.9642, 1.0, 0.8249};
  return sD50WhitePoint;
}

// -----------------------------------------------------------------------------
// getD50WhitePointInXyz
// -----------------------------------------------------------------------------
static const double *getD65WhitePointInXyz()
{
  static const double  sD65WhitePoint[3] = {0.95047, 1.0, 1.08883};
  return sD65WhitePoint;
}

// -----------------------------------------------------------------------------
// labSubFunc
// -----------------------------------------------------------------------------
static double labSubFunc(double inT)
{
  if (inT > 0.008856)
    return pow(inT, (1.0/3.0));
  return 7.78703 * inT + 16.0 / 116.0;
}

// -----------------------------------------------------------------------------
// labSubInvFunc
// -----------------------------------------------------------------------------
static double labSubInvFunc(double inT)
{
  if (inT > 0.20689)
    return pow(inT, 3);
  return (inT - 16.0 / 116.0) / 7.78703;
}

// -----------------------------------------------------------------------------
// getMultiColorMapData
// -----------------------------------------------------------------------------
static void getMultiColorMapData(ColorMap::ColorMapIndex inIndex, unsigned int inMultiNum,
                                    std::vector<ColorMapData> &outData)
{
  const ColorMapData  *colorMapData;
  unsigned int i, j, dataNum;
  double singleRatio;

  colorMapData = getColorMapData(inIndex);
  if (colorMapData == nullptr)
    return;

  dataNum = 0;
  while (colorMapData[dataNum].index == inIndex)
    dataNum++;
  singleRatio = 1.0 / (double )inMultiNum;

  outData.clear();
  for (i = 0; i < inMultiNum; i++)
  {
    for (j = 0; j < dataNum; j++)
    {
      outData.push_back(colorMapData[j]);
      outData.back().ratio = colorMapData[j].ratio * singleRatio + singleRatio * i;
    }
  }
}

// -----------------------------------------------------------------------------
// getColorMapData
// -----------------------------------------------------------------------------
static const ColorMapData *getColorMapData(ColorMap::ColorMapIndex inIndex)
{
  const ColorMapData  *colorMapData = kColorMapData;
  
  while (colorMapData->index != inIndex)
  {
    colorMapData++;
    if (colorMapData->index == ColorMap::CMI_End)
      return nullptr;
  }
  
  return colorMapData;
}
