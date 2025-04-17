#include "m_screen.h"
#include <QDebug>

M_Screen::M_Screen(QWidget *parent)
    : QWidget{parent}
{
    installEventFilter(this);
}

void M_Screen::readImage(QImage img)
{
    // 接受图像并缩放至控件大小
    if(img.isNull())return;
    _buffer = img.copy().scaled(size(),Qt::KeepAspectRatio);
    this->update();
}

bool M_Screen::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint){
        //绘制事件
        QPainter pa(this);
        // 抗锯齿
        pa.setRenderHint(QPainter::Antialiasing, true);
        // 黑底
        QRect rect = this->rect();
        rect.setWidth(rect.width()-1);
        rect.setHeight(rect.height()-1);
        pa.setBrush(Qt::black);
        pa.drawRoundedRect(rect,8,8);
        // 绘制帧
        if(!_buffer.isNull()){
            double x,y;
            x = (width()-_buffer.width())/2.0;
            y = (height()-_buffer.height())/2.0;
            pa.drawImage(x,y,_buffer);
        }
    }else if(event->type()==QEvent::Resize){
        //界面缩放事件
    }
    return QWidget::eventFilter(watched,event);
}

