#include "m_settingsif.h"

#include "../M_Def.h"

#include <QDebug>

M_SettingsIF::M_SettingsIF(QWidget *parent)
    : ElaWindow{parent}
{
}

void M_SettingsIF::PageConfig()
{
    //========= page config =============
    bindModelCfgNum("测试1",0,10,45);
    bindModelCfgNum("测试2",1,20,35);
    bindModelCfgNum("测试3",2,0,234);
    bindModelCfgNum("测试4",3,0,1000);

    std::vector<std::string> list;
    list.push_back("选项1111");
    list.push_back("选项22222222");
    list.push_back("选项3");
    list.push_back("选项45678");
    bindModelCfgList("选项测试",4,list);

    bindModelCfgButton("测试",1);
}
