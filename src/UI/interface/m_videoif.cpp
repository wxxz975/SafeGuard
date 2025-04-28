#include "m_videoif.h"
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QDebug>

M_VideoIF::M_VideoIF(QObject *parent)
    : QObject{parent}
{
    // 临时
    count = 0;
    tf = startTimer(1000/60.0);
}

M_VideoIF::~M_VideoIF()
{
    // 临时
    killTimer(tf);
}


void M_VideoIF::ScreenSizeChange(int w, int h)
{
    width = w;
    height = h;
}

void M_VideoIF::run()
{
    // 测试
    cv::Mat *a = new cv::Mat();
    *a = cv::Mat::zeros(1080, 1920, CV_8UC3);
    cv::Scalar color(255, 255, 255);
    cv::putText(*a, QString("Frame:%0").arg(count).toUtf8().data(), cv::Point(100, 500), cv::FONT_HERSHEY_SIMPLEX, 4, color, 5);
    cv::putText(*a, QString("Screen:%0X%1").arg(width).arg(height).toUtf8().data(), cv::Point(100, 700), cv::FONT_HERSHEY_SIMPLEX, 4, color, 5);
    cv::rectangle(*a, cv::Point(10, 10), cv::Point(1900, 1060), color, 4);
    setMat(a);
    if(count%10==0){
        setMat(a,MatType::MT::ScreenShot);
    }
    count++;
    delete a;
}

void M_VideoIF::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==tf){
        run();
    }
}
