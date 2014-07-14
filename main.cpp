#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>


#include <QPixmap>

#include "svimage.h"
#include "svprocessor.h"
#include "svimageprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    QQmlApplicationEngine engine;
    SvImageProvider imageProvider;

    QImage imgLeft("../ComputerVision/img/left8.png");
    QImage imgRight("../ComputerVision/img/right8.png");
    QImage imgStereo(imgLeft.width(), imgRight.height(), QImage::Format_RGB32);

    SvImage left(imgLeft);
    SvImage right(imgRight);
    SvImage stereo(imgStereo);

    imageProvider.addImage("left", &left);
    imageProvider.addImage("right", &right);
    imageProvider.addImage("result", &stereo);

    engine.addImageProvider("images", &imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:///Main.qml")));

    SvProcessor proc(&left, &right, &stereo, 1);
    proc.start();

    return a.exec();
}
