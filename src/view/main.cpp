#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::shared_ptr<PointCloudController> cloudsController =std::make_shared<PointCloudController>();
    std::shared_ptr<ThreadController> threadController=std::make_shared<ThreadController>();
    w.setController(cloudsController);
    w.setThreadController(threadController);
    w.show();

    //consol output (qDebug()) to text widget
    // Setup QMessageCatch
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    qInstallMessageHandler(MainWindow::QMessageOutput);
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    return a.exec();
}
