#ifndef M_SETTINGS_H
#define M_SETTINGS_H

#include <QWidget>
#include <QEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStringList>
#include <QPainter>

#include "ElaScrollPage.h"

class ElaScrollPageArea;
class ElaColorDialog;
class ElaComboBox;
class ElaSpinBox;

class M_Settings : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit M_Settings(QWidget *parent = nullptr);


private:

    bool eventFilter(QObject *watched, QEvent *event);

    ElaScrollPageArea* _ColorArea{nullptr};
    QHBoxLayout* _ColorLayout{nullptr};
    ElaColorDialog* _ColorDialog{nullptr};
    ElaComboBox* _TextPosition_ComBox{nullptr};
    ElaSpinBox* _TextFontSize_SpinBox{nullptr};
    ElaSpinBox* _LineWidth_SpinBox{nullptr};
    QStringList _TPCList{"左上边框内","左上边框外"};
    QString _BoradText = "违禁品";


signals:
};

#endif // M_SETTINGS_H
