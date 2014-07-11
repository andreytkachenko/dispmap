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
    SvImageProvider* imageProvider = new SvImageProvider();

    QImage imgLeft  = QPixmap("img/left8.png").toImage();
    QImage imgRight = QPixmap("img/right8.png").toImage();
    QImage imgStereo(imgLeft.width(), imgRight.height(), QImage::Format_RGB32);

    SvImage left(imgLeft);
    SvImage right(imgRight);
    SvImage stereo(imgStereo);



    imageProvider->addImage("left", &left);
    imageProvider->addImage("right", &right);
    imageProvider->addImage("result", &stereo);

    engine.addImageProvider("image", imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:///Main.qml")));

    /*SvProcessor proc(&left, &right, &stereo, 4);
    proc.start();*/


   //

    //QObject *object = component.create();


    return a.exec();
}
