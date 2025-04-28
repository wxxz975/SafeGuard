#include "m_videocore.h"

#include <QWidget>
#include <QThread>
#include <QTimer>

#include "opencv2/opencv.hpp"

#include <QDebug>

M_VideoCore::M_VideoCore(QObject *parent)
    : M_VideoIF{parent}
{
    // 核心线程
    _core_thread = new QThread();
    moveToThread(_core_thread);
    _core_thread->start();
}

void M_VideoCore::GetScreenSizeChange(int width, int height)
{
    _ScreenWidth = width;
    _ScreenHeight = height;
}

void M_VideoCore::setMat(cv::Mat *mat, MatType::MT Type)
{
    if(mat == nullptr)return;
    if(mat->empty())return;
    if(Type==MatType::MT::VideoStream){
        emit readReady(Type,QImage(mat->data, mat->cols, mat->rows,mat->step, QImage::Format_BGR888).copy().scaled(QSize(_ScreenWidth,_ScreenHeight),Qt::KeepAspectRatio));
    }else{
        emit readReady(Type,QImage(mat->data, mat->cols, mat->rows,mat->step, QImage::Format_BGR888).copy().scaled(QSize(ScreenShotMaxWidth,ScreenShotMaxHeight),Qt::KeepAspectRatio));
    }
}
