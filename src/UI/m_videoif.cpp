#include "m_videoif.h"
#include <opencv2/opencv.hpp>

#include <QDebug>

M_VideoIF::M_VideoIF(QObject *parent)
    : QObject{parent}
{
    count = 0;
}

void M_VideoIF::readyRead()
{
    // 测试用
    cv::Mat *a = new cv::Mat();
    *a = cv::Mat::zeros(1024, 1024, CV_8UC3);
    cv::Scalar color(255, 255, 255);
    cv::putText(*a, QString("Frame:%0").arg(count).toUtf8().data(), cv::Point(100, 500), cv::FONT_HERSHEY_SIMPLEX, 4, color, 5);
    cv::rectangle(*a, cv::Point(10, 10), cv::Point(1008, 1008), color, 4);
    count++;
    setMat(a);
}

void M_VideoIF::readCompleted(cv::Mat *used)
{
    delete used;
}

//void M_VideoIF::windowChange(int width, int height)
//{

//}

void M_VideoIF::configChange(int id, int value)
{

}
