#ifndef M_MODELSETTINGS_H
#define M_MODELSETTINGS_H

#include <QWidget>
#include "m_settingbase.h"

class M_ModelSettings : public M_SettingBase
{
    Q_OBJECT
public:
    explicit M_ModelSettings(QWidget *parent = nullptr);

    void addCfgNum(std::string &, int id, int min, int max);
    void addCfgListm(std::string &title, int id, std::vector<std::string> &list);
    void addCfgButton(std::string,int id);
};

#endif // M_MODELSETTINGS_H
