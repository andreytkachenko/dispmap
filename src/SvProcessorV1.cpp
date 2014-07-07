/*
 * SvProcessor.cpp
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#include "SvProcessorV1.h"

SvProcessorV1::SvProcessorV1(SvImage& left, SvImage& right) {
	this->left  = &left;
	this->right = &right;
}

int SvProcessorV1::getPixelColor(int cursor) {
	float val = ((1.0 + cursor) / this->windowSize);
	return (val * val) * 255.0;
}
/*
int SvProcessorV1::match(int x, int y, int j) {
	int error = 0;

	for (int i = 0; i <= 2; i++) {
		for (int g = 0; g <= 3; g++) {
			error += diff(x + i, y + g, x + i + j, y + g);
		}
	}

	return error;
}
*/
int SvProcessorV1::diff(int lx, int ly, int rx, int ry) {
	int Rvalue, Gvalue, Bvalue;

	Rvalue = abs(this->left->getPixel(lx, ly, 0) - this->right->getPixel(rx, ry, 0));
	Gvalue = abs(this->left->getPixel(lx, ly, 1) - this->right->getPixel(rx, ry, 1));
	Bvalue = abs(this->left->getPixel(lx, ly, 2) - this->right->getPixel(rx, ry, 2));

	return (Gvalue + Rvalue + Bvalue) +
		   ((abs(Gvalue - Rvalue) + abs(Bvalue - Gvalue)) * 4);
}

int SvProcessorV1::match(int x, int y, int j) {
	int error = 0;
	int ms = 3;
	int c = diff(x, y, x + j, y),
	    l = 0, r = 0, t = 0, b = 0;

	error = c;

	for (int i = 1; i <= ms; i++) {
		l += diff(x - i, y, x + j - i, y);
		r += diff(x + i, y, x + j + i, y);
		t += diff(x, y - i, x + j, y - i);
		b += diff(x, y + i, x + j, y + i);
	}

	error += l > r ? r : l;
	error += t > b ? b : t;
	//error += l + r+b+t;

	return error;
}

void SvProcessorV1::run(SvImage& stereo, ImageType base = LEFT) {
	int x, y, cursor, closest, tmp;
	int minErrorValue, tmpSmoothed, matched;
	int precursor, preprecursor;

	for (y = 0; y < stereo.getHeight(); y++) {
		cursor       = 0;
		precursor    = 0;
		preprecursor = 0;
		for (x = 0; x < stereo.getWidth(); x++) {
			closest = -1; minErrorValue = -1;matched=0;
			minErrorValue=-1;

			for (int i = 1; i < this->windowSize; i++) {
				tmp = this->match(x, y, i);
				tmpSmoothed  = (tmp) + (abs(cursor - i) * 5);
				/*if (tmpSmoothed > 150 ) {
					continue;
				}*/

				if (tmpSmoothed < minErrorValue || minErrorValue == -1) {
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

			if (matched == 1) {
				cursor = closest;
			}

			//stereo.putPixel(x, y, minErrorValue/20);

			if (cursor != precursor) {
				stereo.putPixel(x, y, this->getPixelColor(cursor));
			}

			preprecursor = precursor;
			precursor = cursor;
		}
	}
}

SvProcessorV1::~SvProcessorV1() {

}

