#include "m_modelsettings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaScrollPageArea.h"
#include "ElaComboBox.h"
#include "ElaSpinBox.h"
#include "ElaToggleSwitch.h"
#include "ElaPushButton.h"
#include "ElaText.h"

#include <QDebug>

M_ModelSettings::M_ModelSettings(QWidget *parent)
    : M_SettingBase{parent}
{
    // =============== UI ================
    setTitle("模型配置");
    // =============== UI ================
}

void M_ModelSettings::addCfgNum(std::string& title, int id, int min, int max)
{
    if(centerLayout==nullptr)return;
    ElaScrollPageArea* ESPA = new ElaScrollPageArea(this);
    QHBoxLayout* HBLay = new QHBoxLayout(ESPA);
    ElaSpinBox* ElaSpin = new ElaSpinBox(this);
    ElaSpin->setMinimum(min);
    ElaSpin->setMaximum(max);
    connect(ElaSpin,&ElaSpinBox::textChanged,this,[=](){
        _Save->show();
    });

    ElaText* ElaT= new ElaText(QString(title.c_str()), this);
    ElaT->setTextPixelSize(15);
    HBLay->addSpacing(20);
    HBLay->addWidget(ElaT);
    HBLay->addStretch();
    HBLay->addWidget(ElaSpin);
    HBLay->addSpacing(20);

    centerLayout->insertWidget(centerLayout->count()-2,ESPA);
}

void M_ModelSettings::addCfgListm(std::string &title, int id, std::vector<std::string> &list)
{
    ElaScrollPageArea* ESPA = new ElaScrollPageArea(this);
    QHBoxLayout* HBLay = new QHBoxLayout(ESPA);
    ElaComboBox* ElaComb = new ElaComboBox(this);

    for(std::vector<std::string>::iterator it = list.begin();it!=list.end();it++){
        ElaComb->addItem(QString(it->c_str()));
    }

    connect(ElaComb,&ElaComboBox::currentTextChanged,this,[=](){
        ElaComb->show();
    });

    ElaText* ElaT = new ElaText(QString(title.c_str()), this);
    ElaT->setTextPixelSize(15);
    HBLay->addSpacing(20);
    HBLay->addWidget(ElaT);
    HBLay->addStretch();
    HBLay->addWidget(ElaComb);
    HBLay->addSpacing(20);
    centerLayout->insertWidget(centerLayout->count()-2,ESPA);
}

void M_ModelSettings::addCfgButton(std::string str, int id)
{
    ElaScrollPageArea* ESPA = new ElaScrollPageArea(this);
    QHBoxLayout* HBLay = new QHBoxLayout(ESPA);
    ElaToggleSwitch* ElaTog = new ElaToggleSwitch(this);

    ElaText* ElaT = new ElaText(QString(str.c_str()), this);
    ElaT->setTextPixelSize(15);
    HBLay->addSpacing(20);
    HBLay->addWidget(ElaT);
    HBLay->addStretch();
    HBLay->addWidget(ElaTog);
    HBLay->addSpacing(20);
    connect(ElaTog,&ElaToggleSwitch::toggled,this,[=](){
        _Save->show();
    });
    centerLayout->insertWidget(centerLayout->count()-2,ESPA);
}
