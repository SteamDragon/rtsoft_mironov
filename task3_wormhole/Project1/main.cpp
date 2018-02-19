#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <vector>

int main()
{
	std::vector<cv::Mat> stickers;
	cv::Mat image = cv::imread("base.jpg");
	cv::resize(image, image, cv::Size(800, 600));
	cv::imshow("tmp", image);
	cv::waitKey(0);
	return 0;
}