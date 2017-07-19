#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main3()
{
	Mat src = imread("image1.jpg", 0);

	Mat dst, dst1, cdst, cdst1, cdst2, thresh;

	threshold(src, thresh, 70, 255, 3);

	//for #1 and #2
	Canny(src, dst, 80, 100, 3);
	//for #3
	Canny(thresh, dst1, 80, 100, 3);
	
	//for #1
	cvtColor(dst, cdst, CV_GRAY2BGR);
	//for #2
	cvtColor(dst, cdst1, CV_GRAY2BGR);
	//for #3
	cvtColor(dst1, cdst2, CV_GRAY2BGR);

	vector<Vec2f> lines;

	vector<Vec4i> lines1, lines2;

	
	// detect lines
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);

	// draw lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	
	HoughLinesP(dst, lines1, 1, CV_PI / 180, 50, 50, 10);

	for (size_t i = 0; i < lines1.size(); i++)
	{
		Vec4i l = lines1[i];
		line(cdst1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}

	HoughLinesP(dst1, lines2, 1, CV_PI / 180, 50, 50, 10);

	for (size_t i = 0; i < lines2.size(); i++)
	{
		Vec4i l = lines2[i];
		line(cdst2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}
	
	//results needed #1 Normal Hough Transform not probabilitic
	//imshow("Normal Hough Transform not probabilitic", cdst);

	//results needed #2 Probablistic Hough Transform
	//imshow("Probablistic Hough Transform", cdst1);

	//results needed #2 Probablistic Hough Transform with thresholding 
	//imshow("robablistic Hough Transform with thresholding", cdst2);

	imshow("robablistic Hough Transform with thresholding", cdst2);
	imshow("Probablistic Hough Transform", cdst1);
	imshow("Normal Hough Transform not probabilitic", cdst);
	imshow("wsretwref", thresh);
	imshow("Nosfefc", src);
	waitKey();
	return 0;
}
