#include <QApplication>
#include "m_mainpage.h"
#include "ElaApplication.h"

#include "opencv2/opencv.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Ela 框架初始化
    ElaApplication::getInstance()->init();

    // 主界面
    M_MainPage w;
    w.show();

    return a.exec();
}
