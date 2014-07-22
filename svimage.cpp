#include "svimage.h"

int SvImage::getPixel(int x, int y, int channel) {
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    QRgb rgb = m_image->pixel(x, y);

    switch (channel) {
    case 0:
        return qRed(rgb);
    case 1:
        return qGreen(rgb);
    case 2:
        return qBlue(rgb);
    default:
        return qGray(rgb);
    }
}

int SvImage::getPixelNormalizedHue(int x, int y) {
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    QRgb rgb = m_image->pixel(x, y);
    QColor color(rgb);

    return (color.hsvHue() * getPixelSaturation(x, y)) / 255;
}

int SvImage::getPixelHue(int x, int y) {
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    QRgb rgb = m_image->pixel(x, y);
    QColor color(rgb);

    return color.hsvHue();
}

int SvImage::getPixelValue(int x, int y) {
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    QRgb rgb = m_image->pixel(x, y);
    QColor color(rgb);

    return color.value();
}

int SvImage::getPixelSaturation(int x, int y)
{
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    QRgb rgb = m_image->pixel(x, y);
    QColor color(rgb);

    return color.saturation();
}

QRgb SvImage::getPixelRGB(int x, int y)
{
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return 0;
    }

    return m_image->pixel(x, y);
}

void SvImage::putGrayPixel(int x, int y, int value)
{
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return;
    }

    if (value > 255) {
        value = 255;
    }

    m_image->setPixel(x, y, qRgb(value, value, value));
}

void SvImage::putPixel(int x, int y, int red, int green, int blue)
{
    if (y >= m_image->height() ||
        y < 0 ||
        x >= m_image->width()
        || x < 0) {

        return;
    }

    m_image->setPixel(x, y, qRgb(red, green, blue));
}

unsigned int SvImage::getHeight() {
    return m_image->height();
}

unsigned int SvImage::getWidth() {
    return m_image->width();
}

QImage& SvImage::getImage() {
    return *m_image;
}

SvImage::SvImage(QImage& image) {
    m_image = &image;
}

SvImage::~SvImage() {

}
