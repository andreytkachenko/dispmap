/*
 * SvProcessor.h
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#ifndef SVPROCESSORV1_H_
#define SVPROCESSORV1_H_

#include <iostream>
#include <thread>
#include "SvImage.h"
#include "SvMultithreadProcessor.h"

using namespace std;

class SvProcessorV1 : public SvMultithreadProcessor {

protected:
	const int    windowSize = 90;

public:
	int diff(int lx, int ly, int rx, int ry);
	int match(int x, int y, int i);
	void exec();

	int getPixelColor(int cursor);
};

#endif /* SVPROCESSORV1_H_ */
