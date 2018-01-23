
#include "systime.h"
#include<QtGui>
#include <QtCore/QTextCodec>

myTime::myTime(QWidget *parent)
    : QWidget(parent)
{
    init();
}
myTime::~myTime()
{

}
void myTime::init()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    datetime=new QDateTime;
    timer=new QTimer;
    lcdNumber=new QLCDNumber;
    label=new QLabel;
    label->setMinimumSize(145,20);
    label->setAlignment(Qt::AlignCenter);//文字对齐方式为中间对齐
    label->setFont(QFont("times",10,QFont::Bold));
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::blue);//字体颜色
    label->setPalette(pa);
    label->setAutoFillBackground(this);
    label->setStyleSheet("background-color:rgba(0,0,0,0)");//设置标签背景透明
    label->setText(QDateTime::currentDateTime().toString("yyyy-dd-MM hh:mm:ss"));
    QVBoxLayout * layout=new QVBoxLayout;
    layout->addWidget(label);
    this->setLayout(layout);


    connect(timer,SIGNAL(timeout()),this,SLOT(chTime()));
    timer->start(1000);
}
void myTime::chTime()
{
    label->setText(QDateTime::currentDateTime().toString("yyyy-dd-MM hh:mm:ss"));
}
