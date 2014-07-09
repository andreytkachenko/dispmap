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
#include "SvMultithreadProcessor.h"

class SvProcessorV2 : public SvMultithreadProcessor {

protected:

public:
	void exec();
};

#endif /* SVPROCESSOR_H_ */
