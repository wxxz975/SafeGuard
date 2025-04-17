#ifndef M_VIDEOCORE_H
#define M_VIDEOCORE_H

#include "m_videoif.h"

#include <QElapsedTimer>
#include <QImage>

// 运行状态
#define STOPF    0
#define RUNF     1

// 帧率配置
#define MAXFPS   60    // 最大帧率
#define MINFPS   10    // 最小帧率&初始帧率

class QTimer;

class M_VideoCore : public M_VideoIF
{
    Q_OBJECT
public:
    explicit M_VideoCore(QObject *parent = nullptr);
    // 开始
    bool start();
    //
    void stop();

signals:
    void readReady(QImage);
private slots:
    // 帧率控制槽函数
    void run();
private:
    // 获取矩阵地址实现
    bool setMat(cv::Mat *mat);
    cv::Mat* _mat_buffer{nullptr};
    QImage _img_buffer;

    // 核心主线程
    QThread *_core_thread{nullptr};

    // 帧间计时变量
    QElapsedTimer _ela;
    // 帧间控制计时器
    QTimer* _frame_timer{nullptr};
    //计时变量
    int64_t _start;
    int64_t _end;

    // 当前fps
    int _cur_fps;

    // 运行状态
    int _run_flage;
    // 帧间延迟
    double _frame_delay;

    // 帧率
    int fps();
};

#endif // M_VIDEOCORE_H
