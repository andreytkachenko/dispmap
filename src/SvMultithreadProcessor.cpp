/*
 * SvMultithreadProcessor.cpp
 *
 *  Created on: 09 июля 2014 г.
 *      Author: andrey
 */

#include "SvMultithreadProcessor.h"

SvMultithreadProcessor::SvMultithreadProcessor(SvImage& left, SvImage& right) {
	m_left   = &left;
	m_right  = &right;
	m_stereo = NULL;
	m_line   = 0;
}

SvMultithreadProcessor::SvMultithreadProcessor() {

}

int SvMultithreadProcessor::run(SvImage& stereo, int line) {
	m_stereo = &stereo;
	m_line   = line;
	m_thread = std::thread(&SvMultithreadProcessor::process, this);

	return 0;
}

void SvMultithreadProcessor::process() {
	exec();
	m_thread.detach();
}

void SvMultithreadProcessor::exec() {

}

SvMultithreadProcessor::~SvMultithreadProcessor() {
	if (m_thread.joinable()) {
		m_thread.detach();
	}
}

