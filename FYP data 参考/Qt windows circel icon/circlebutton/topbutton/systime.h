#ifndef MYTIME_H
#define MYTIME_H
#include <QtGui/QWidget>
class QVBobLayout;
class QHBocLayout;
class QPushButton;
class QLabel;
class QLCDNumber;
class QDateTime;
class QTimer;

class myTime : public QWidget
{
    Q_OBJECT
signals:
    void currentTime();
public:
    myTime(QWidget *parent = 0);
    ~myTime();
    QDateTime* datetime;
    QTimer* timer;
    QLCDNumber* lcdNumber;
    QLabel* label;
    QPushButton* button;
    QPushButton* ebutton;
private slots:
    void chTime();
private:
    void init();
};
#endif // MYTIME_H
