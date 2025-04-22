#include "m_settingbase.h"

#include <QVBoxLayout>

#include "ElaScrollPageArea.h"
#include "ElaPushButton.h"
#include "ElaText.h"

M_SettingBase::M_SettingBase(QWidget *parent)
    : ElaScrollPage{parent}
{
    _Save = new ElaScrollPageArea(this);
    QHBoxLayout* _SaveLayout = new QHBoxLayout(_Save);
    ElaPushButton* Savebtn = new ElaPushButton(this);
    Savebtn->setText("保存");
    ElaPushButton* Cancelbtn = new ElaPushButton(this);
    Cancelbtn->setText("取消");

    connect(Savebtn,&ElaPushButton::clicked,this,[=](){
        _Save->hide();
    });
    connect(Cancelbtn,&ElaPushButton::clicked,this,[=](){
        _Save->hide();
    });

    ElaText* _Info = new ElaText("配置已修改,是否保存", this);
    _Info->setTextPixelSize(18);
    _SaveLayout->addSpacing(20);
    _SaveLayout->addWidget(_Info);
    _SaveLayout->addStretch();
    _SaveLayout->addWidget(Savebtn);
    _SaveLayout->addWidget(Cancelbtn);
    _SaveLayout->addSpacing(20);
    _Save->hide();

    centralWidget = new QWidget(this);
    centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addWidget(_Save);
    centerLayout->addStretch();

}

void M_SettingBase::setTitle(QString title)
{
    centralWidget->setWindowTitle(title);
    addCentralWidget(centralWidget, true, true, 0);
}

void M_SettingBase::ToSave()
{
    _Save->show();
}
