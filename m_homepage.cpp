#include "m_homepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "ElaWidget.h"
#include "ElaScrollPageArea.h"

#include "m_screen.h"
#include "m_videocore.h"

#include <QDebug>

M_HomePage::M_HomePage(QWidget *parent)
    : ElaScrollPage{parent}
{
    // =============== UI ================
    // Ela界面配置
    setTitleVisible(false);
    setContentsMargins(5, 5, 5, 5);

    //
    _mMainScreen = new M_Screen();
    _mImgList = new QWidget(this);
    _mImgList->setMaximumHeight(200);
    // 布局配置
    hb = new QHBoxLayout(_mImgList);
    for(int i = 0;i<4;i++){
        QWidget * img = new QWidget(this);
        img->setStyleSheet("border-radius:1px solid;background-color: rgb(200, 200, 200);");
        img->setMaximumWidth(240);
        img->setMinimumWidth(240);
        hb->addWidget(img);
    }
    hb->setMargin(0);
    hb->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("home");
    addCentralWidget(centralWidget);
    // 属相布局
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setSpacing(10);
    centerLayout->setContentsMargins(2, 2, 2, 2);
    centerLayout->addWidget(_mMainScreen);
    centerLayout->addWidget(_mImgList);
    centerLayout->setStretch(0,75);
    centerLayout->setStretch(1,25);
    // =============== UI ================

    // 视频核心
    _mVideoc = new M_VideoCore();
    connect(_mVideoc,SIGNAL(readReady(QImage)),_mMainScreen,SLOT(readImage(QImage)));

}

M_HomePage::~M_HomePage()
{

}
