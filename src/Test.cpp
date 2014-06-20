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
#define WINDOW_SIZE    80
#define MATCH_SIZE_X   1
#define MATCH_SIZE_Y   1
#define ERROR_LEVEL    300
#define COLOR_SCALE    0

int getPixelValue(Mat* data, int x, int y, int offset = -1)
{
	if (y >= data->rows || y < 0 || x >= data->cols || x < 0) {
		return 0;
	}

	uchar* pixel = data->ptr(y, x);
	uchar value;

	if (offset == -1 || offset > 2) {
		value = 0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2];
	} else {
		value = pixel[offset];
	}

	return  value;
}


int getPixelColor(int cursor)
{
	float val = ((1.0 + cursor) / WINDOW_SIZE);
	return (val * val) * 255.0;
}

void putPixel(Mat* mat, int x, int y, int cursor)
{
	uchar* data;

	if (x >= 0 && x < mat->cols && y >= 0 && y < mat->rows) {
		data = mat->ptr(y, x);
		data[0] = getPixelColor(cursor);
	}
}

void normalize(StereoData& params, int x_from, int x_to, int y)
{
	/*int n = x_to - x_from, val;
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
	}*/
}

int match(StereoData &params, int x, int y, int j, bool backwise=false) {
	int error = 0, offset;
	int Rvalue, Gvalue, Bvalue;
	int sign=backwise?-1:1;
	int MX2 = MATCH_SIZE_X >> 1, MY2 = MATCH_SIZE_Y >> 1;


	for (int i = -MX2; i <= MX2; i++) {
		offset = x + (j*sign) + (i*sign);
		if (offset < 0 || offset >= params.right->cols) {
			return 999;
		}

		for (int g = -MY2; g <= MY2; g++) {
			if (y + g >= params.right->rows) {
				return 999;
			}

			Rvalue = abs(getPixelValue(params.left, x + (i*sign), y + g, 0) - getPixelValue(params.right, offset, y + g, 0));
			Gvalue = abs(getPixelValue(params.left, x + (i*sign), y + g, 1) - getPixelValue(params.right, offset, y + g, 1));
			Bvalue = abs(getPixelValue(params.left, x + (i*sign), y + g, 2) - getPixelValue(params.right, offset, y + g, 2));

			error += Rvalue << COLOR_SCALE;
			error += Gvalue << COLOR_SCALE;
			error += Bvalue << COLOR_SCALE;
		}
	}

	return error;
}

int closestMatch(StereoData& params, int cursor, int x, int y, bool backwise = false) {
	int tmp, tmpSmoothed=999, minErrorValue=999, matched=0;
	int closest=999;

	for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
		tmp = match(params, x, y, i, backwise);

		if (tmp > ERROR_LEVEL) continue;

		tmpSmoothed  = tmp + (0.1 * abs(cursor - i));
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

	return matched ? closest : -1;
}

void calcLineBackwise(StereoData& params, int y) {
	int closest, diff;
	int cursor       = WINDOW_SIZE/2;
	int precursor    = WINDOW_SIZE/2;
	int preprecursor = WINDOW_SIZE/2;

	for (int x = params.stereo->cols - 1; x >= 0 ; x--) {
		closest = closestMatch(params, cursor, x, y, true);

		if (closest != -1) {
			diff = closest - cursor;

			if (diff > 0 /*&& diff < 5*/) {
				for (int i = cursor; i < closest; i++) {
					putPixel(params.stereo, x - i, y, 0);
				}
			}

			cursor = closest;
			putPixel(params.stereo, x - cursor, y, cursor);
		}

		preprecursor = precursor;
		precursor = cursor;
	}
}

void calcLine(StereoData& params, int y) {
	int closest, diff;
	int cursor       = WINDOW_SIZE/2;
	int precursor    = WINDOW_SIZE/2;
	int preprecursor = WINDOW_SIZE/2;

	for (int x = 0; x < params.stereo->cols; x++) {
		closest = closestMatch(params, cursor, x, y);

		if (closest != -1) {
			diff = closest - cursor;

			if (diff > 0 && diff < 5) {
				for (int i = cursor; i <= closest; i++) {
					putPixel(params.stereo, x + i, y, 0);
				}
			}

			cursor = closest;
			putPixel(params.stereo, x + cursor, y, cursor);
		}

		preprecursor = precursor;
		precursor = cursor;
	}
}

void calcDepthMapMy2(StereoData &params) {
	for (int y = 0; y < params.stereo->rows; y++) {
		calcLine(params, y);
	}
}

int main(int argc, char** argv) {
	StereoData params;

	Mat left = imread("left8.png", 1);
	Mat right = imread("right8.png", 1);

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
