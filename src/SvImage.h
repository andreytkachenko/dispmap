/*
 * SvImage.h
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#ifndef SVIMAGE_H_
#define SVIMAGE_H_

#include <opencv2/opencv.hpp>

using namespace cv;

class SvImage {

protected:
	Mat* image;

public:
	int  getPixel(int x, int y, int channel);
	void putPixel(int x, int y, int val);

	int  getHeight();
	int  getWidth();
	Mat& getCvMatrix();

	SvImage(Mat& image);
	virtual ~SvImage();
};

#endif /* SVIMAGE_H_ */
