#include "m_mainpage.h"
#include "ElaStatusBar.h"
#include "ElaText.h"

#include "m_settings.h"
#include "m_homepage.h"
#include "m_update.h"
#include "m_count.h"

#include <QDebug>

M_MainPage::M_MainPage(M_VideoCore* _VideoCore,QWidget *parent)
    : M_SettingsIF{parent},_VCore{_VideoCore}
{
    // =============== UI ================
    // Ela界面配置
    setWindowTitle("智能安检");
    setUserInfoCardVisible(false);
    setNavigationBarDisplayMode(ElaNavigationType::Minimal);
    // 添加导航栏页面
    _mHomepage = new M_HomePage();
    addPageNode("安检监控",_mHomepage,ElaIconType::House);

    _mSettings = new M_Settings();
    addPageNode("软件设置",_mSettings,ElaIconType::GearComplex);

    _mCount = new M_Count();
    addPageNode("识别统计",_mCount,ElaIconType::ChartPie);
    //ElaIconType::LaptopArrowDown

    _mUpdate = new M_Update();
    addPageNode("软件更新",_mUpdate,ElaIconType::LaptopArrowDown);


    // 更新维护

    // =============== UI ================

    //
    PageConfig();
    bindVideoCore();
}

M_MainPage::~M_MainPage()
{

}

void M_MainPage::bindVideoCore()
{
    connect(_VCore,SIGNAL(readReady(MatType::MT,QImage)),_mHomepage,SIGNAL(SendImg(MatType::MT,QImage)));
    connect(_mHomepage,SIGNAL(ScreenSizeChange(int,int)),_VCore,SLOT(GetScreenSizeChange(int,int)));
    connect(_mHomepage,SIGNAL(ScreenSizeChange(int,int)),_VCore,SLOT(ScreenSizeChange(int,int)));
}

void M_MainPage::bindModelCfgNum(std::string title, int id, int min, int max)
{
    if(_mSettings==nullptr)return;
    _mSettings->addCfgNum(title,id,min,max);
}

void M_MainPage::bindModelCfgList(std::string title, int id, std::vector<std::string> list)
{
    if(_mSettings==nullptr)return;
    _mSettings->addCfgListm(title,id,list);
}

void M_MainPage::bindModelCfgButton(std::string title, int id)
{
    if(_mSettings==nullptr)return;
    _mSettings->addCfgButton(title,id);
}
