#include "highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>                    
#include<iostream>
#include<fstream>
#include<time.h>
//#include "vld.h"
#define coordinatespath  "D:\\coordinatesdata.txt"
#define picturepath "E:\\capture.jpg"

using namespace cv;
void onMouse(int event, int x, int y, int flags, void* param);
//int rectanglex1 = 0, rectangley1 = 0, rectanglex2 = 0, rectangley2 = 0;
FILE * coordinatesdata;
int prex, prey;
int curx, cury;
IplImage *frame;
//CvCapture *capture;
int main(int argc, char** argv)
{
	CvCapture *capture;
	if ((coordinatesdata = fopen(coordinatespath, "w")) == NULL)
	{
		fprintf(stdout,"Can't opne %s\n", coordinatespath);
		//getch();
		exit(1);
	}


	

	cvNamedWindow("Webcam", 0);
	capture = cvCaptureFromCAM(0);
	//capture = cvCaptureFromFile("11000.avi");
	cvSetMouseCallback("Webcam", onMouse, NULL);
	while ((frame = cvQueryFrame(capture)))
	{
		//frame = cvQueryFrame(capture);
		//frame = cvLoadImage(picturepath, -1);
		if (!frame) {fprintf(stdout,"error frame" ); break; }
		//show the rectangle:
		cvRectangle(
			frame,
			cvPoint(prex, prey),
			cvPoint(curx, cury),
			Scalar(0, 0, 255),
			2,
			1,
			0
			);

		cvShowImage("Webcam", frame);
		if (cvWaitKey(10) >= 0)
		{
			break;
		}
		//cvReleaseImage(&frame);
	}

	cvDestroyWindow("Webcam");
	cvReleaseCapture(&capture);
	
	if (fclose(coordinatesdata) != 0)
	{
		fprintf(stderr, "Error closingfile!\n");
	}
	return 0;
}
void onMouse(int Event, int x, int y, int flags, void* param)
{
	
	//curx = 0, cury = 0;
	//int width = 0, height = 0;
	if (Event == CV_EVENT_LBUTTONDOWN)
	{
		prex = x;
		prey = y;

		fprintf(coordinatesdata, "%d\n%d\n", x, y);
		fprintf(stdout, "%d\n%d\n", prex, prey);//µ÷ÊÔÊ¹ÓÃ
	}



	 if (Event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		//Mat img(frame, 0);
		cvRectangle(
			frame,
			cvPoint(prex, prey),
			cvPoint(x,y),
			Scalar(0,255,255),
			3,
			1,
			0
			);
		cvShowImage("Webcam",frame);
		//cvReleaseMat(&img);
		//fprintf(stdout, "moving\n");
	}

	 if (Event == CV_EVENT_LBUTTONUP)
	{
		curx = x;
		cury = y;
		fprintf(coordinatesdata, "%d\n%d\n", x - prex, y - prey);
		fflush(coordinatesdata);
		fprintf(stdout, "%d\n%d\n", x - prex, y - prey);//µ÷ÊÔÊ¹ÓÃ
	}
		//printf("The Event is : %d ", Event);
	//printf("The flags is : %d ", flags);
	//printf("The param is : %d\n", param);
}
