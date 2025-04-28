#ifndef M_HOMEPAGE_H
#define M_HOMEPAGE_H

#include <QWidget>
#include <QImage>
#include <QVector>

#include "M_Def.h"
#include "m_settingbase.h"

class M_Screen;
class ElaWidget;
class QScrollArea;
class M_SceenShotWidget;

#define SceenShotNum 6

class M_HomePage : public M_SettingBase
{
    Q_OBJECT
public:
    explicit M_HomePage(QWidget *parent = nullptr);
    ~ M_HomePage();

signals:
    void ScreenSizeChange(int width,int height);
    void SendImg(MatType::MT,QImage);
private:

    void addScreenShot(QImage);
    // 主屏幕
    M_Screen* _mMainScreen{nullptr};
    // 截图列表
    ElaScrollArea* _mImgList{nullptr};
    QWidget* _mImgLWidget{nullptr};
    M_SceenShotWidget *_front{nullptr};
    QHBoxLayout *hb{nullptr};
    // 图片和控件列表
    QVector<QImage> _imglist;
    QVector<M_SceenShotWidget*> _mSSWlist;
    int _count;
};

#endif // M_HOMEPAGE_H
