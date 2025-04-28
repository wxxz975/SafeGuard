#include "m_sceenshotwidget.h"

#include <QImage>
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include <QThread>

M_SceenShotWidget::M_SceenShotWidget(int index, QWidget *parent)
    : QWidget{parent}
{
    _index = index;
    installEventFilter(this);
}

bool M_SceenShotWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint){
        QPainter pa(this);
        if(_list!=nullptr&&_list->count()>_index){
            setMinimumWidth(_list->at(_index).width());
            pa.drawImage(0,0,_list->at(_index));
        }
    }
    return QWidget::eventFilter(watched,event);
}

void M_SceenShotWidget::SetList(QVector<QImage>* V)
{
    _list = V;
}

void M_SceenShotWidget::SetNext(M_SceenShotWidget *f)
{
    _next = f;
}

void M_SceenShotWidget::Update()
{
    update();
    // 传递触发
    if(_next!=nullptr)_next->Update();
}
