#include "m_settings.h"

#include "ElaScrollPageArea.h"
#include "ElaColorDialog.h"
#include "ElaComboBox.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaToggleSwitch.h"
#include "ElaToggleButton.h"

#include <QSpacerItem>
#include <QDebug>


M_Settings::M_Settings(QWidget *parent)
    : M_SettingBase{parent}
{
    // =============== UI ================
    ElaText* themeText = new ElaText("边框设置", this);
    themeText->setWordWrap(false);
    themeText->setTextPixelSize(18);

    // 线条效果展示

    ElaScrollPageArea* _LineShowArea = new ElaScrollPageArea(this);
    QHBoxLayout *_LineShowLayout = new QHBoxLayout();
    QWidget *LineBoard = new QWidget(this);
    _LineShowArea->setFixedHeight(350);
    _LineShowArea->setLayout(_LineShowLayout);
    _LineShowLayout->addWidget(LineBoard);

    // 颜色选择项
    ElaScrollPageArea* _ColorArea = new ElaScrollPageArea(this);
    _ColorArea->setFixedHeight(140);
    QHBoxLayout* _ColorLayout = new QHBoxLayout();

    _ColorDialog = new ElaColorDialog(this);
    _ColorDialog->setCurrentColor(QColor(240,0,0));
    // title
    _ColorDialog->setWindowTitle("颜色选择器");
    ElaText* colorText = new ElaText(_ColorDialog->getCurrentColorRGB(), this);
    colorText->setTextPixelSize(15);
    ElaPushButton* colorDialogButton = new ElaPushButton(this);
    colorDialogButton->setFixedSize(35, 35);
    colorDialogButton->setLightDefaultColor(_ColorDialog->getCurrentColor());
    colorDialogButton->setLightHoverColor(_ColorDialog->getCurrentColor());
    colorDialogButton->setLightPressColor(_ColorDialog->getCurrentColor());
    colorDialogButton->setDarkDefaultColor(_ColorDialog->getCurrentColor());
    colorDialogButton->setDarkHoverColor(_ColorDialog->getCurrentColor());
    colorDialogButton->setDarkPressColor(_ColorDialog->getCurrentColor());
    connect(colorDialogButton, &ElaPushButton::clicked, this, [=]() {
        _ColorDialog->exec();
    });
    connect(_ColorDialog, &ElaColorDialog::colorSelected, this, [=](const QColor& color) {
        colorDialogButton->setLightDefaultColor(color);
        colorDialogButton->setLightHoverColor(color);
        colorDialogButton->setLightPressColor(color);
        colorDialogButton->setDarkDefaultColor(color);
        colorDialogButton->setDarkHoverColor(color);
        colorDialogButton->setDarkPressColor(color);
        colorText->setText(_ColorDialog->getCurrentColorRGB());
        LineBoard->update();
        _Save->show();
    });

    ElaText* _ColorDialogText = new ElaText("线条&文本颜色", this);
    QVBoxLayout* _LayoutV = new QVBoxLayout(_ColorArea);
    _LayoutV->addLayout(_ColorLayout);
    _ColorDialogText->setTextPixelSize(15);
    _ColorLayout->addSpacing(20);
    _ColorLayout->addWidget(_ColorDialogText);
    _ColorLayout->addStretch();
    _ColorLayout->addWidget(colorDialogButton);
    _ColorLayout->addWidget(colorText);
    _ColorLayout->addSpacing(40);

    _ColorLayout = new QHBoxLayout();
    _LayoutV->addSpacing(10);
    _LayoutV->addLayout(_ColorLayout);
    _LineWidth_SpinBox = new ElaSpinBox(this);
    connect(_LineWidth_SpinBox,&ElaSpinBox::textChanged,this,[=](){
        LineBoard->update();
        _Save->show();
    });

    _LineWidth_SpinBox->setMinimum(1);
    _LineWidth_SpinBox->setMaximum(10);
    ElaText* _HeadText = new ElaText("线条宽度", this);
    _HeadText->setTextPixelSize(15);

    _ColorLayout->addSpacing(20);
    _ColorLayout->addWidget(_HeadText);
    _ColorLayout->addStretch();
    _ColorLayout->addWidget(_LineWidth_SpinBox);
    _ColorLayout->addSpacing(20);
    _LayoutV->addSpacing(10);

    // 标记文本配置

    ElaScrollPageArea* _TextArea = new ElaScrollPageArea(this);
    _TextArea->setFixedHeight(140);
    QVBoxLayout* _TextLayoutV = new QVBoxLayout(_TextArea);
    QHBoxLayout* _TextLayoutPH = new QHBoxLayout();
    _TextLayoutV->addLayout(_TextLayoutPH);
    _TextPosition_ComBox = new ElaComboBox(this);
    _TextPosition_ComBox->addItems(_TPCList);
    connect(_TextPosition_ComBox,&ElaComboBox::currentTextChanged,this,[=](){
        LineBoard->update();
        _Save->show();
    });

    ElaText* _TextPosition = new ElaText("标记位置", this);
    _TextPosition->setTextPixelSize(15);
    _TextLayoutPH->addSpacing(20);
    _TextLayoutPH->addWidget(_TextPosition);
    _TextLayoutPH->addStretch();
    _TextLayoutPH->addWidget(_TextPosition_ComBox);
    _TextLayoutPH->addSpacing(20);

    _TextLayoutV->addSpacing(20);
    // 文本大小
    ElaText* _TextSize = new ElaText("文本大小", this);
    _TextSize->setTextPixelSize(15);
    _TextFontSize_SpinBox = new ElaSpinBox(this);
    connect(_TextFontSize_SpinBox,&ElaSpinBox::textChanged,this,[=](){
        LineBoard->update();
        _Save->show();
    });
    _TextFontSize_SpinBox->setMinimum(10);
    _TextFontSize_SpinBox->setMaximum(40);
    QHBoxLayout* _TextLayoutSH = new QHBoxLayout();
    _TextLayoutV->addLayout(_TextLayoutSH);
    _TextLayoutSH->addSpacing(20);
    _TextLayoutSH->addWidget(_TextSize);
    _TextLayoutSH->addStretch();
    _TextLayoutSH->addWidget(_TextFontSize_SpinBox);
    _TextLayoutSH->addSpacing(20);

    // 添加页面布局
    //board
    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(_LineShowArea);
    //color selector
    centerLayout->addSpacing(10);
    centerLayout->addWidget(_ColorArea);
    //Text config
    //position
    centerLayout->addSpacing(10);
    centerLayout->addWidget(_TextArea);
    centerLayout->addSpacing(10);
    //

    // 识别配置
    themeText = new ElaText("识别配置", this);
    themeText->setWordWrap(false);
    themeText->setTextPixelSize(18);

    _IdentifyArea = new ElaScrollPageArea(this);
    _IdentifyArea->installEventFilter(this);
    LoadButton();

    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeText);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(_IdentifyArea);

    // 模型设置
    themeText = new ElaText("模型设置", this);
    themeText->setWordWrap(false);
    themeText->setTextPixelSize(18);


    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeText);
    centerLayout->addSpacing(20);

    setTitle("设置");
    centerLayout->addWidget(_Save);
    _Save->hide();
    // =============== UI ================

    // 事件监听
    LineBoard->installEventFilter(this);
}

