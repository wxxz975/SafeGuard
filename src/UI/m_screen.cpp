#include "m_screen.h"

#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QPaintEvent>

M_Screen::M_Screen(QWidget *parent)
    : QWidget{parent}
{
    installEventFilter(this);
    painterflage = true;
}

void M_Screen::readimg(QImage img)
{
    // 预防多次触发造成事件队列溢出
    _painter_buffer = img;
    if(painterflage){
        painterflage = false;
        this->update();
    }
}

bool M_Screen::eventFilter(QObject *watched, QEvent *event)
{
    //绘制事件
    if(event->type()==QEvent::Paint){
        QPainter pa(this);
        pa.setRenderHint(QPainter::Antialiasing, true);
        QRect rect = this->rect();
        rect.setWidth(rect.width()-1);
        rect.setHeight(rect.height()-1);
        pa.setBrush(Qt::black);
        pa.drawRoundedRect(rect,8,8);
        // 绘制帧
        if(!_painter_buffer.isNull()){
            double x,y;
            x = (width()-_painter_buffer.width())/2.0;
            y = (height()-_painter_buffer.height())/2.0;
            pa.drawImage(x,y,_painter_buffer);
            painterflage = true;
        }
    }else if(event->type()==QEvent::Resize){
        emit ScreenChange(width(),height());
    }
    return QWidget::eventFilter(watched,event);
}
