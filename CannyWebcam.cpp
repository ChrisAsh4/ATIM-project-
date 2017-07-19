// OpenCVWebcamTest.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

using namespace cv;
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    VideoCapture capWebcam(0);            // declare a VideoCapture object and associate to webcam, 0 => use 1st webcam

    if (capWebcam.isOpened() == false) {                                // check if VideoCapture object was associated to webcam successfully
        std::cout << "error: capWebcam not accessed successfully\n\n";      // if not, print error message to std out
        _getch();                                                           // may have to modify this line if not using Windows
        return(0);                                                          // and exit program
    }

    Mat imgOriginal;        // input image
	Mat hist;				// histogram image
    Mat imgGrayscale;       // grayscale of input image
    Mat imgBlurred;         // intermediate blured image
    Mat imgCanny;           // Canny edge image
	Mat imgHough;           // hough image
	vector<Vec4i> lines;        // Hough lines

    char charCheckForEscKey = 0;

    while (charCheckForEscKey != 27 && capWebcam.isOpened()) {            // until the Esc key is pressed or webcam connection is lost
        bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);            // get next frame

        if (!blnFrameReadSuccessfully || imgOriginal.empty()) {                 // if frame not read successfully
            std::cout << "error: frame not read from webcam\n";                 // print error message to std out
            break;                                                              // and jump out of while loop
        }


        cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale

																				// Establish the number of bins
		/*
		//-----------------------histogram
		int histSize = 256;

		float range[] = { 0, 256 };
		const float* histRange = { range };

		bool uniform = true; bool accumulate = false;

		calcHist(&imgGrayscale,					// the source of the array
					1,							// number of source arrays
					0,							// the channel (dim) to be measured
					Mat(), 
					hist, 
					1, 
					&histSize,
					&histRange, 
					uniform, 
					accumulate);;
		//--------------------histogram
		*/

        cv::GaussianBlur(imgGrayscale,              // input image
                         imgBlurred,                // output image
                         cv::Size(5, 5),            // smoothing window width and height in pixels
                         1.8);                      // sigma value, determines how much the image will be blurred

        cv::Canny(imgBlurred,                       // input image
                  imgCanny,                         // output image
                  50,                               // low threshold
                  100);                             // high threshold

		//
		//cv::cvtColor(imgOriginal, imgHough, CV_BGR2GRAY);                   // convert to grayscale

		vector<Vec4i> lines;
		HoughLinesP(imgCanny, lines, 1, CV_PI / 180, 50, 50, 10);

		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(imgOriginal, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
		}

		//

                                                    // declare windows
        cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);       // note: you can use CV_WINDOW_NORMAL which allows resizing the window
        cv::namedWindow("imgCanny", CV_WINDOW_NORMAL);          // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
		cv::namedWindow("imgHough", CV_WINDOW_NORMAL);
                                                                // CV_WINDOW_AUTOSIZE is the default
        cv::imshow("imgOriginal", imgOriginal);                 // show windows
        cv::imshow("imgCanny", imgCanny);                       //
		//cv::imshow("imgHough", imgHough);

        charCheckForEscKey = cv::waitKey(1);        // delay (in ms) and get key press, if any
	}   // end while

	return(0);
}










