#ifndef M_SETTINGS_H
#define M_SETTINGS_H

#include <QWidget>
#include <QEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStringList>
#include <QPainter>
#include <QVector>

#include <QMap>

#include "m_settingbase.h"

class ElaScrollPageArea;
class ElaColorDialog;
class ElaComboBox;
class ElaSpinBox;
class ElaToggleButton;

class M_Settings : public M_SettingBase
{
    Q_OBJECT
public:
    explicit M_Settings(QWidget *parent = nullptr);


    void addCfgNum(std::string &title, int id, int min, int max);
    void addCfgListm(std::string &titletitle, int id, std::vector<std::string> &list);
    void addCfgButton(std::string &title,int id);

private:

    void IDF_BtnClick(int id);

    bool eventFilter(QObject *watched, QEvent *event);
    QStringList LoadText();
    void LoadButton();
    void updateIdentifyButton();
    QVector<ElaToggleButton*> Btns;

    ElaScrollPageArea* _IdentifyArea{nullptr};
    ElaColorDialog* _ColorDialog{nullptr};
    ElaComboBox* _TextPosition_ComBox{nullptr};
    ElaSpinBox* _TextFontSize_SpinBox{nullptr};
    ElaSpinBox* _LineWidth_SpinBox{nullptr};

    const QStringList _TPCList{"左上边框内","左上边框外"};
    const QString _BoradText = "违禁品";

    QMap<std::string,int> IDF_KV;

signals:
};

#endif // M_SETTINGS_H
