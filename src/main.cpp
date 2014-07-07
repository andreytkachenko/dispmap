/*
 * main.cpp
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#include <opencv2/opencv.hpp>
#include "SvImage.h"
#include "SvProcessorV1.h"
#include "SvProcessorV2.h"

using namespace cv;

int main(int argc, char** argv) {
	Mat matLeft = imread("img/left11.png", 1);
	Mat matRight = imread("img/right11.png", 1);
	Mat matStereo(Mat::zeros(matLeft.rows, matLeft.cols, CV_8U));

	SvImage left(matLeft);
	SvImage right(matRight);
	SvImage stereo(matStereo);

	SvProcessorV1 proc(left, right);
	proc.run(stereo, SvProcessorV1::LEFT);

	imshow("Display Image", stereo.getCvMatrix());
	waitKey();

	return 0;
}
