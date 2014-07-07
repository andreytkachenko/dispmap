/*
 * SvProcessor.h
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#ifndef SVPROCESSOR_H_
#define SVPROCESSOR_H_

#include <iostream>
#include "SvImage.h"

using namespace std;

class SvProcessorV2 {
protected:
	SvImage*     left;
	SvImage*     right;
	std::vector<int>* lineLeft;
	std::vector<int>* lineRight;

public:
	enum ImageType {
		LEFT, RIGHT
	};

	void scanLine(int pos, ImageType type);

	void run(SvImage& stereo, ImageType base);

	SvProcessorV2(SvImage& left, SvImage& right);
	virtual ~SvProcessorV2();
};

#endif /* SVPROCESSOR_H_ */
