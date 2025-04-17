#ifndef M_MODELSETTINGS_H
#define M_MODELSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>

#include "ElaScrollPage.h"

class ElaComboBox;
class ElaSpinBox;
class ElaToggleSwitch;

class M_ModelSettings : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit M_ModelSettings(QWidget *parent = nullptr);

signals:
private:
    ElaComboBox* _Comb_1{nullptr};
    ElaSpinBox* _SpinBox_1{nullptr};
    ElaToggleSwitch* _Toggle_1{nullptr};

    QStringList _List_1{"框架1","框架2","框架3"};
};

#endif // M_MODELSETTINGS_H
