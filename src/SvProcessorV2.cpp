/*
 * SvProcessor.cpp
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#include "SvProcessorV2.h"

SvProcessorV2::SvProcessorV2(SvImage& left, SvImage& right) {
	this->left  = &left;
	this->right = &right;
	this->lineLeft  = new std::vector<int>();
	this->lineRight = new std::vector<int>();
}

void SvProcessorV2::scanLine(int pos, ImageType type) {
	SvImage*     image;
	std::vector<int>* line;

	if (type == LEFT) {
		image = this->left;
		line  = this->lineLeft;
	} else {
		image = this->right;
		line  = this->lineRight;
	}
}

void SvProcessorV2::run(SvImage& stereo, ImageType base = LEFT) {
	int x, y, cl, pv, ppv;
	int flag = 0, tmp;

	for (y = 0; y < stereo.getHeight(); y++) {
		flag = false;
		for (x = 0; x < stereo.getWidth(); x++) {
			cl   = (this->left->getPixel(x, y, -1));
			tmp = abs((pv - ppv) + (cl - pv)) > 10;
			stereo.putPixel(x, y, abs((pv - ppv) + (cl - pv)));

			ppv = pv;
			pv  = cl;
		}
	}
}

SvProcessorV2::~SvProcessorV2() {
	delete this->lineLeft;
	delete this->lineRight;
}

