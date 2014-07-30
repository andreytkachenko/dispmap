#include "svkernel.h"

SvKernel::SvKernel()
{

}

SvKernel::~SvKernel()
{

}

int SvKernel::rgbDiff(QRgb left, QRgb right)
{
    QColor cLeft(left);
    QColor cRight(right);

    int leftDiff = max(qBlue(left), qRed(left), qGreen(left)) -
                   min(qBlue(left), qRed(left), qGreen(left));

    int rightDiff = max(qBlue(right), qRed(right), qGreen(right)) -
                    min(qBlue(right), qRed(right), qGreen(right));

    int minDiff= leftDiff < rightDiff ? rightDiff : leftDiff;

    int diff = qGray(left) - qGray(right);
    int hsvDiff = minDiff > 70 ? abs(cLeft.hsvHue() - cRight.hsvHue()) : 0;
    if (hsvDiff > 180) {
        hsvDiff = 360 - hsvDiff;
    }

    int dsign = sign(diff);
    dsign = dsign == 0 ? 1 : dsign;

    return /*dsign * (abs(rightDiff - leftDiff)>>2) + */diff /*+ (hsvDiff > 5 ? dsign * 10 : 0)*/;
}

void SvKernel::exec(SvPointCloud *pc, SvImage *image, int line)
{
    SvPoint p;
    QRgb vtop, top, right, bottom, vbottom, center;
    QRgb rTop, lTop;

    int __dX, _dX, dX, dX_,
        __dY, _dY, dY, dY_;

    int hDiff, vDiff;

    for (int x = 0; x < image->getWidth(); x++) {
        hDiff = 0; vDiff = 0;

        top     = image->getPixelRGB(x - 1, line - 2);
        right   = image->getPixelRGB(x,     line - 1);
        bottom  = image->getPixelRGB(x - 1, line);
        vtop    = image->getPixelRGB(x - 1, line - 3);

        dX_  = rgbDiff(center, right);
        dY_  = rgbDiff(vtop, top);
        dY   = rgbDiff(top, center);
        _dY  = rgbDiff(center, bottom);

        if ( dX >= _dX && dX > dX_ ||
             dX <= _dX && dX < dX_) {
            if (dX == _dX) {
                if (dX > dX_ && _dX > __dX ||
                    dX < dX_ && _dX < __dX) {

                    hDiff = abs(dX);
                }
            } else {
                hDiff = abs(dX);
            }
        }

        if ( dY >= _dY && dY > dY_ ||
             dY <= _dY && dY < dY_) {

            if (dY == _dY) {
                vbottom = image->getPixelRGB(x - 1, line + 1);
                __dY = rgbDiff(bottom, vbottom);

                if (dY > dY_ && _dY > __dY ||
                    dY < dY_ && _dY < __dY) {

                    vDiff = abs(dY);
                }
            } else {
                vDiff = abs(dY);
            }
        }

        if (hDiff > 0 || vDiff > 0) {
            if (x > 1 && line > 1){
                lTop  = image->getPixelRGB(x - 2, line - 2);
                rTop  = image->getPixelRGB(x,     line - 2);

                p.setX(x - 1);
                p.setY(line - 1);

                p.setDiff(hDiff, rgbDiff(center, lTop), vDiff, rgbDiff(center, rTop));

                pc->addPoint(p);
            }
        }

        __dX = _dX;
        _dX = dX;
         dX = dX_;
        center = right;
    }
}

