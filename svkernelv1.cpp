#include "svkernelv1.h"

SvKernelV1::SvKernelV1()
{

}

SvKernelV1::~SvKernelV1()
{

}


int SvKernelV1::getPixelColor(int cursor)
{
    if (cursor == 0) {
        return 0;
    }

    return ((10 * m_left->getWidth()) / (2.0 * 0.9 * cursor ));
}

int SvKernelV1::diff(int lx, int ly, int rx, int ry)
{
    int Red, Green, Blue, color;

    int Lvalue = m_left->getPixelValue(lx, ly);
    int Rvalue = m_right->getPixelValue(rx, ry);

    int dLvalue = m_left->getPixelValue(rx - 1, ry) - Lvalue;
    int dRvalue = m_right->getPixelValue(rx - 1, ry) - Rvalue;

    int dLsign = dLvalue >= 0 ? 1 : -1;
    int dRsign = dRvalue >= 0 ? 1 : -1;

    Red = abs(m_left->getPixel(lx, ly, 0) - m_right->getPixel(rx, ry, 0));
    Green = abs(m_left->getPixel(lx, ly, 1) - m_right->getPixel(rx, ry, 1));
    Blue = abs(m_left->getPixel(lx, ly, 2) - m_right->getPixel(rx, ry, 2));
    color  = abs(Green - Red) + abs(Blue - Green);

    return ((Green + Red + Blue) +
            color << 2) + (dLsign == dRsign ? 0 : 100);
}

int SvKernelV1::match(int x, int y, int j)
{
    int error = 0;
    int ms = 5;
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

void SvKernelV1::exec(int line)
{
    unsigned int  x;
    int cursor, closest, tmp;
    int minErrorValue, tmpSmoothed, matched;
    int dist;

    cursor       = 0;

    for (x = 0; x < m_result->getWidth(); x+=1) {
        closest = -1; minErrorValue = -1;matched=0;
        minErrorValue=-1;

        for (int i = 1; i < m_windowSize; i++) {
            dist = (abs(cursor - i));

            tmp = match(x, line, i);
            tmpSmoothed  = tmp;

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

        m_result->putGrayPixel(x/* + cursor*/, line, getPixelColor(cursor));
    }
}
