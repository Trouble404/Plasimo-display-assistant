#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    tempConverter(new TempConverter(0))
{
    ui->setupUi(this);
    connect(ui->centDial, SIGNAL(valueChanged(int)), this->tempConverter, SLOT(setTempCelsius(int)));
    connect(ui->fahDial, SIGNAL(valueChanged(int)), this->tempConverter, SLOT(setTempFahrenheit(int)));
    connect(this->tempConverter, SIGNAL(tempCelsiusChanged(int)), ui->centDial, SLOT(setValue(int)));
    connect(this->tempConverter, SIGNAL(tempFahrenheitChanged(int)), ui->fahDial, SLOT(setValue(int)));
}

Widget::~Widget()
{
    delete ui;
}
