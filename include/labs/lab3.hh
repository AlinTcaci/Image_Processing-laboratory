//
// Created by Alin Tcaci on 07.03.2024.
//

#ifndef LAB3_HH
#define LAB3_HH


#include <chrono>
#include <filesystem>


#include "lab.hh"

namespace utcn::ip {
class Lab3: public Lab {
  static inline std::map<int, std::string> LAB_MENU = {
    {1,
      "Compute the histogram for a given grayscale image"
      "(in an array of integers having dimension 256)"},
    {2, "Compute the PDF (in an array of floats of dimension 256)."},
    {3, "Display the computed histogram using the provided function."},
    {4, "Compute the histogram for a given number of bins m ≤ 256."},
    {5, "Implement the multilevel thresholding algorithm from section 3.3."},
    {6, "Enhance the multilevel thresholding algorithm using the Floyd-Steinberg dithering."},
    {7,
        "Perform multilevel thresholding on a color image by applying the procedure from 3.3 on"
        "the Hue channel from the HSV color-space representation of the image."},
  };

  static inline float TH = 0.0003;
  static inline int WH = 5;

  static void testHistogramGrayscale();

  static void testComputePDF();

  static void testDisplayHistogram();

  static void testHistogramByBins();

  static void testMultilevelThresholding();

  static void testFloydSteinberg();

  static void testMultilevelThresholdingOnColorImage();

  public:
    void runLab() override;
};
}

#endif //LAB3_HH
