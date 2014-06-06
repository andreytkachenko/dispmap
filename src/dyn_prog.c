/*int dispForPixel(Mat &left, Mat &right, int x, int y, int cursor)
{
	int leftValue = getPixelValue(left, x, y);
	int rightValue, diff, minimum = 2555;
	int result = cursor, b, c, d, m,g = 0,h;

	for (int i = 0; i < WINDOW_SIZE; i++) {
		rightValue = getPixelValue(right, x + i, y);
		diff = abs(leftValue - rightValue);
		if (diff < minimum) {
			minimum = diff;
			h = i;
			g = 0;
		}

		if (diff == minimum) {
			g++;
     	}
	}

	minimum = abs(leftValue - getPixelValue(right, x + cursor, y));
    if (g == 1) {
    	result = h;
    } else if (x == 0) {
		for (int i = 0; i < WINDOW_SIZE; i++) {
			rightValue = getPixelValue(right, x + i, y);
			diff = abs(leftValue - rightValue);
			if (diff < minimum) {
				minimum = diff;
				result = i;
			}
		}
	} else {
		for (int i = 0; i < 255; i++) {
			b = abs(getPixelValue(left, x + 1, y) - getPixelValue(right, x + cursor, y));
			c = abs(getPixelValue(left, x, y) - getPixelValue(right, x + cursor + 1, y));
			d = abs(getPixelValue(left, x + 1, y) - getPixelValue(right, x + cursor + 1, y));

			m = d;
			if (b < m) {
				m = b;
			}
			if (c < m) {
				m = c;
			}

			if (m == d) {
				result = cursor;
				break;
			} else if (m == b) {
				cursor--;
			} else if (m == c) {
				cursor++;
			}
		}
	}

	return result;
}*/

/*
int rdispForPixel(Mat &left, Mat &right, int x, int y, int cursor)
{
	int leftValue = getPixelValue(left, x, y);
	int rightValue, diff, minimum = abs(leftValue - getPixelValue(right, x - cursor, y));
	int result = cursor, b, c, d, m;

	if (x == 0) {
		for (int i = 0; i < WINDOW_SIZE; i++) {
			rightValue = getPixelValue(right, x + i, y);
			diff = abs(leftValue - rightValue);
			if (diff < minimum) {
				minimum = diff;
				result = i;
			}
		}
	} else {
		for (int i = 0; i < 255; i++) {
			b = abs(getPixelValue(left, x - 1, y) - getPixelValue(right, x - cursor, y));
			c = abs(getPixelValue(left, x, y) - getPixelValue(right, x - cursor - 1, y));
			d = abs(getPixelValue(left, x - 1, y) - getPixelValue(right, x - cursor - 1, y));

			m = d;
			if (b < m) {
				m = b;
			}
			if (c < m) {
				m = c;
			}

			if (m == d) {
				result = cursor;
				break;
			} else if (m == b) {
				cursor--;
			} else if (m == c) {
				cursor++;
			}
		}
	}

	return result;
}


void calcDepthMapDynProgr(StereoData &params, Mat &stereo, Mat &left, Mat &right) {
	int x, y, cursor;
	uchar* data;

	for (y = 0; y < stereo.rows; y++) {
		cursor = 0;
		for (x = 0; x < stereo.cols; x++) {
			//cursor = rdispForPixel(left, right, stereo.cols - x, y, cursor);
			cursor = dispForPixel(left, right, x, y, cursor);
			data = stereo.ptr(y, x);
			data[0] = cursor;
		}
	}
}
*/
