#ifndef M_SETTINGSIF_H
#define M_SETTINGSIF_H

#include "ElaWindow.h"

#include <string>
#include <vector>

//enum SetType{Num,DropList,Button};
//typedef void (*PcallBack)(int) ;

class M_SettingsIF : public ElaWindow
{
    Q_OBJECT
public:
    explicit M_SettingsIF(QWidget *parent = nullptr);

    // 配置声明函数
    // 在此处添加绑定需要的选项
    // 无需手动触发
    void PageConfig();

    // 添加模型配置绑定函数 数值类
    // 当配置变更并保存确定时会触发 M_VideoIF 中 configChange(int id,int value) 函数
    // 参数1  显示名称      std::string
    // 参数2  绑定id       int            当数值改变时用于确定分辨绑定的函数
    // 参数3  限定值       int            控件最小值 默认值0
    // 参数4  限定值       int            控件最大值 默认值100
    // configChange 详细说明
    // 参数1  触发的id      int            配置更改的id
    // 参数2  改变的值      int            用户修改的值
    virtual void bindModelCfgNum(std::string title,int id,int min,int max) = 0;


    // 添加模型配置绑定函数 下拉列表
    // 当配置变更并保存确定时会触发 M_VideoIF 中 configChange(int id,int value) 函数
    // 参数1  显示名称      std::string
    // 参数2  绑定id       int            当数值改变时用于确定分辨绑定的函数
    // 参数3  绑定id       int            当数值改变时用于确定分辨绑定的函数
    // configChange 详细说明
    // 参数1  触发的id      int            配置更改的id
    // 参数2  选项下标      int            用户选中的选项下标
    virtual void bindModelCfgList(std::string title,int id,std::vector<std::string> list) = 0;


    // 添加模型配置绑定函数 按钮类
    // 当配置变更并保存确定时会触发 M_VideoIF 中 configChange(int id,int value) 函数
    // 参数1  显示名称      std::string
    // 参数2  绑定id       int            当数值改变时用于确定分辨绑定的函数
    // configChange 详细说明
    // 参数1  触发的id      int            配置更改的id
    // 参数2  是否使用      int            用户是否使用选项
    //        value       0              禁用
    //            |       1              启用
    //            |       *              无效
    virtual void bindModelCfgButton(std::string title,int id) = 0;


signals:

private:
};

#endif // M_SETTINGSIF_H
