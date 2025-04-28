#ifndef M_MAINPAGE_H
#define M_MAINPAGE_H

#include "interface/m_settingsif.h"
#include "m_videocore.h"
#include "M_Def.h"

class M_Settings;
class M_HomePage;
class M_ModelSettings;
class M_SelectionSettings;
class M_Count;
class M_Update;


class M_MainPage : public M_SettingsIF
{
    Q_OBJECT
public:
    explicit M_MainPage(M_VideoCore* _VideoCore,QWidget *parent = nullptr);
    ~M_MainPage();
signals:
private:
    // 边框设置界面
    M_Settings* _mSettings{nullptr};
    // 主界面
    M_HomePage* _mHomepage{nullptr};
    // 更新界面
    M_Update* _mUpdate{nullptr};
    // 统计界面界面
    M_Count* _mCount{nullptr};
    // 视频核心指针
    M_VideoCore* _VCore{nullptr};

    // 连接核心信号槽
    void bindVideoCore();

    void bindModelCfgNum(std::string title,int id,int min,int max);
    void bindModelCfgList(std::string title,int id,std::vector<std::string> list);
    void bindModelCfgButton(std::string title,int id);

};

#endif // M_MAINPAGE_H
