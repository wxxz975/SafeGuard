#include "m_mainpage.h"
#include "ElaStatusBar.h"
#include "ElaText.h"

#include "m_settings.h"
#include "m_homepage.h"
#include "m_modelsettings.h"
#include "m_selectionsettings.h"
#include "m_count.h"

#include <QDebug>

M_MainPage::M_MainPage(QWidget *parent)
    : M_SettingsIF{parent}
{
    // =============== UI ================
    // Ela界面配置
    setWindowTitle("智能安检");
    setUserInfoCardVisible(false);
    setNavigationBarDisplayMode(ElaNavigationType::Minimal);
    // 添加导航栏页面
    _mHomepage = new M_HomePage();
    addPageNode("安检监控",_mHomepage,ElaIconType::House);

    _mSelect = new M_SelectionSettings();
    addPageNode("识别配置",_mSelect,ElaIconType::GearComplex);

    _mModelSettings = new M_ModelSettings();
    addPageNode("模型配置",_mModelSettings,ElaIconType::GearComplex);

    _mSettings = new M_Settings();
    addPageNode("标记设置",_mSettings,ElaIconType::GearComplex);

    _mCount = new M_Count();
    addPageNode("识别统计",_mCount,ElaIconType::Calculator);
    // =============== UI ================

    //
    PageConfig();
}

M_MainPage::~M_MainPage()
{

}

void M_MainPage::bindModelCfgNum(std::string title, int id, int min, int max)
{
    if(_mModelSettings==nullptr)return;
    _mModelSettings->addCfgNum(title,id,min,max);
}

void M_MainPage::bindModelCfgList(std::string title, int id, std::vector<std::string> list)
{
    if(_mModelSettings==nullptr)return;
    _mModelSettings->addCfgListm(title,id,list);
}

void M_MainPage::bindModelCfgButton(std::string title, int id)
{
    if(_mModelSettings==nullptr)return;
    _mModelSettings->addCfgButton(title,id);
}
