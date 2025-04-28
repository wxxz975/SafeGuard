#ifndef M_SCREEN_H
#define M_SCREEN_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QImage>


//namespace cv {
//    class Mat;
//}

class M_Screen : public QWidget
{
    Q_OBJECT
public:
    explicit M_Screen(QWidget *parent = nullptr);

signals:
    void ScreenChange(int width,int height);
public slots:
    void readimg(QImage);
private:
    bool eventFilter(QObject *watched, QEvent *event);

    bool painterflage;
    QImage _painter_buffer;
};

#endif // M_SCREEN_H
