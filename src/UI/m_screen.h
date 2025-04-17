#ifndef M_SCREEN_H
#define M_SCREEN_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QImage>

class M_Screen : public QWidget
{
    Q_OBJECT
public:
    explicit M_Screen(QWidget *parent = nullptr);
signals:
    void sizechange(int w,int h);
public slots:
    void readImage(QImage);
private:
    bool eventFilter(QObject *watched, QEvent *event);

    QImage _buffer;
};

#endif // M_SCREEN_H
