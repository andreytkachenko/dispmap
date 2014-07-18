#include "svkernelv2.h"

SvKernelV2::SvKernelV2()
{

}

SvKernelV2::~SvKernelV2()
{

}

void SvKernelV2::exec(int line)
{
    int hue, value, saturation;
    int _hue, _value, _saturation;
    int __hue, __value, __saturation;
    int dValue, dHue, dSaturation;
    int tValue, tHue, tSaturation;
    int _dValue, __dValue;
    int _dSaturation, __dSaturation;
    int _dHue, __dHue;

    for (int x = 0; x < m_result->getWidth(); x++) {
        hue = m_left->getPixelHue(x, line);
        value = m_left->getPixelValue(x, line);
        saturation = m_left->getPixelSaturation(x, line);

        dHue = _hue - hue;
        dSaturation = _saturation - saturation;
        dValue = _value - value;

        int m1 = m_left->getPixelValue(x, line - 1);
        int m2 = m_left->getPixelValue(x, line - 2);
        int m3 = m_left->getPixelValue(x, line - 3);

        int dY = m1-value;
        int _dY = m2-m1;
        int __dY = m3-m2;

        int hV = 0;

        if (((_dValue > dValue && _dValue > __dValue) ||
             (_dValue < dValue && _dValue < __dValue))) {

            hV = abs(_dValue);
            m_result->putGrayPixel(x, line, abs(_dValue));
        }

        if (((_dY > dY && _dY > __dY) ||
             (_dY < dY && _dY < __dY))) {
            if (abs(_dY) > hV) {
                m_result->putGrayPixel(x, line - 2, abs(_dY));
            }
        }

        __hue = _hue;
        __value = _value;
        __saturation = _saturation;

        _hue = hue;
        _value = value;
        _saturation = saturation;

        __dValue = _dValue;
        _dValue = dValue;

        __dSaturation = _dSaturation;
        _dSaturation = dSaturation;

        __dHue = _dHue;
        _dHue = dHue;
    }
}

int SvKernelV2::getPixelValueByBit(int bit)
{

}

unsigned int SvKernelV2::figureType(int x, int y, int level)
{
    unsigned char typeCode, resultType;
    int result, error = -1;
    for (int type = 1; type < 20; type++) {
        typeCode = m_figures[type - 1];
        result = 0;
        for (int bit = 0; bit < 9; bit++) {
            value = getPixelValueByBit(bit);
            if (typeCode & (1 << bit)) {
                result += abs(level - value);
            } else {
                result += value;
            }
        }

        if (error > result || error == -1) {
            resultType = type;
            error = result;
        }
    }

    return (error << 5) | resultType;
}
