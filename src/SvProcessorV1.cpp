/*
 * SvProcessor.cpp
 *
 *  Created on: 27 июня 2014 г.
 *      Author: andrey
 */

#include "SvProcessorV1.h"

int SvProcessorV1::getPixelColor(int cursor) {
	if (cursor == 0) {
		return 0;
	}

	return ((10 * m_left->getWidth()) / (2.0 * 0.9 * cursor ));
}
/*
int SvProcessorV1::match(int x, int y, int j) {
	int error = 0;

	for (int i = 0; i <= 1; i++) {
		for (int g = 0; g <= 2; g++) {
			error += diff(x + i, y + g, x + i + j, y + g);
		}
	}

	return error;
}*/

int SvProcessorV1::diff(int lx, int ly, int rx, int ry) {
	int Rvalue, Gvalue, Bvalue, color;

	Rvalue = abs(m_left->getPixel(lx, ly, 0) - m_right->getPixel(rx, ry, 0));
	Gvalue = abs(m_left->getPixel(lx, ly, 1) - m_right->getPixel(rx, ry, 1));
	Bvalue = abs(m_left->getPixel(lx, ly, 2) - m_right->getPixel(rx, ry, 2));
	color  = abs(Gvalue - Rvalue) + abs(Bvalue - Gvalue);

	return (Gvalue + Rvalue + Bvalue) +
			color * 4;
}

int SvProcessorV1::match(int x, int y, int j) {
	int error = 0;
	int ms = 4;
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
	//error += l + r + b + t;

	return error;
}

void SvProcessorV1::exec() {
	int x, y, cursor, closest, tmp;
	int minErrorValue, tmpSmoothed, matched;
	int precursor, preprecursor;
	int dist, diff, val, prev, preprev;

	cursor       = 0;
	precursor    = 0;
	preprecursor = 0;

	for (x = 0; x < m_stereo->getWidth(); x++) {
		closest = -1; minErrorValue = -1;matched=0;
		minErrorValue=-1;

		val = m_left->getPixelHue(x, m_line);

		for (int i = 1; i < windowSize; i++) {
			dist = (abs(cursor - i));

			tmp = match(x, m_line, i);

			tmpSmoothed  = tmp;// + (dist) * (1.0/diff);

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

		m_stereo->putPixel(x, m_line, getPixelColor(cursor));

		preprecursor = precursor;
		precursor = cursor;

		preprev = prev;
		prev    = val;
	}
}

