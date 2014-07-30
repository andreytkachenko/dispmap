#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include "svimage.h"
#include "svprocessor.h"
#include "svimageprovider.h"
#include "svpointcloudviewer.h"
#include "svapplicationcontext.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    qmlRegisterType<SvPointCloudViewer>("SvPCV", 1, 0, "SvPointCloudViewer");
    qmlRegisterUncreatableType<SvPointCloud>("SvPCV", 1, 0, "SvApplicationContext", "c++ only");

    QQmlApplicationEngine engine;
    SvImageProvider imageProvider;

    QImage imgLeft("../CSV/img/left3.png");
    //QImage imgLeft("../CSV/img/right1.png");
    QImage imgRight("../CSV/img/right1.png");

    SvImage left(imgLeft);
    SvImage right(imgRight);

    SvPointCloud pointCloud(imgLeft.width(), imgLeft.height());
    SvApplicationContext applicationContext;

    applicationContext.setPointCloud(&pointCloud);

    SvProcessor proc(4);

    proc.enqueueImage(&pointCloud, &left);

    imageProvider.addImage("left", &left);
    imageProvider.addImage("right", &right);

    engine.addImageProvider("images", &imageProvider);
    engine.rootContext()->setContextProperty("processor", &proc);
    engine.rootContext()->setContextProperty("app", &applicationContext);
    engine.load(QUrl(QStringLiteral("qrc:///Main.qml")));

    proc.start();

    return a.exec();
}
