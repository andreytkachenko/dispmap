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
    int hsvDiff = abs(cLeft.hsvHue() - cRight.hsvHue());
    if (hsvDiff > 180) {
        hsvDiff = 360 - hsvDiff;
    }

    return (rightDiff - leftDiff) + diff;  /*diff + (minDiff > 20 ? sign(diff) * hsvDiff : 0)*/;
}

void SvKernelV2::exec(int line)
{
    QRgb vtop, top, right, bottom, _xy, xy;

    int dX, _dX, dX_,
        dY, _dY, dY_;

    int value;

    for (int x = 0; x < m_result->getWidth(); x++) {
        value = 0;

        vtop   = m_left->getPixelRGB(x - 1, line - 3);
        top    = m_left->getPixelRGB(x - 1, line - 2);
        right  = m_left->getPixelRGB(x,     line - 1);
        bottom = m_left->getPixelRGB(x - 1, line);
        xy     = m_left->getPixelRGB(x - 1, line - 1);

        dX_ = rgbDiff(_xy, right);
        dY_ = rgbDiff(vtop, top);
        dY  = rgbDiff(top, _xy);
        _dY = rgbDiff(_xy, bottom);


        if ( dX > _dX && dX > dX_ ||
             dX < _dX && dX < dX_) {

            value += abs(dX);
        }

        if ( dY > _dY && dY > dY_ ||
             dY < _dY && dY < dY_) {

            value += abs(dY);
        }

        if (value > 0) {
            m_result->putGrayPixel(x - 1, line - 1, value);
        }

        _dX = dX;
         dX = dX_;
        _xy = right;
    }
}

