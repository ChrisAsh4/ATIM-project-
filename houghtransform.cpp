#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main1()
{
	Mat src = imread("image1.jpg", 0);

	Mat dst, cdst, thresh;

	threshold(src, thresh, 70, 255, 3);

	Canny(thresh, dst, 80, 100, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);
	/*
	vector<Vec2f> lines;
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
	*/

	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}

	//imshow("source", src);
	//imshow("canny", dst);
	imshow("detected lines", cdst);
	//imshow("thresh", thresh);

	waitKey();
	return 0;

	//results needed #1 Normal Hough Transform not probabilitis

	//results needed #2 Probablistic Hough Transform

	//results needed #2 Probablistic Hough Transform with thresholding 
}
