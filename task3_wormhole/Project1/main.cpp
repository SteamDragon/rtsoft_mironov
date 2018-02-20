#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <vector>
#include "LinkedList.h"
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

#include <windows.h>

inline void delay(unsigned long ms)
{
	Sleep(ms);
}

#else  /* presume POSIX */

#include <unistd.h>

inline void delay(unsigned long ms)
{
	usleep(ms * 1000);
}

#endif
void recogniseStickersByThreshold(cv::Mat image, std::vector< std::vector<cv::Point> > &contours) {
	cv::Mat image_hsv;
	cv::cvtColor(image, image_hsv, cv::COLOR_RGB2BGR); // Преобразуем в HSV
	cv::Mat tmp_img(image.size(), CV_8U);
	// Выделение подходящих по цвету областей.\
	 Цвет задается константой в цветовом пространстве RGB :)

	cv::inRange(image_hsv, cv::Scalar(200, 50, 100),
		cv::Scalar(255, 100, 200), tmp_img);
	// "Замазать" огрехи в при выделении по цвету
	cv::dilate(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 3);
	cv::erode(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 1);
	//Выделение непрерывных областей
	cv::findContours(tmp_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
}

void repaintDinos(cv::Mat image,
	std::vector< std::vector<cv::Point> >& contours,
	LinkedList& dinoList,
	int modifyer = 0)
{
	cv::Mat gref, gtpl;
	cv::cvtColor(image, gref, CV_BGR2GRAY);

	for (int i = 0; i < contours.size(); i++)
	{
			dinoList.next();
		cv::Rect rect = cv::boundingRect(contours[i]);
		cv::Mat dino = dinoList.getCurrentImage();
		cv::Mat dinoSized;
		cv::resize(dino, dinoSized, cv::Size(rect.width, rect.height));
		dinoSized.copyTo(image(rect));
	}
}

int main()
{
	std::vector< std::vector<cv::Point> > contours;
	LinkedList dinos;
	cv::Mat image = cv::imread("../../pictures/base.jpg");
	dinos.push_back(cv::imread("../../pictures/dino.jpg"));
	dinos.push_back(cv::imread("../../pictures/dino1.png"));
	dinos.push_back(cv::imread("../../pictures/dino2.jfif"));

	cv::resize(image, image, cv::Size(800, 600));
	recogniseStickersByThreshold(image, contours);

	while (cv::waitKey(600))
	{		
		repaintDinos(image, contours, dinos);
		cv::imshow("tmp", image);
	}

	return 0;
}