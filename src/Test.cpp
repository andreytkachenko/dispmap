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
#include <algorithm>

using namespace std;
using namespace cv;

typedef struct {
	Mat* left;
	Mat* right;
	Mat* stereo;
	Mat* temp;
	std::vector<int> match;
} StereoData;

#define WINDOW_START   0
#define WINDOW_SIZE    80
#define MATCH_SIZE_X   3
#define MATCH_SIZE_Y   3
#define ERROR_LEVEL    0
#define Y_CORRECTION   0
#define COLOR_SCALE    4

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
		if (offset == 0 || offset == 2) {
			value = pixel[offset] & 0x1F;
		} else {
			value = pixel[offset] & 0x3F;
		}
		value = pixel[offset];
	}

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
	int error = 0, val;
	int Rvalue, Gvalue, Bvalue;
	params.match.clear();
	for (int i = -(MATCH_SIZE_X / 2); i < MATCH_SIZE_X / 2; i++) {
		if (x + j + i >= params.right->cols) {
			return 999;
		}

		for (int g = -(MATCH_SIZE_Y / 2); g < MATCH_SIZE_Y / 2; g++) {
			val = 0;
			if (y + g >= params.right->rows) {
				return 999;
			}

			Rvalue = abs(getPixelValue(params.left, x + i, y + g, 0) - getPixelValue(params.right, x + j + i, y + g, 0));
			Gvalue = abs(getPixelValue(params.left, x + i, y + g, 1) - getPixelValue(params.right, x + j + i, y + g, 1));
			Bvalue = abs(getPixelValue(params.left, x + i, y + g, 2) - getPixelValue(params.right, x + j + i, y + g, 2));

			val += Rvalue << COLOR_SCALE;
			val += Gvalue << COLOR_SCALE;
			val += Bvalue << COLOR_SCALE;

			params.match.push_back(g * MATCH_SIZE_X + i);
			error += val;
		}
	}

	std::sort(params.match.begin(), params.match.end());

	return error;
}

int rmatch(StereoData &params, int x, int y, int j) {
	int error = 0;

	for (int i = 0; i < MATCH_SIZE_X; i++) {
		if (x - j - i < 0) {
			return 999;
		}

		for (int g = 0; g < MATCH_SIZE_Y; g++) {
			if (y + g >= params.left->rows) {
				return 999;
			}

			error += abs(getPixelValue(params.right, x - i, y + g, 0) - getPixelValue(params.left, x - j - i, y + g, 0));
			error += abs(getPixelValue(params.right, x - i, y + g, 1) - getPixelValue(params.left, x - j - i, y + g, 1));
			error += abs(getPixelValue(params.right, x - i, y + g, 2) - getPixelValue(params.left, x - j - i, y + g, 2));
		}
	}

	return error;
}

int getPixelColor(int cursor)
{
	float val = ((1.0 + cursor) / WINDOW_SIZE);
	return (val * val) * 255.0;
}

void putPixelValue(Mat* mat, int x, int y, int value)
{
	uchar* data;

	if (x >= 0 && x < mat->cols && y >= 0 && y < mat->rows) {
		data = mat->ptr(y, x);
		data[0] = value;
	}
}

void putPixel(Mat* mat, int x, int y, int cursor)
{
	putPixelValue(mat, x, y, getPixelColor(cursor));
}

void calcDepthMapMy2(StereoData &params) {
	int x, y, cursor, closest, tmp, minLevel=0;
	int minErrorValue, tmpSmoothed, matched;
	int precursor, preprecursor;

	for (y = 0; y < params.stereo->rows; y++) {
		cursor       = 0;
		precursor    = 0;
		preprecursor = 0;
		for (x = 0; x < params.stereo->cols; x++) {
			closest = 999; minErrorValue = 999;matched=0;
			minErrorValue=999;

			for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
				tmp = match(params, x, y, i);
				tmpSmoothed  = (tmp) + ((abs(cursor - i)) >> 4);
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


			if (closest-cursor > 0 && closest-cursor < 5) {
				for (int i = cursor; i < closest; i++) {
					putPixel(params.stereo, x + i, y, 0);
				}
			}


			if (matched == 1) {
				//if (cursor != closest) {
				if (params.match.size() > 2)  {
					int a = params.match.at(0);
					int dx = a % MATCH_SIZE_X;
					int dy = a / MATCH_SIZE_X;

					putPixel(params.stereo, (x + closest) + dx, y + dy, closest);

					a = params.match.at(1);
					dx = a % MATCH_SIZE_X;
					dy = a / MATCH_SIZE_X;

					putPixel(params.stereo, (x + closest) + dx, y + dy, closest);

					a = params.match.at(2);
					dx = a % MATCH_SIZE_X;
					dy = a / MATCH_SIZE_X;

					putPixel(params.stereo, (x + closest) + dx, y + dy, closest);
				}

				//putPixel(params.stereo, (x + closest), y, closest);
				cursor = closest;
			}

			preprecursor = precursor;
			precursor = cursor;
		}


		/*cursor = 25;precursor=25;
		for (x = params.stereo->cols; x >= 0; x--) {
			closest = 999; minErrorValue = 999;matched=0;
			minErrorValue=999;

			for (int i = WINDOW_START; i < WINDOW_SIZE; i++) {
				tmp = rmatch(params, x, y, i);
				tmpSmoothed  = tmp + (0.0 * abs(cursor - i));
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

			//if (abs(cursor - precursor)) {
				//if (abs(getPixelColor(cursor) - getPixelValue(params.stereo, x, y)) < 50) {
					//if (getPixelValue(params.stereo, x, y) == getPixelColor(cursor)) {
						putPixel(params.temp, x, y, cursor);
					//} else {

						//putPixel(params.stereo, x, y, 0);
					//}

				//} else {
				///	putPixel(params.stereo, x, y, 0);
				//}
			//}

			precursor=cursor;
		}*/
	}
}

void smooth(StereoData &params)
{
	int t = 2;
	int i,j, x,y,val,tmp,diff = 0;
	int count = 0, e=0, preval;

	for (y = 0; y < params.stereo->rows; y++) {
		for (x = 0; x < params.stereo->cols; x++) {
			count=0; diff=0, e=0;
			val = getPixelValue(params.stereo, x, y, 0);
			if (val) {
				for (i=-t; i <= t; i++) {
					for (j=-t; j <= t; j++) {
						if (y >= params.stereo->rows || y < 0 || x >= params.stereo->cols || x < 0) {
							continue;
						}

						if (i==0 && j==0) {
							continue;
						}

						uchar* pixel = params.stereo->ptr(y+i, x+j);


						tmp = pixel[0];
						if (tmp) {
							diff += abs(val-tmp);
							e += tmp;
							count++;
						} else {

						}
					}
				}


				/*if (count && diff < 300) {
					putPixelValue(params.temp, x, y, val);
				} else */if (count) {
					putPixelValue(params.temp, x, y, e/count);
				}
			}
		}
	}
}


int main(int argc, char** argv) {
	StereoData params;

	Mat left = imread("left4_.png", 1);
	Mat right = imread("right4_.png", 1);

	Mat stereo(Mat::zeros(left.rows, left.cols, CV_8U));
	Mat temp(Mat::zeros(left.rows, left.cols, CV_8U));

	params.left = &left;
	params.right = &right;
	params.stereo = &stereo;
	params.temp = &temp;

	//calcDepthMapDynProgr(params);
	calcDepthMapMy2(params);
	//smooth(params);

	imshow("Display Image Stereo", stereo);
	//imshow("Display Image Smoothed", temp);

	waitKey();

	return 0;
}
