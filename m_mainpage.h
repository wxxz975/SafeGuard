#ifndef M_MAINPAGE_H
#define M_MAINPAGE_H

#include <QWidget>
//
#include "ElaWindow.h"

class M_Settings;
class M_HomePage;
class M_ModelSettings;
class M_SelectionSettings;
class M_Count;

class M_MainPage : public ElaWindow
{
    Q_OBJECT
public:
    explicit M_MainPage(QWidget *parent = nullptr);
    ~M_MainPage();
signals:
private:
    // 边框设置界面
    M_Settings* _mSettings{nullptr};
    // 主界面
    M_HomePage* _mHomepage{nullptr};
    // 模型配置界面
    M_ModelSettings* _mModelSettings{nullptr};
    // 配置识别界面
    M_SelectionSettings* _mSelect{nullptr};
    // 统计界面界面
    M_Count* _mCount{nullptr};
};

#endif // M_MAINPAGE_H
