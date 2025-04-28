#ifndef M_UPDATE_H
#define M_UPDATE_H

#include <QWidget>
#include "m_settingbase.h"

class M_Update : public M_SettingBase
{
    Q_OBJECT
public:
    explicit M_Update(QWidget *parent = nullptr);
};

#endif // M_UPDATE_H
