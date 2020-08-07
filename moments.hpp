#ifndef MOMEMTS
#define MOMENTS


void pre_compute_power_arrays(const cv::Size s);
cv::Moments drt_moments(const cv::Mat& image);
#endif // MOMENTS
