#include "m_selectionsettings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>

#include "ElaScrollPageArea.h"
#include "ElaComboBox.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaToggleButton.h"

#include <QDebug>

M_SelectionSettings::M_SelectionSettings(QWidget *parent)
    : ElaScrollPage{parent}
{

    // =============== UI ================
    // Ela界面配置
    ElaScrollPageArea* _Text = new ElaScrollPageArea(this);
    _Text->setFixedHeight(400);
    // 按钮自适应布局
    // 未完成

//    QGridLayout* _Layout = new QGridLayout(_Text);

//    _Layout->setHorizontalSpacing(5); // 水平间距
//    _Layout->setVerticalSpacing(5);   // 垂直间距

    //    _Layout->setSpacing(0);
    //    _Layout->setContentsMargins(0, 0, 0, 0);
//    _Layout->setHorizontalSpacing(10);
    // 设置垂直间距
//    _Layout->setVerticalSpacing(10);

//    ElaToggleButton* bt;
//    QSpacerItem *horizontalSpacer;
//    int j = 0;
//    for(int i = 0;i<list.count();i++){
//        bt = new ElaToggleButton(this);
//        bt->setText(list[i]);
//        _Layout->addWidget(bt,j,i,1,1,Qt::AlignLeft|Qt::AlignTop);

//    }
    //    for(int i = 0;i<6;i++){
    //        for(j = 0;j<6;++j){
    //            if(i*6+j+1>list.count())break;
    //            bt = new ElaToggleButton(this);
    //            bt->setText(list[i*6+j]);
    //            _Layout->addWidget(bt,i,j,1,1,Qt::AlignLeft|Qt::AlignTop);
    //        }
    //        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //        _Layout->addItem(horizontalSpacer, i, j);
    //        qDebug()<<i<<j;
    //        if(i*6+j+1>list.count())break;
    //    }
//    qDebug()<<bt->size();

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("识别配置");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addWidget(_Text);
    centerLayout->addStretch();
    addCentralWidget(centralWidget);
    // =============== UI ================
}

bool M_SelectionSettings::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}
