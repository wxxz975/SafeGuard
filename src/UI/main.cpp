#include <QApplication>

#include "ElaApplication.h"
#include "opencv2/opencv.hpp"

#include "m_mainpage.h"
#include "m_videocore.h"
#include "M_Def.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Ela 框架初始化
    ElaApplication::getInstance()->init();
    qRegisterMetaType<MatType::MT>("MatType::MT");

    M_VideoCore Core;
    // 主界面
    M_MainPage w(&Core);
    w.show();

    return a.exec();
}
