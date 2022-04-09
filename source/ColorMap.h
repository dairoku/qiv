// =============================================================================
//  ColorMap.h
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
  \date     2022/02/27
*/
#ifndef QIV_COLOR_MAP_H
#define QIV_COLOR_MAP_H

// Includes --------------------------------------------------------------------
#include <vector>
#include <string>

// -----------------------------------------------------------------------------
// ColorMap class
// -----------------------------------------------------------------------------
class  ColorMap
{
public:
  // Constatns -----------------------------------------------------------------
  enum ColorMapIndex  // = CMI_
  {
    CMI_NOT_SPECIFIED  = 0,

    // Linear
    CMI_GrayScale   = 1,
    CMI_Jet,
    CMI_Rainbow,
    CMI_RainbowWide,
    CMI_Spectrum,
    CMI_SpectrumWide,
    CMI_Thermal,
    CMI_ThermalWide,

    // Diverging
    CMI_CoolWarm,
    CMI_PurpleOrange,
    CMI_GreenPurple,
    CMI_BlueDarkYellow,
    CMI_GreenRed,

    CMI_ANY            = 32767,

    // For Internal use only
    CMI_End         = -1
  };

  // Static Functions ----------------------------------------------------------
  static void getColorMap(ColorMapIndex inIndex, unsigned int inColorNum,
                          unsigned char *outColorMap,
                          unsigned int inMultiNum = 1,
                           double inGain = 1.0, int inOffset = 0);
  static void getMonoMap(int inColorNum,  unsigned char *outColorMap, double inGamma = 1.0,
                          double inGain = 1.0, int inOffset = 0.0);
  static void calcLinearColorMap(const unsigned char *inRgb0, const unsigned char *inRgb1,
                                 unsigned int inOffset, unsigned int inColorNumAll,
                                 unsigned int inMapNum, unsigned char *outColorMap);
  static void calcDivergingColorMap(const unsigned char *inRgb0, const unsigned char *inRgb1,
                                    unsigned int inOffset, unsigned int inColorNumAll,
                                    unsigned int inMapNum, unsigned char *outColorMap);
  static void interpolateColor(const unsigned char *inRgb0, const unsigned char *inRgb1,
                   double inInterp, unsigned char *outRgb);
  static double adjustHue(const double *inMsh, double inMunsat);
  static void convRgbToMsh(const unsigned char *inRgb, double *outMsh);
  static void convMshToRgb(const double *inMsh, unsigned char *outRgb);
  static void convLabToMsh(const double *inLab, double *outMsh);
  static void convMshToLab(const double *inMsh, double *outLab);
  static void convXyzD50ToLab(const double *inXyz, double *outLab);
  static void convLabToXyzD50(const double *inLab, double *outXyz);
  static void convXyzD65ToLab(const double *inXyz, double *outLab);
  static void convLabToXyzD65(const double *inLab, double *outXyz);
  static void convLinRgbToXyz(const double *inRgbL, double *outXyz);
  static void convXyzToLinRgb(const double *inXyz, double *outRgbL);
  static void convLinRgbToXyzD50(const double *inRgbL, double *outXyz);
  static void convXyzD50ToLinRgb(const double *inXyz, double *outRgbL);
  static void convRgbToLinRGB(const unsigned char *inRgb, double *outRgbL);
  static void convLinRgbToRGB(const double *inRgbL, unsigned char *outRgb);
  static ColorMapIndex stringToColorMapIndex(const char *inString,
                            ColorMapIndex inDefault = CMI_NOT_SPECIFIED);
  static void getColorMapNameTable( std::vector<std::string> *outStrTable,
                                    std::vector<ColorMapIndex> *outIndexTable);
};

#endif //QIV_COLOR_MAP_H
