#include "svkernelv2.h"

SvKernelV2::SvKernelV2()
{

}

SvKernelV2::~SvKernelV2()
{

}

int SvKernelV2::rgbDiff(QRgb left, QRgb right)
{
    QColor cLeft(left);
    QColor cRight(right);

    int leftDiff = max(qBlue(left), qRed(left), qGreen(left)) -
                   min(qBlue(left), qRed(left), qGreen(left));

    int rightDiff = max(qBlue(right), qRed(right), qGreen(right)) -
                    min(qBlue(right), qRed(right), qGreen(right));

    int minDiff= leftDiff < rightDiff ? rightDiff : leftDiff;

    int diff = cLeft.value() - cRight.value();
    int hsvDiff = minDiff > 70 ? abs(cLeft.hsvHue() - cRight.hsvHue()) : 0;
    if (hsvDiff > 180) {
        hsvDiff = 360 - hsvDiff;
    }

    int dsign = sign(diff);
    dsign = dsign == 0 ? 1 : dsign;

    return /*dsign * ((rightDiff - leftDiff)>>2) + */diff /*+ (hsvDiff > 5 ? dsign * 10 : 0)*/;
}

void SvKernelV2::exec(int line)
{
    QRgb vtop, top, right, bottom, vbottom, _xy, xy;

    int __dX, _dX, dX, dX_,
        __dY, _dY, dY, dY_;

    int value;

    for (int x = 0; x < m_result->getWidth(); x++) {
        value = 0;

        vtop    = m_left->getPixelRGB(x - 1, line - 3);
        top     = m_left->getPixelRGB(x - 1, line - 2);
        right   = m_left->getPixelRGB(x,     line - 1);
        bottom  = m_left->getPixelRGB(x - 1, line);
        vbottom = m_left->getPixelRGB(x - 1, line + 1);
        xy      = m_left->getPixelRGB(x - 1, line - 1);

        dX_ = rgbDiff(_xy, right);
        dY_ = rgbDiff(vtop, top);
        dY  = rgbDiff(top, _xy);
        _dY = rgbDiff(_xy, bottom);
        __dY = rgbDiff(bottom, vbottom);

        if ( dX >= _dX && dX > dX_ ||
             dX <= _dX && dX < dX_) {
            if (dX == _dX) {
                if (dX > dX_ && _dX > __dX ||
                    dX < dX_ && _dX < __dX) {
                    value += abs(dX);
                }
            } else {
                value += abs(dX);
            }
        }

        if ( dY >= _dY && dY > dY_ ||
             dY <= _dY && dY < dY_) {

            if (dY == _dY) {
                if (dY > dY_ && _dY > __dY ||
                    dY < dY_ && _dY < __dY) {

                    value += abs(dY);
                }
            } else {
                value += abs(dY);
            }
        }

        if (value > 0) {
            m_result->putGrayPixel(x - 1, line - 1, value);
        }

        __dX = _dX;
        _dX = dX;
         dX = dX_;
        _xy = right;
    }
}

