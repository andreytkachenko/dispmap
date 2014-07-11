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
    int  getPixel(int x, int y, int channel);
    int  getPixelHue(int x, int y);
    int  getPixelValue(int x, int y);
    void putPixel(int x, int y, int val);

    unsigned int getHeight();
    unsigned int getWidth();

    QImage& getImage();

    SvImage(QImage& image);
    virtual ~SvImage();
};

#endif // SVIMAGE_H
