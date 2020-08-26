#include "mainwindow.h"
#include <QApplication>

//to prevent multiple instance
#include <QLocalSocket>
#include <QLocalServer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("KDictionary");
    QApplication::setOrganizationName("org.keshavnrj.ubuntu");
    QApplication::setApplicationVersion(VERSIONSTR);

    MainWindow w;
    const QString appKey = "kdictionary_instance_";

        QLocalSocket *socket = new QLocalSocket();
        socket->connectToServer(appKey);

        if (socket->isOpen()) {
            socket->close();
            socket->deleteLater();
            return 0;
        }
        socket->deleteLater();

        QLocalServer server;

        QObject::connect(&server,
                         &QLocalServer::newConnection,
                         [&w] () {
            /*Set the window on the top level.*/
            w.setWindowFlags(w.windowFlags() |
                             Qt::WindowStaysOnTopHint);
            w.showNormal();
            w.setWindowFlags(w.windowFlags() &
                             ~Qt::WindowStaysOnTopHint
                             );
            w.showNormal();
            w.activateWindow();
        });
        server.listen(appKey);

         w.show();

    return a.exec();
}
