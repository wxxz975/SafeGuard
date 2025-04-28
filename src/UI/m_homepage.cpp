#include "m_homepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "ElaWidget.h"
#include "ElaScrollPageArea.h"
#include "ElaScrollArea.h"

#include "m_sceenshotwidget.h"
#include "m_screen.h"

#include <opencv2/opencv.hpp>

#include <QDebug>
#include <QScrollArea>

M_HomePage::M_HomePage(QWidget *parent)
    : M_SettingBase{parent}
{
    // =============== UI ================
    // Ela界面配置
    setTitleVisible(false);
    setContentsMargins(5, 5, 5, 5);

    //
    _mMainScreen = new M_Screen();

    connect(_mMainScreen,SIGNAL(ScreenChange(int,int)),this,SIGNAL(ScreenSizeChange(int,int)));
    connect(this,&M_HomePage::SendImg,[&](MatType::MT type,QImage img){
        if(type == MatType::MT::VideoStream){
            _mMainScreen->readimg(img);
        }else{
            addScreenShot(img);
        }
    });

    _mImgList = new ElaScrollArea(this);
    _mImgLWidget = new QWidget(this);
    _mImgList->setMinimumHeight(200);
    _mImgList->setMaximumHeight(200);

    _mImgLWidget->setMinimumHeight(190);
    _mImgList->setWidget(_mImgLWidget);
    _mImgList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _mImgList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 布局配置
    hb = new QHBoxLayout(_mImgLWidget);
    M_SceenShotWidget * tmp;
    for(int i = 0;i<SceenShotNum;i++){
        if(i!=0){
            tmp->SetNext(new M_SceenShotWidget(i,this));
            tmp = tmp->Next();
        }else{
            tmp = new M_SceenShotWidget(i,this);
        }
        tmp->SetList(&_imglist);
        tmp->setMinimumHeight(ScreenShotMaxHeight);
        tmp->setMinimumWidth(200);
        hb->addWidget(tmp);
        _mSSWlist.push_back(tmp);
    }
    hb->setMargin(0);
    hb->setSpacing(5);

    setTitle("home");
    // 竖向布局
    centerLayout->setContentsMargins(2, 2, 2, 2);
    centerLayout->insertWidget(0,_mMainScreen);
    centerLayout->insertWidget(1,_mImgList);
    centerLayout->setStretch(0,75);
    centerLayout->setStretch(1,25);
    // =============== UI ================

    _count = 0;
}

M_HomePage::~M_HomePage()
{

}

void M_HomePage::addScreenShot(QImage img)
{
    _count = ++_count%SceenShotNum;
    _imglist.push_front(img.copy());
    if(_imglist.count()>SceenShotNum)_imglist.pop_back();
    if(_mSSWlist.count()>0)_mSSWlist[0]->Update();
    _mImgLWidget->setMinimumWidth(SceenShotNum*(hb->spacing()+_mSSWlist[0]->minimumWidth()));
}

