#ifndef M_VIDEOIF_H
#define M_VIDEOIF_H

#include <QObject>

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
protected:
    // 函数功能: 传入矩阵
    // 函数触发时 无传入参数
    // 函数内部使用 setmat 传入矩阵地址
    // 此函数无需手动触发
    void readyRead();

    // 函数功能: 画面大小已变化
    // 函数触发时 传入当前画面大小
    // 此函数无需手动触发
//    void windowChange(int width,int height);

    // 开始
    virtual bool start() = 0;
    // 停止
    virtual void stop() = 0;

    virtual int fps() = 0;

    // 函数功能: 获取矩阵地址
    // 在 readyRead 内使用
    // 参数值 矩阵地址(一帧画面)
    // 返回值 执行结果 true为正常 false为无效
    virtual bool setMat(cv::Mat*) = 0;

    // 函数功能: 配置发生更改
    // 函数触发时 传入绑定id和数值
    // 参数1  触发的id      int            配置更改的id
    // 参数2  改变的值      int
    // 详细函数说明需查看 M_SettingsIF 头文件
    // 此函数无需手动触发
    void configChange(int id,int value);

protected slots:
    // 函数功能: 矩阵已使用
    // 函数触发时 传入已使用矩阵地址
    // 此函数无需手动触发
    void readCompleted(cv::Mat* used);
private:
    // 临时
    int count;
};

#endif // M_VIDEOIF_H
