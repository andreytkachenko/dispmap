/*
 * SvMultithreadProcessor.h
 *
 *  Created on: 09 июля 2014 г.
 *      Author: andrey
 */

#ifndef SVMULTITHREADPROCESSOR_H_
#define SVMULTITHREADPROCESSOR_H_

#include <thread>
#include "SvImage.h"

class SvMultithreadProcessor {

protected:
	SvImage*     m_left;
	SvImage*     m_right;
	SvImage*     m_stereo;

	std::thread  m_thread;
	int          m_line;

public:

	void setLeftImage(SvImage& image) { m_left = &image;}
	void setRightImage(SvImage& image) { m_right = &image;}
	bool isActive() { return m_thread.joinable(); }
	void join() { m_thread.join(); }
	void detach() { m_thread.detach(); }

	int run(SvImage& stereo, int line);
	void process();
	virtual void exec();

	SvMultithreadProcessor(SvImage& left, SvImage& right);
	SvMultithreadProcessor();

	virtual ~SvMultithreadProcessor();
};

#endif /* SVMULTITHREADPROCESSOR_H_ */
