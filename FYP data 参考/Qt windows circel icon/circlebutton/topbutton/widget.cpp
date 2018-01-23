#include "widget.h"
#include "ui_widget.h"
#include "roundbutton.h"
#include "systime.h"
#include <QLabel>
#include <QButtonGroup>
Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pushButtonGroup = new QButtonGroup(this);
    AeroButton * topbutton0 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/00.png"),"/home/wenchao/topbutton/zgfimg/000.png", this);
    topbutton0->setIconSize(QSize(55, 50));
    m_pushButtonGroup->addButton(topbutton0,0);
    topbutton0->setMaximumSize(55,50);
    AeroButton * topbutton1 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/111.png"),"/home/wenchao/topbutton/zgfimg/1111.png", this);
    topbutton1->setIconSize(QSize(50, 50));
    topbutton1->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton1,1);
    AeroButton * topbutton2 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/22.png"),"/home/wenchao/topbutton/zgfimg/222.png", this);
    topbutton2->setIconSize(QSize(50, 50));
    topbutton2->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton2,2);
    AeroButton * topbutton3 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/33.png"),"/home/wenchao/topbutton/zgfimg/333.png", this);
    topbutton3->setIconSize(QSize(50, 50));
    topbutton3->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton3,3);
    AeroButton * topbutton4 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/44.png"),"/home/wenchao/topbutton/zgfimg/444.png", this);
    topbutton4->setIconSize(QSize(50, 50));
    topbutton4->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton4,4);
    AeroButton * topbutton5 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/55.png"),"/home/wenchao/topbutton/zgfimg/555.png", this);
    topbutton5->setIconSize(QSize(50, 50));
    topbutton5->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton5,5);
    AeroButton * topbutton6 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/66.png"),"/home/wenchao/topbutton/zgfimg/666.png", this);
    topbutton6->setIconSize(QSize(50, 50));
    topbutton6->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton6,6);
    AeroButton * topbutton7 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/77.png"),"/home/wenchao/topbutton/zgfimg/777.png", this);
    topbutton7->setIconSize(QSize(50, 50));
    topbutton7->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton7,7);
    AeroButton * topbutton8 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/88.png"),"/home/wenchao/topbutton/zgfimg/888.png", this);
    topbutton8->setIconSize(QSize(50, 50));
    topbutton8->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton8,8);
    AeroButton * topbutton9 = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/99.png"),"/home/wenchao/topbutton/zgfimg/999.png", this);
    topbutton9->setIconSize(QSize(50, 50));
    topbutton9->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbutton9,9);
    AeroButton * topbuttonx = new AeroButton(QIcon("/home/wenchao/topbutton/zgfimg/xx.png"),"/home/wenchao/topbutton/zgfimg/xxx.png", this);
    topbuttonx->setIconSize(QSize(50, 50));
    topbuttonx->setMaximumSize(50,50);
    m_pushButtonGroup->addButton(topbuttonx,10);
    myTime *timey = new myTime;//create  time
    labellog = new QLabel;
    labellogm = new QLabel;
    labellogmoney = new QLabel;
    labellog->setAlignment(Qt::AlignCenter);//文字对齐方式为中间对齐
    labellogm->setAlignment(Qt::AlignCenter);
    labellogmoney->setAlignment(Qt::AlignCenter);
    labellogmoney->setMaximumSize(80,20);
    labellogm->setMaximumSize(60,15);
    labellog->setMaximumSize(60,15);
    QGridLayout *lablemag = new QGridLayout;

    labellogmoney->setText(QObject::tr("人数:"));


    labellog->setText(QObject::tr("    已登录"));


    lablemag->addWidget(timey,0,1);
    lablemag->addWidget(labellogm,0,0);

    lablemag->addWidget(labellogmoney,1,0);
    lablemag->addWidget(labellog,1,1);


    QObject::QObject::connect(m_pushButtonGroup, SIGNAL(buttonClicked(int)),this, SLOT(buttonslot(int)));//
    QHBoxLayout *numbuttonlayout = new QHBoxLayout;

    numbuttonlayout->addStretch();
    numbuttonlayout->addWidget(topbutton0);
    numbuttonlayout->addWidget(topbutton1);
    numbuttonlayout->addWidget(topbutton2);
    numbuttonlayout->addWidget(topbutton3);
    numbuttonlayout->addWidget(topbutton4);
    numbuttonlayout->addWidget(topbutton5);
    numbuttonlayout->addWidget(topbutton6);
    numbuttonlayout->addWidget(topbutton7);
    numbuttonlayout->addWidget(topbutton8);
    numbuttonlayout->addWidget(topbutton9);
    numbuttonlayout->addWidget(topbuttonx);
    numbuttonlayout->addStretch();

    numbuttonlayout->addLayout(lablemag);

    this->setLayout(numbuttonlayout);


}
int a,i=1;
void Widget::buttonslot(int num)
{


if(i==1)
    {
     a=a+num*100;

}
else if(i==2)
{
    a=a+num*10;
}
else if(i==3)
{
 a=a+num;
}
i++;
    labellogm->setText(QString::number(a,'g',3));
    if(num==10)
    {
     labellogm->clear();
     i=1;
     a=0;
 }
}

Widget::~Widget()
{
    delete ui;
}
