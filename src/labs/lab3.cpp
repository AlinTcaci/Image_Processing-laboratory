//
// Created by Alin Tcaci on 06.03.2024.
//
#include <lab3.hh>

void utcn::ip::Lab3::runLab() {
  int op;
  do {
    utcn::ip::Lab3::printMenu(LAB_MENU);
    std::cin >> op;
    switch (op) {
      case 0:
        break;
      case 1:
        testHistogramGrayscale();
      break;
      case 2:
        testComputePDF();
      break;
      case 3:
        testDisplayHistogram();
      break;
      case 4:
        testHistogramByBins();
      break;
      case 5:
        testMultilevelThresholding();
      break;
      case 6:
        testFloydSteinberg();
      break;
      case 7:
        testMultilevelThresholdingOnColorImage();
      break;
      default:
        std::cout << "Invalid selection" << std::endl;
    }
  } while (op != 0);
}

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height)
{
  cv::Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

  //computes histogram maximum
  int max_hist = 0;
  for (int i = 0; i<hist_cols; i++)
    if (hist[i] > max_hist)
      max_hist = hist[i];
  double scale = 1.0;
  scale = (double)hist_height / max_hist;
  int baseline = hist_height - 1;

  for (int x = 0; x < hist_cols; x++) {
    cv::Point p1 = cv::Point(x, baseline);
    cv::Point p2 = cv::Point(x, baseline - cvRound(hist[x] * scale));
    line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins colored in magenta
  }

  imshow(name, imgHist);
}

void utcn::ip::Lab3::testHistogramGrayscale() {
  // Compute the histogram for a given grayscale image
  // (in an array of integers having dimension 256).
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    int h[256] = {0};
    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        h[src.at<uchar>(i,j)]++;

    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        std::cout << h[i] << " ";
      }
      std::cout << "\n";
    }

    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab3::testComputePDF() {
  // Compute the PDF (in an array of floats of dimension 256).
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    int h[256] = {0};     // histogram
    float pdf[256] = {0}; // probability density function

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        h[src.at<uchar>(i,j)]++;

    for(int i = 0; i < 256; i++)
      pdf[i] = (float)h[i] / (float)(height * width);

    for(int i = 0; i < 256; i++) {
      for(int j = 0; j < 256; j++) {
        std::cout << pdf[i] << " ";
      }
      std::cout << "\n";
    }

    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab3::testDisplayHistogram() {
  // Display the computed histogram using the provided function.
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int h[256] = {0};
    int height = src.rows;
    int width = src.cols;
    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        h[src.at<uchar>(i,j)]++;

    cv::imshow("Original", src);
    showHistogram("Histogram", h, 256, height);
    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab3::testHistogramByBins() {
  // Compute the histogram for a given number of bins m ≤ 256.
}

float maximLocal(float *p, int k, int WH) {
  float maxim = -1;
  for(int i = k-WH; i <= k + WH; i++) {
    if(p[i] > maxim) maxim = p[i];
  }
  return maxim;
}

float averageLocal(float *p, int k, int WH) {
  float avg = 0;
  for(int i = k-WH; i <= k + WH; i++) {
    avg += p[i];
  }
  avg /= 2 * (float)WH + 1;
  return avg;
}

void utcn::ip::Lab3::testMultilevelThresholding() {
  // Implement the multilevel thresholding algorithm from section 3.3.
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    int h[256] = {0};
    float p[256];
    int intensity[8] = {0};
    int index = 1;
    int hMLT[256] = {0};
    cv::Mat dst = cv::Mat(height, width, CV_8UC1);

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        h[src.at<uchar>(i,j)]++;

    for(int i = 0; i < 256; i++)
      p[i] = (float)h[i] / (float)(height * width);

    for(int k = WH; k < 256 - WH; k++) {
      if(p[k] == maximLocal(p, k, WH)) {
        if(p[k] > averageLocal(p,k,WH) + TH) {
          intensity[index++] = k;
        }
      }
    }
    intensity[index] = 255;

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        int val = src.at<uchar>(i,j);
        for(int k = 0; k < index ; k++) {
          if(intensity[k] <= val && val <= intensity[k + 1]) {
            if(val - intensity[k] <= intensity[k + 1] - val) {
              dst.at<uchar>(i,j) = (uchar)intensity[k];
            } else {
              dst.at<uchar>(i,j) = (uchar)intensity[k + 1];
            }
          }
        }
      }

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        hMLT[dst.at<uchar>(i,j)]++;

    cv::imshow("MTL", dst);
    cv::imshow("Original", src);
    showHistogram("Histogram ", h, 256, height);
    showHistogram("Histogram MLT ", hMLT, 256, height);
    imageutil::macOsWaitKey();
  }
}

int saturateGreyPixel(int value) {
  if(value < 0) return 0;
  if(value > 255) return 255;
  return value;
}

void utcn::ip::Lab3::testFloydSteinberg() {
  // Enhance the multilevel thresholding algorithm using
  // the Floyd-Steinberg dithering from section 3.4.
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    cv::Mat dst = src.clone();
    int height = src.rows;
    int width = src.cols;
    int h[256] = {0};
    float p[256];
    int intensity[8] = {0};
    int index = 1;

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++)
        h[src.at<uchar>(i,j)]++;

    for(int i = 0; i < 256; i++)
      p[i] = (float)h[i] / (float)(height * width);

    for(int k = WH; k < 256 - WH; k++)
      if(p[k] == maximLocal(p, k, WH))
        if(p[k] > averageLocal(p,k,WH) + TH)
          intensity[index++] = k;

    intensity[index] = 255;

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        int oldpixel = dst.at<uchar>(i,j);
        int newpixel = 0;
        for(int k = 0; k < index ; k++) {
          if(intensity[k] <= oldpixel && oldpixel <= intensity[k + 1]) {
            if(oldpixel - intensity[k] <= intensity[k + 1] - oldpixel) {
              newpixel = (uchar)intensity[k];
            } else {
              newpixel = (uchar)intensity[k + 1];
            }
          }
        }
        dst.at<uchar>(i,j) = newpixel;

        int errorFloyd = oldpixel - newpixel;

        if (j + 1 < width) dst.at<uchar>(i, j+1) = saturateGreyPixel(dst.at<uchar>(i, j+1) + errorFloyd * 7 / 16);
        if (i + 1 < height) {
          if (j > 0) dst.at<uchar>(i+1, j-1) = saturateGreyPixel(dst.at<uchar>(i+1, j-1) + errorFloyd * 3 / 16);
            dst.at<uchar>(i+1, j) = saturateGreyPixel(dst.at<uchar>(i+1, j) + errorFloyd * 5 / 16);
          if (j + 1 < width) dst.at<uchar>(i+1, j+1) = saturateGreyPixel(dst.at<uchar>(i+1, j+1) + errorFloyd * 1 / 16);
        }
      }

    cv::imshow("Floyd", dst);
    cv::imshow("Original", src);
    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab3::testMultilevelThresholdingOnColorImage() {
  // Perform multilevel thresholding on a color image by applying the procedure from section
  // 3.3 on the Hue channel from the HSV color-space representation of the image. Modify only
  // the Hue values, keeping the S and V channels unchanged or setting them to their maximum
  // possible value. Transform the result back to RGB color-space for viewing.
}