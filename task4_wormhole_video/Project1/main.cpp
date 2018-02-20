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

	cv::inRange(image_hsv, cv::Scalar(150, 70, 130),
		cv::Scalar(200, 110, 200), tmp_img);
	// "Замазать" огрехи в при выделении по цвету
	cv::dilate(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 3);
	cv::erode(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 1);
	//Выделение непрерывных областей
	cv::findContours(tmp_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
}

void repaintDinos(cv::Mat image,
	std::vector< std::vector<cv::Point> >& contours,
	LinkedList& dinoList,
	int modifyer = 0)
{
	cv::Mat empty;

	for (int i = 0; i < contours.size(); i++)
	{
		dinoList.next();
		cv::Rect rect = cv::boundingRect(contours[i]);
		cv::Mat dino = dinoList.getCurrentImage();
		cv::Mat dinoSized;
		if (dino.dims > 0)
		{
			cv::resize(dino, dinoSized, rect.size());
			dinoSized.copyTo(image(rect));
		}
	}
}

int main()
{
	std::vector< std::vector<cv::Point> > contours;
	LinkedList dinos;
	cv::Mat image;
	dinos.push_back(cv::imread("pictures/dino.jpg"));
	dinos.push_back(cv::imread("pictures/dino1.png"));
	dinos.push_back(cv::imread("pictures/dino2.jfif"));
	cv::VideoCapture cap;
	if (!cap.open(0))
	{
		image = cv::imread("pictures/base.jpg");
	}
	
	int i = 0;
	if (cap.isOpened())
	{
		cap >> image;
	}
	contours.clear();
	recogniseStickersByThreshold(image, contours);
	while (cv::waitKey(10))
	{
		if (cap.isOpened())
		{
			cap >> image;
		}
		if (image.empty()) break; // end of video stream

		contours.clear();
		try {
			recogniseStickersByThreshold(image, contours);
		}
		catch (std::exception)
		{
			continue;
		}

		i++;
		repaintDinos(image, contours, dinos);
		cv::imshow("tmp", image);
	}

	return 0;
}