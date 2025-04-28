#ifndef M_VIDEOCORE_H
#define M_VIDEOCORE_H

#include "interface/m_videoif.h"

#include <QElapsedTimer>
#include <QImage>

class QTimer;

class M_VideoCore : public M_VideoIF
{
    Q_OBJECT
public:
    explicit M_VideoCore(QObject *parent = nullptr);

signals:
    // 发送图片信号
    void readReady(MatType::MT type,QImage img);
public slots:
    // 获取窗口大小改变数值用于缩放图片
    void GetScreenSizeChange(int,int);
private:

    // 获取矩阵地址实现
    void setMat(cv::Mat *mat,MatType::MT Type=MatType::MT::VideoStream);
    cv::Mat* _mat_buffer{nullptr};

    // 核心主线程
    QThread *_core_thread{nullptr};

    // 主屏幕大小
    double _ScreenWidth;
    double _ScreenHeight;
};

#endif // M_VIDEOCORE_H
