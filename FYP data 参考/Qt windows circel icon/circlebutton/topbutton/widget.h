#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QLabel *labellog;//登录
    QLabel *labellogm;//数字
     QLabel *labellogmoney;//收银员
     QButtonGroup *m_pushButtonGroup;
private slots:
    void buttonslot(int num=0);



};

#endif // WIDGET_H
