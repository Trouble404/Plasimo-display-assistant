#include <QtGui/QApplication>
#include "widget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w = new Widget;
    w->resize(1024,50);
    w->setFixedHeight(70);
    QPalette pal;

    QString filename = "/home/wenchao/zgfMenu/img/top1.png";

    QPixmap pixmap(filename);

    pal.setBrush(QPalette::Window,QBrush(pixmap));

    w->setPalette(pal);

    w->show();

    return a.exec();
}


