
#include "roundbutton.h"
#include<QIcon>
AeroButton::AeroButton(QWidget * parent)
    : QPushButton(parent),
    m_hovered(false),
    m_pressed(false),
    m_color(Qt::gray),
    m_highlight(Qt::lightGray),
    m_shadow(Qt::black),
    m_opacity(1.0),
    m_roundness(0){}

AeroButton::AeroButton(const QString & text, QWidget * parent)
    : QPushButton(text, parent),
    m_hovered(false),
    m_pressed(false),
    m_color(Qt::gray),
    m_highlight(Qt::lightGray),
    m_shadow(Qt::black),
    m_opacity(1.0),
    m_roundness(0){}

AeroButton::AeroButton(const QIcon & icon,const QString & text, QWidget * parent)
    : QPushButton(icon,text,parent),
    m_hovered(false),
    m_pressed(false),
    m_color(Qt::gray),
    m_highlight(Qt::lightGray),//强光(效果)
    m_shadow(Qt::black),
    m_opacity(1.0),// 不透明
    m_roundness(0){}// 圆，圆度

AeroButton::~AeroButton(){}

void AeroButton::paintEvent(QPaintEvent * pe)
        //void AeroButton::drawButton(QPainter* pe)
{
    Q_UNUSED(pe);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿处理
    //test for state changes
    QColor button_color;
    if(this->isEnabled())
    {
        m_hovered ? button_color = m_highlight : button_color = m_color;

        if(m_pressed)
        {
            button_color = m_highlight.darker(250);
        }
    }
    else
    {
        button_color = QColor(50, 50, 50);
    }

    //QRect button_rect = QRect(1, 1, 40, 40);
    QRect button_rect =this->geometry();
    //outline
    painter.setPen(QPen(QBrush(Qt::red), 2.0));
    //main button
    QPainterPath painter_path;

    //painter_path.addRoundRect(1, 1, button_rect.width() - 2, button_rect.height() - 2, m_roundness, m_roundness);
    painter_path.addEllipse(0,0,button_rect.width()-2,button_rect.width()-2);
    painter.setClipPath(painter_path);


    //icon
    QString text = this->text();
    QIcon icon = this->icon();

    if(m_pressed == false && !icon.isNull())
    {

        QSize icon_size = this->iconSize();
        QRect icon_position = this->calculateIconPosition(button_rect,icon_size);
        painter.setOpacity(1.0);

        painter.drawPixmap(icon_position, QPixmap(icon.pixmap(icon_size)));
    }
    else
    {
       QSize icon_size1 = this->iconSize();
        QRect icon_position = this->calculateIconPosition(button_rect,icon_size1);
        painter.setOpacity(1.0);
        QPixmap img(text);//图像
      painter.drawPixmap(icon_position,img);

    }
}

void AeroButton::enterEvent(QEvent * e)
{
    m_hovered = true;

    this->repaint();

    QPushButton::enterEvent(e);
}

void AeroButton::leaveEvent(QEvent * e)
{
    m_hovered = false;
    this->repaint();

    QPushButton::leaveEvent(e);
}

void AeroButton::mousePressEvent(QMouseEvent * e)
{
    m_pressed = true;
    this->repaint();

    QPushButton::mousePressEvent(e);
}

void AeroButton::mouseReleaseEvent(QMouseEvent * e)
{
    m_pressed = false;
    this->repaint();

    QPushButton::mouseReleaseEvent(e);
}

QRect AeroButton::calculateIconPosition(QRect button_rect, QSize icon_size)
{
    int x = (button_rect.width() / 2) - (icon_size.width() / 2);
    int y = (button_rect.height() / 2) - (icon_size.height() / 2);

    int width = icon_size.width();
    int height = icon_size.height();


    QRect icon_position;
    icon_position.setX(x);
    icon_position.setY(y);
    icon_position.setWidth(width);
    icon_position.setHeight(height);

    return icon_position;
}
