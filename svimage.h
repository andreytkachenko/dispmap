#ifndef SVIMAGE_H
#define SVIMAGE_H

#include <QImage>
#include <QRgb>
#include <QColor>

class SvImage
{
protected:
    QImage* m_image;

public:
    int  getPixel(int x, int y, int channel = -1);
    int  getPixelHue(int x, int y);
    int  getPixelNormalizedHue(int x, int y);
    int  getPixelValue(int x, int y);
    int  getPixelSaturation(int x, int y);
    QRgb getPixelRGB(int x, int y);
    void putGrayPixel(int x, int y, int val);
    void putPixel(int x, int y, int red, int green, int blue);

    unsigned int getHeight();
    unsigned int getWidth();

    QImage& getImage();

    SvImage(QImage& image);
    virtual ~SvImage();
};

#endif // SVIMAGE_H
