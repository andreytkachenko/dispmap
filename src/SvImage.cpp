/*
 * SvImage.cpp
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#include "SvImage.h"

int SvImage::getPixel(int x, int y, int channel = -1) {
	if (y >= this->image->rows || y < 0 || x >= this->image->cols || x < 0) {
		return 0;
	}

	uchar* pixel = this->image->ptr(y, x);
	uchar value;

	if (channel == -1 || channel > 2) {
		value = 0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2];
	} else {
		value = pixel[channel];
	}

	return  value;
}

int SvImage::getPixelHue(int x, int y) {
	uchar* pixel = this->image->ptr(y, x);
	if (x >= 0 && x < this->image->cols && y >= 0 && y < this->image->rows) {
		return abs(pixel[1] - pixel[0]) + abs(pixel[2] - pixel[1]);
	}

	return 0;
}

int SvImage::getPixelValue(int x, int y) {
	uchar* pixel = this->image->ptr(y, x);
	if (x >= 0 && x < this->image->cols && y >= 0 && y < this->image->rows) {
		return (pixel[0] + pixel[1] + pixel[2])/3;
	}

	return 0;
}

void SvImage::putPixel(int x, int y, int value)
{
	uchar* data;

	if (x >= 0 && x < this->image->cols && y >= 0 && y < this->image->rows) {
		data = this->image->ptr(y, x);
		data[0] = value;
	}
}

int SvImage::getHeight() {
	return this->image->rows;
}

int SvImage::getWidth() {
	return this->image->cols;
}

Mat& SvImage::getCvMatrix() {
	return *this->image;
}

SvImage::SvImage(Mat& image) {
	this->image = &image;
}

SvImage::~SvImage() {

}

