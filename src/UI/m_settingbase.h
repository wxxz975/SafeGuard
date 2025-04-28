#ifndef M_SETTINGBASE_H
#define M_SETTINGBASE_H

#include <QWidget>
#include <QEvent>
#include "ElaScrollPage.h"

class QVBoxLayout;
class ElaScrollPageArea;

class M_SettingBase : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit M_SettingBase(QWidget *parent = nullptr);

    void setTitle(QString title);

signals:
protected:

    QWidget* centralWidget{nullptr};
    QVBoxLayout* centerLayout{nullptr};
    ElaScrollPageArea* _Save{nullptr};

    void ToSave();
};

#endif // M_SETTINGBASE_H
