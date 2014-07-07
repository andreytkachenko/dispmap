//============================================================================
// Name        : CSV.cpp
// Author      : Andrey
// Version     :
// Copyright   : Your copyright notice
// Description : Computer Stereo Vision in C++, Ansi-style
//============================================================================

#include <opencv2/opencv.hpp>
#include "SvImage.h"
#include "SvProcessorV1.h"
#include "SvProcessorV2.h"
#include <thread>

using namespace cv;

int main(int argc, char** argv) {
	Mat matLeft = imread("img/left12.png", 1);
	Mat matRight = imread("img/right12.png", 1);
	Mat matStereo(Mat::zeros(matLeft.rows, matLeft.cols, CV_8U));

	SvImage left(matLeft);
	SvImage right(matRight);
	SvImage stereo(matStereo);

	int line = 0;

	SvProcessorV1 proc[4];

	for (int i = 0; i < 4; i++) {
		proc[i].setLeftImage(left);
		proc[i].setRightImage(right);
	}

	while (line < stereo.getHeight()) {
		for (int i = 0; i < 4; i++) {
			if (line < stereo.getHeight() && !proc[i].isActive()) {
				proc[i].run(stereo, line++, SvProcessorV1::LEFT);
			}
		}
	}

	imshow("Display Image", stereo.getCvMatrix());
	waitKey();

	return 0;
}
