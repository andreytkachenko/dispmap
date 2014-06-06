//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

typedef struct {
	Mat* left;
	Mat* right;
	Mat* stereo;
	Mat* visited;
} StereoData;

#define WINDOW_START   0
#define WINDOW_SIZE    70
#define MATCH_SIZE     3
#define ERROR_LEVEL    1

int getPixelValue(Mat* data, int x, int y)
{
	uchar* pixel = data->ptr(y, x);

	return pixel[0];
}

int match(StereoData &params, int x, int y, int j) {
	int error = 0;
	for (int i = 0; i < MATCH_SIZE; i++) {
		if (x + j + i >= params.right->cols) {
			return 999;
		}

		for (int g = 0; g < MATCH_SIZE; g++) {
			if (y + g >= params.right->rows) {
				return 999;
			}
			error += abs(getPixelValue(params.left, x + i, y + g) - getPixelValue(params.right, x + j + i, y + g));
		}
	}

	return error;
}

int rmatch(StereoData &params, int x, int y, int j) {
	int error = 0;
	for (int i = 0; i < MATCH_SIZE; i++) {
		if (x - j - i < 0) {
			return 999;
		}

		for (int g = 0; g < MATCH_SIZE; g++) {
			if (y + g >= params.left->rows) {
				return 999;
			}

			error += abs(getPixelValue(params.right, x - i, y + g) - getPixelValue(params.left, x - j - i, y + g));
		}
	}

	return error;
}

int getPixelColor(int cursor)
{
	float val = ((1.0 + cursor) / WINDOW_SIZE);
	return (val * val * val) * 255.0;
}

void putPixel(Mat* mat, int x, int y, int cursor)
{
	uchar* data;


	data = mat->ptr(y, x);
	data[0] = getPixelColor(cursor);
}


void calcDepthMapMy2(StereoData &params) {
	int x, y, cursor, cursor2, closest;
	int minErrorValue, tmp, minLevel = 0, tmpSmoothed;
	int rightLevel = 0, matched;

	for (y = 0; y < params.stereo->rows; y++) {
		cursor = 0; cursor2 = 0;rightLevel=0;
		for (x = 0; x < params.stereo->cols; x++) {
			closest = 999; minErrorValue = 999;matched=0;
			for (int i = 0; i < WINDOW_SIZE; i++) {
				if (getPixelValue(params.visited, x + i, y)) {
					continue;
				}

				tmp = match(params, x, y, i);
				tmpSmoothed = tmp;

				if (tmp < minErrorValue) {
					minErrorValue = tmp;
					closest = i;
					matched = 1;
				} else if (tmp == minErrorValue) {
					if (abs(cursor - i) < abs(cursor - closest)) {
						closest = i ;
						matched++;
					}
				}
			}

			if (matched) {
				cursor = closest;
				putPixel(params.visited, x + cursor, y, 50);
				putPixel(params.stereo, x, y, cursor);
			}



			/*closest = 999;minErrorValue = 999;

			for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
				tmp = rmatch(params, params.stereo->cols - x, y, i) ;
				if (tmp < minErrorValue) {
					minErrorValue = tmp;
					closest = i;
				}

				if (tmp == minErrorValue) {
					if (abs(cursor2 - i) < abs(cursor2 - closest)) {
						closest = i;
					}
				}
			}

			if (closest != 999) {
				if (cursor2 != closest) {
					cursor2 = closest;
					putPixel(params, params.stereo->cols - x, y, cursor2);
				}
			}*/
		}
	}
}

int main(int argc, char** argv) {
	StereoData params;

	Mat left = imread("left6.png", 1);
	Mat right = imread("right6.png", 1);

	cvtColor(left, left, CV_BGR2GRAY);
	cvtColor(right, right, CV_BGR2GRAY);

	Mat stereo(Mat::zeros(left.rows, left.cols, CV_8U));
	Mat visited(Mat::zeros(left.rows, left.cols, CV_8U));

	params.visited = &visited;
	params.left = &left;
	params.right = &right;
	params.stereo = &stereo;

	//calcDepthMapDynProgr(params);
	calcDepthMapMy2(params);

	imshow("Display Image Dyn Progr", stereo);
	//imshow("Display Image Dyn Progr1", visited);
	waitKey();

	return 0;
}
