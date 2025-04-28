#ifndef M_COUNT_H
#define M_COUNT_H

#include <QWidget>

#include "m_settingbase.h"

class ElaTableView;

class M_Count : public M_SettingBase
{
    Q_OBJECT
public:
    explicit M_Count(QWidget *parent = nullptr);
signals:
private:
    ElaTableView* tables{nullptr};
};

#endif // M_COUNT_H
