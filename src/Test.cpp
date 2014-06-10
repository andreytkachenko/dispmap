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
} StereoData;

#define WINDOW_START   0
#define WINDOW_SIZE    150
#define MATCH_SIZE     2
#define ERROR_LEVEL    1

int getPixelValue(Mat* data, int x, int y)
{
	uchar* pixel = data->ptr(y, x);
	uchar value  = 0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2];

	return  value;
}

void normalize(Mat* mat, int x_from, int x_to, int y)
{
	int n = x_to - x_from, val;
	int sum_xy = 0, sum_x = 0, sum_y = 0, sum_x2 = 0;
	float  a, b;
	int tmp;
	uchar* data;

	for (int i = x_from; i < x_to; i++) {
		val = getPixelValue(mat, i, y);
		sum_xy += i * val;
		sum_x  += i;
		sum_y  += val;
		sum_x2 += i * i;
	}

	a = 0; //((n * sum_xy) - (sum_x * sum_y)) / ((n * sum_x2) - (sum_x * sum_x));
	b = (sum_y - a * sum_x) / n;

	for (int i = x_from; i < x_to; i++) {
		data = mat->ptr<uchar>(y, i);
		//data[0] = a * i ;
	}
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
	return (val * val) * 255.0;
}

void putPixel(Mat* mat, int x, int y, int cursor)
{
	uchar* data;


	data = mat->ptr(y, x);
	data[0] = getPixelColor(cursor);
}

void calcDepthMapMy2(StereoData &params) {
	int x, y, cursor, closest, tmp;
	int minErrorValue, tmpSmoothed, matched;
	int precursor;

	for (y = 0; y < params.stereo->rows; y++) {
		cursor = 25;precursor=25;
		for (x = 0; x < params.stereo->cols; x++) {
			closest = 999; minErrorValue = 999;matched=0;
			minErrorValue=999;

			for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
				tmp = match(params, x, y, i);
				tmpSmoothed  = tmp + (0.2 * abs(cursor - i));
	            if (tmpSmoothed < minErrorValue) {
					minErrorValue = tmpSmoothed;
					closest = i;
					matched = 1;
				} else if (tmpSmoothed == minErrorValue) {
					if (abs(cursor - i) < abs(cursor - closest)) {
						closest = i;
						matched++;
					}
				}
			}

			if (matched) {
				cursor = closest;
			}

			if (cursor - precursor > 0) {
				for (int i = precursor; i < cursor; i++) {
					putPixel(params.stereo, x + i, y, 0);
				}
			}

			putPixel(params.stereo, x + cursor, y, cursor);

			precursor=cursor;
		}
	}

	/*for (y = 0; y < params.stereo->rows; y++) {
		cursor = 0;
		for (x = 0; x < params.stereo->cols; x++) {

			closest = 999;minErrorValue = 999;matched=0;

			for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
				tmp = rmatch(params, params.stereo->cols - x, y, i);
				tmpSmoothed = tmp + (1 * abs(cursor - i));

				if (tmpSmoothed < minErrorValue) {
					minErrorValue = tmpSmoothed;
					matched = 1;
					closest = i ;
				} else if (tmpSmoothed == minErrorValue) {
					if (abs(cursor - i) < abs(cursor - closest)) {
						closest = i;
						matched++;
					}
				}
			}

			if (matched) {
				cursor = closest;

				if (minErrorValue < 50) {
					putPixel(params.stereo, params.stereo->cols - x, y, 0);
				}
			}
		}
	}*/

}


int main(int argc, char** argv) {
	StereoData params;

	Mat left = imread("left4.png", 1);
	Mat right = imread("right4.png", 1);

	Mat stereo(Mat::zeros(left.rows, left.cols, CV_8U));

	params.left = &left;
	params.right = &right;
	params.stereo = &stereo;

	//calcDepthMapDynProgr(params);
	calcDepthMapMy2(params);

	imshow("Display Image Dyn Progr", stereo);
	waitKey();

	return 0;
}
