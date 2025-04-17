#ifndef M_HOMEPAGE_H
#define M_HOMEPAGE_H

#include <QWidget>

#include "ElaScrollPage.h"

class M_VideoCore;

class M_HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit M_HomePage(QWidget *parent = nullptr);
    ~ M_HomePage();
signals:
private:
    // 主屏幕
    QWidget* _mMainScreen{nullptr};
    // 截图列表
    QWidget* _mImgList{nullptr};
    // 截图横向布局
    QHBoxLayout *hb{nullptr};

    M_VideoCore *_mVideoc{nullptr};
};

#endif // M_HOMEPAGE_H
