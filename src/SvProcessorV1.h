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

using namespace std;

class SvProcessorV1 {

protected:
	SvImage*     left;
	SvImage*     right;

	std::thread  m_thread;
	SvImage*     m_stereo;
	int          m_line;

	const int windowSize = 90;

public:
	enum ImageType {
		LEFT, RIGHT
	};

	void setLeftImage(SvImage& image) { left = &image;}
	void setRightImage(SvImage& image) { right = &image;}
	bool isActive() { return m_thread.joinable(); }

	int diff(int lx, int ly, int rx, int ry);
	int match(int x, int y, int i);
	int run(SvImage& stereo, int line, ImageType base);
	int calc(SvProcessorV1* proc);

	int getPixelColor(int cursor);

	SvProcessorV1(SvImage& left, SvImage& right);
	SvProcessorV1();

	virtual ~SvProcessorV1();
};

#endif /* SVPROCESSORV1_H_ */
