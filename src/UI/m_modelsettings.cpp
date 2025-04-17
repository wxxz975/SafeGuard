#include "m_modelsettings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaText.h"
#include "ElaScrollPageArea.h"
#include "ElaComboBox.h"
#include "ElaSpinBox.h"
#include "ElaToggleSwitch.h"
#include "ElaPushButton.h"

M_ModelSettings::M_ModelSettings(QWidget *parent)
    : ElaScrollPage{parent}
{
    // =============== UI ================
    // Ela界面配置
    // save
    ElaScrollPageArea* _Save = new ElaScrollPageArea(this);
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
    // 模型位置

    // 模型框架

    ElaScrollPageArea* _TextArea = new ElaScrollPageArea(this);
    QHBoxLayout* _TextLayoutPH = new QHBoxLayout(_TextArea);
    _Comb_1 = new ElaComboBox(this);
    _Comb_1->addItems(_List_1);
    connect(_Comb_1,&ElaComboBox::currentTextChanged,this,[=](){
        _Save->show();
    });

    ElaText* _Text = new ElaText("模型参数-下拉类型", this);
    _Text->setTextPixelSize(15);
    _TextLayoutPH->addSpacing(20);
    _TextLayoutPH->addWidget(_Text);
    _TextLayoutPH->addStretch();
    _TextLayoutPH->addWidget(_Comb_1);
    _TextLayoutPH->addSpacing(20);

    // 模型参数 1 数值
    ElaScrollPageArea* _TextArea_1 = new ElaScrollPageArea(this);
    QHBoxLayout* _TextLayoutPH_1 = new QHBoxLayout(_TextArea_1);
    _SpinBox_1 = new ElaSpinBox(this);
    connect(_SpinBox_1,&ElaSpinBox::textChanged,this,[=](){
        _Save->show();
    });

    ElaText* _Text_1 = new ElaText("模型参数-数值类型", this);
    _Text_1->setTextPixelSize(15);
    _TextLayoutPH_1->addSpacing(20);
    _TextLayoutPH_1->addWidget(_Text_1);
    _TextLayoutPH_1->addStretch();
    _TextLayoutPH_1->addWidget(_SpinBox_1);
    _TextLayoutPH_1->addSpacing(20);

    // 模型参数 2 启用

    ElaScrollPageArea* _TextArea_2 = new ElaScrollPageArea(this);
    QHBoxLayout* _TextLayoutPH_2 = new QHBoxLayout(_TextArea_2);
    _Toggle_1 = new ElaToggleSwitch(this);

    ElaText* _Text_2 = new ElaText("模型参数-启用类型", this);
    _Text_2->setTextPixelSize(15);
    _TextLayoutPH_2->addSpacing(20);
    _TextLayoutPH_2->addWidget(_Text_2);
    _TextLayoutPH_2->addStretch();
    _TextLayoutPH_2->addWidget(_Toggle_1);
    _TextLayoutPH_2->addSpacing(20);
    connect(_Toggle_1,&ElaToggleSwitch::toggled,this,[=](){
        _Save->show();
    });


    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("模型配置");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addWidget(_TextArea);
    centerLayout->addWidget(_TextArea_1);
    centerLayout->addWidget(_TextArea_2);
    centerLayout->addWidget(_Save);

    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
    // =============== UI ================
}