void M_Settings::addCfgNum(std::string &title, int id, int min, int max)
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

    centerLayout->insertWidget(centerLayout->count()-1,ESPA);
}

void M_Settings::addCfgListm(std::string &title, int id, std::vector<std::string> &list)
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
    centerLayout->insertWidget(centerLayout->count()-1,ESPA);
}

void M_Settings::addCfgButton(std::string &title, int id)
{
    ElaScrollPageArea* ESPA = new ElaScrollPageArea(this);
    QHBoxLayout* HBLay = new QHBoxLayout(ESPA);
    ElaToggleSwitch* ElaTog = new ElaToggleSwitch(this);

    ElaText* ElaT = new ElaText(QString(title.c_str()),this);
    ElaT->setTextPixelSize(15);
    HBLay->addSpacing(20);
    HBLay->addWidget(ElaT);
    HBLay->addStretch();
    HBLay->addWidget(ElaTog);
    HBLay->addSpacing(20);
    connect(ElaTog,&ElaToggleSwitch::toggled,this,[=](){
        _Save->show();
    });
    centerLayout->insertWidget(centerLayout->count()-1,ESPA);
}

bool M_Settings::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == _IdentifyArea){
        if(event->type()==QEvent::Resize){
            updateIdentifyButton();
        }
    }
    else{
        if(event->type() == QEvent::Paint){
            QWidget *w = static_cast<QWidget*>(watched);
            if(w){
                QPainter pa(w);
                QFont font;
                QPen pen;

                font.setPointSize(_TextFontSize_SpinBox->value());
                pen.setColor(_ColorDialog->getCurrentColor());
                pen.setWidth(_LineWidth_SpinBox->value());
                pa.setPen(pen);
                pa.setFont(font);
                pa.drawRect(60,50,w->width()-120,w->height()-100);
                pa.drawText(62+pen.width(),
                            _TextPosition_ComBox->currentIndex()?50-pen.width():50+pa.fontMetrics().ascent()+pa.fontMetrics().descent(),
                            _BoradText);
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

QStringList M_Settings::LoadText()
{
    IDF_KV.insert("剪刀1",1);
    IDF_KV.insert("菜刀菜刀",2);
    IDF_KV.insert("炸菜刀菜刀弹",3);
    IDF_KV.insert("锤头炸菜刀菜刀弹炸菜刀",4);
    IDF_KV.insert("剪刀",12);
    IDF_KV.insert("剪刀1",51);
    IDF_KV.insert("菜刀炸菜刀菜刀弹炸菜刀菜刀弹炸菜刀菜刀弹",11);
    IDF_KV.insert("炸菜刀菜刀弹",45);
    IDF_KV.insert("锤头炸菜刀菜刀弹炸菜刀",63);
    IDF_KV.insert("剪刀",34);
    IDF_KV.insert("炸弹炸弹",6);
    IDF_KV.insert("菜刀菜刀",35);
    IDF_KV.insert("炸菜刀菜刀弹",24);
    IDF_KV.insert("锤头炸菜刀菜刀弹炸菜刀",35);
    IDF_KV.insert("剪刀",456);
    return {"剪刀1","菜刀菜刀","炸菜刀菜刀弹","锤头炸菜刀菜刀弹炸菜刀","剪刀","菜刀炸菜刀菜刀弹炸菜刀菜刀弹炸菜刀菜刀弹","炸弹","炸弹炸弹","剪刀1","菜刀菜刀","炸菜刀菜刀弹","锤头菜","剪刀","菜刀","炸弹","炸弹炸弹"};
}

void M_Settings::LoadButton()
{
    QStringList list = LoadText();
    ElaToggleButton* bt;
    if(!Btns.isEmpty())for(ElaToggleButton*i:Btns){delete i;}
    Btns.clear();
    QFont font;
    for(QString&i:list){
        bt = new ElaToggleButton(i);
        Btns.push_back(bt);
        bt->setMinimumWidth(bt->font().pixelSize()*i.count()+20);
        bt->setMaximumWidth(bt->font().pixelSize()*i.count()+20);
        bt->setMinimumHeight(bt->font().pixelSize()+20);
        bt->setMaximumHeight(bt->font().pixelSize()+20);
    }
}

void M_Settings::updateIdentifyButton()
{
    if(_IdentifyArea==nullptr||Btns.isEmpty())return;
    const int margin = 10;
    int width = centralWidget->width()-2*centerLayout->margin();
    int _w = margin,_tmp = 0,_h = margin;
    QFont font = Btns.at(0)->font();
    for(ElaToggleButton*&i:Btns)
    {
        i->setParent(_IdentifyArea);
        if(_w+i->width()+margin/2>width){
            _w=margin;
            _h+=i->height()+margin/2;
        }
        i->move(_w,_h);
        _w+=i->width()+margin/2;
    }
    if(Btns.count()>0){
        _h+=Btns[0]->height();
    }
    _IdentifyArea->setMaximumHeight(_h+margin);
    _IdentifyArea->setMinimumHeight(_h+margin);
}










