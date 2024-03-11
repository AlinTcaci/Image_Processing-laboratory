#include "lab2.hh"

void utcn::ip::Lab2::runLab() {
  int op;
  do {
    utcn::ip::Lab2::printMenu(LAB_MENU);
    std::cin >> op;
    switch (op) {
      case 0:
        break;
      case 1:
        testSplitRGB();
        break;
      case 2:
        testColorToGrayscale();
        break;
      case 3:
        testColorToBW();
        break;
      case 4:
        testRGBToHSV();
        break;
      case 5:
        testIsInside();
        break;
      default:
        std::cout << "Invalid selection" << std::endl;
    }
  } while (op != 0);
}

void utcn::ip::Lab2::testSplitRGB() {
  // Create a function that will copy the R, G and B channels of a color, RGB24
  // image (CV_8UC3 type) into three matrices of type CV_8UC1 (grayscale images).
  // Display these matrices in three distinct windows.
  // Implement code here
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path, cv::IMREAD_COLOR);
    int height = src.rows;
    int width = src.cols;
    cv::Mat B = cv::Mat(height,width, CV_8UC1);
    cv::Mat G = cv::Mat(height,width, CV_8UC1);
    cv::Mat R = cv::Mat(height,width, CV_8UC1);

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        B.at<uchar>(i,j) = src.at<cv::Vec3b>(i,j)[0];
        G.at<uchar>(i,j) = src.at<cv::Vec3b>(i,j)[1];
        R.at<uchar>(i,j) = src.at<cv::Vec3b>(i,j)[2];
      }
    cv::imshow(abs_image_path, src);
    cv::imshow("Blue", B);
    cv::imshow("Green", G);
    cv::imshow("Red", R);
    //cv::waitKey(0);
    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab2::testColorToGrayscale() {
  // Create a function that will convert a color RGB24 image (CV_8UC3 type) to a grayscale
  // image (CV_8UC1) and display the result image in a destination window.
  // Implement code here
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path, cv::IMREAD_COLOR);
    int height = src.rows;
    int width = src.cols;
    cv::Mat gray = cv::Mat(height, width, CV_8UC1);

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        gray.at<uchar>(i,j) = (src.at<cv::Vec3b>(i,j)[0] + src.at<cv::Vec3b>(i,j)[1] + src.at<cv::Vec3b>(i,j)[2])/3;
      }

    cv::imshow("Original", src);
    cv::imshow("Grayscale", gray);
    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab2::testColorToBW() {
  // Create a function for converting from grayscale to black and white (binary), using (2.2).
  // Read the threshold from the console. Test the operation on multiple images and using multiple thresholds.
  // Implement code here
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    cv::Mat BW = cv::Mat(height, width, CV_8UC1);
    int threshold;
    std::cout << "Enter the threshold: ";
    std::cin >> threshold;

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        if(src.at<uchar>(i,j) > threshold) {
          BW.at<uchar>(i,j) = 255;
        } else {
          BW.at<uchar>(i,j) = 0;
        }
      }

    cv::imshow(abs_image_path, src);
    cv::imshow("Black and White", BW);
    imageutil::macOsWaitKey();
  }
}

void utcn::ip::Lab2::testRGBToHSV() {
  // Create a function that will compute the H, S and V values from the R, G, B channels of an
  // image, using the equations from section 2.6. Store each value (H, S, V) in a CV_8UC1 matrix.
  // Display these matrices in distinct windows. Check the correctness of your implementation
  // using the example below.
  // Implement code here
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path,cv::IMREAD_COLOR);
    int height = src.rows;
    int width = src.cols;
    cv::Mat H_norm = cv::Mat(height, width, CV_8UC1);
    cv::Mat S_norm = cv::Mat(height, width, CV_8UC1);
    cv::Mat V_norm = cv::Mat(height, width, CV_8UC1);

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++) {
        float b = (float)src.at<cv::Vec3b>(i,j)[0]/255;
        float g = (float)src.at<cv::Vec3b>(i,j)[1]/255;
        float r = (float)src.at<cv::Vec3b>(i,j)[2]/255;

        float M = std::max(r, std::max(g,b));
        float m = std::min(r, std::min(g,b));
        float C = M - m; //chroma

        float H = 0; //hue
        float V = M; //value
        float S = (V != 0) ? C/V : 0; //saturation

        if (C != 0) {
          H = (M == r) ? 60 * (g - b) / C : 0;
          H = (M == g) ? 120 + 60 * (b - r) / C : H;
          H = (M == b) ? 240 + 60 * (r - g) / C : H;
        } else {
          H = 0;
        }
        H = (H < 0) ? H + 360 : H;

        H_norm.at<uchar>(i,j) = (uchar)(H * 255 / 360);
        S_norm.at<uchar>(i,j) = (uchar)(S * 255);
        V_norm.at<uchar>(i,j) = (uchar)(V * 255);
      }

    cv::imshow(abs_image_path, src);
    cv::imshow("Hue", H_norm);
    cv::imshow("Saturation", S_norm);
    cv::imshow("Value", V_norm);
    imageutil::macOsWaitKey();
  }
}

bool utcn::ip::Lab2::isInside(const cv::Mat &src, const int row, const int column) {
  if(row < 0 || column < 0) return false;
  const int height = src.rows;
  const int width = src.cols;
  return row <= height && column <= width;
}

void utcn::ip::Lab2::testIsInside() {
  // Implement a function called isInside(img, i, j), which checks if the position indicated by the
  // pair (i,j) (row, column) is inside the image img.
  // Implement code here
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if(!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path);
    int i, j;
    std::cout << "Row: ";
    std::cin >> i;
    std::cout << "Column: ";
    std::cin >> j;

    isInside(src, i, j) == true ? std::cout << "it is\n" : std::cout << "its not\n";
  }
}