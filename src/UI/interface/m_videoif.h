#ifndef M_VIDEOIF_H
#define M_VIDEOIF_H

#include <QObject>
#include <QTimerEvent>
#include "../M_Def.h"

namespace cv {
    class Mat;
};


class M_VideoIF : public QObject
{
    Q_OBJECT
public:
    // 视频控制接口
    // 此处进行cv视频矩阵传入
    explicit M_VideoIF(QObject *parent = nullptr);
    ~M_VideoIF();


    void startRun();

signals:
    void start_sig();

protected:
    // 函数功能: 传入图像矩阵地址
    // 参数值 矩阵地址(一帧画面)
    // 无返回值
    virtual void setMat(cv::Mat*,MatType::MT Type=MatType::MT::VideoStream) = 0;

public slots:
    // 函数功能: 画面大小已变化
    // 函数触发时 传入当前画面大小
    // 此函数无需手动触发
    void ScreenSizeChange(int,int);

protected slots:
    void run();


private:
    // 临时
    void timerEvent(QTimerEvent *event);
    int tf;
    int count;
    int width;
    int height;
};

#endif // M_VIDEOIF_H
