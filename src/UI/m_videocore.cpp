#include "m_videocore.h"

#include <QWidget>
#include <QThread>
#include <QEvent>
#include <QTimer>

#include "opencv2/opencv.hpp"

#include <QDebug>

M_VideoCore::M_VideoCore(QObject *parent)
    : M_VideoIF{parent}
{
    // 数值初始化
    _cur_fps = MINFPS;
    _frame_delay = 1000.0/_cur_fps;
    _run_flage = 0;
    // 核心线程
    // 界面线程未分离完全，开新线程会出现异常
    // 已找到方法 待处理
//    _core_thread = new QThread();
//    moveToThread(_core_thread);
//    _core_thread->start();

    // 延迟触发计时器 待优化
    QMetaObject::invokeMethod(this,[&](){
        _frame_timer = new QTimer();
        connect(_frame_timer,SIGNAL(timeout()),this,SLOT(run()));
        _frame_timer->start(_frame_delay);
    },Qt::QueuedConnection);
}

bool M_VideoCore::start()
{
    return false;
}

void M_VideoCore::stop()
{

}

bool M_VideoCore::setMat(cv::Mat *mat)
{
    if(mat == nullptr)return false;
    if(mat->empty())return false;
    _mat_buffer = mat;
    _img_buffer = QImage(_mat_buffer->data, _mat_buffer->cols, _mat_buffer->rows,_mat_buffer->step, QImage::Format_BGR888);
    emit readReady(_img_buffer);
    return true;
}

void M_VideoCore::run()
{
    _start = _ela.elapsed();
    if(_mat_buffer!=nullptr){
        readCompleted(_mat_buffer);
        _mat_buffer = nullptr;
    }
    readyRead();
    _end = _ela.elapsed() - _start;
    if(_end > _frame_delay){
        _cur_fps = qMax(MINFPS,_cur_fps-1);
    }else if(_end < _frame_delay){
        if(MAXFPS <= _cur_fps){
            return;
        }
        _cur_fps = qMin(MAXFPS,_cur_fps+1);
    }
    _frame_delay = 1000.0/_cur_fps;
    _frame_timer->setInterval(_frame_delay);
}

int M_VideoCore::fps()
{
    return _cur_fps;
}
