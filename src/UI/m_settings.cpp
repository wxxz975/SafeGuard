#include "m_settings.h"

#include "ElaScrollPageArea.h"
#include "ElaColorDialog.h"
#include "ElaComboBox.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaPushButton.h"

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
    _ColorArea = new ElaScrollPageArea(this);
    _ColorArea->setFixedHeight(140);
    _ColorLayout = new QHBoxLayout();

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
    centerLayout->insertSpacing(0,10);
    centerLayout->insertWidget(1,_LineShowArea);
    //color selector
    centerLayout->insertSpacing(2,10);
    centerLayout->insertWidget(3,themeText);
    centerLayout->insertSpacing(4,10);
    centerLayout->insertWidget(5,_ColorArea);
    //Text config
    //position
    centerLayout->insertSpacing(6,10);
    centerLayout->insertWidget(7,_TextArea);
    centerLayout->insertSpacing(8,10);
//    centerLayout->addSpacing(10);
//    centerLayout->addWidget(_TextArea);
//    centerLayout->addSpacing(10);

    setTitle("设置");
    _Save->hide();
    // =============== UI ================

    // 事件监听
    LineBoard->installEventFilter(this);
}

bool M_Settings::eventFilter(QObject *watched, QEvent *event)
{
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
//            pa.drawText(pa.fontMetrics().width(_BoradText));
        }
    }
    return QWidget::eventFilter(watched,event);
}
