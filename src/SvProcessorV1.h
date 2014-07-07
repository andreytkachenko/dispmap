/*
 * SvProcessor.h
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#ifndef SVPROCESSORV1_H_
#define SVPROCESSORV1_H_

#include <iostream>
#include "SvImage.h"

using namespace std;

class SvProcessorV1 {

protected:
	SvImage*     left;
	SvImage*     right;

	const int windowSize = 90;

public:
	enum ImageType {
		LEFT, RIGHT
	};
	int diff(int lx, int ly, int rx, int ry);
	int match(int x, int y, int i);
	void run(SvImage& stereo, ImageType base);
	int getPixelColor(int cursor);

	SvProcessorV1(SvImage& left, SvImage& right);
	virtual ~SvProcessorV1();
};

#endif /* SVPROCESSORV1_H_ */
