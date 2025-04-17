#ifndef M_SELECTIONSETTINGS_H
#define M_SELECTIONSETTINGS_H

#include <QWidget>
#include <QEvent>
#include <QStringList>

#include "ElaScrollPage.h"


class M_SelectionSettings : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit M_SelectionSettings(QWidget *parent = nullptr);

signals:
private:
    bool eventFilter(QObject *watched, QEvent *event);
    QStringList list{"剪刀","菜刀","炸弹","锤头","剪刀","菜刀","炸弹","锤头"};
};

#endif // M_SELECTIONSETTINGS_H
