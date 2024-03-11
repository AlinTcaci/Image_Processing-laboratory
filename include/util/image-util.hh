#ifndef IMAGE_UTIL_HH
#define IMAGE_UTIL_HH

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace utcn::ip {
class ImageUtil {
 public:
  static void resizeImg(const cv::Mat& src, cv::Mat& dst, int maxSize,
                        bool interpolate);
  static void macOsWaitKey();
};
}  // namespace utcn::ip

#endif  // IMAGE_UTIL_HH
