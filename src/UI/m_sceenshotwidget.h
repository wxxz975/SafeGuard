#ifndef M_SCEENSHOTWIDGET_H
#define M_SCEENSHOTWIDGET_H

#include <QWidget>

class M_SceenShotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit M_SceenShotWidget(int index,QWidget *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event);
    void SetList(QVector<QImage>*);
    void SetNext(M_SceenShotWidget*);
    void Update();
    M_SceenShotWidget* Next(){return _next;}
signals:
private:
    int _index;
    QVector<QImage>* _list{nullptr};
    M_SceenShotWidget* _next{nullptr};
};

#endif // M_SCEENSHOTWIDGET_H
