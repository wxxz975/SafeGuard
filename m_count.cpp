#include "m_count.h"


#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStandardItemModel>
#include <QStandardItem>

#include "ElaWidget.h"
#include "ElaTableView.h"

M_Count::M_Count(QWidget *parent)
    : ElaScrollPage{parent}
{
    // =============== UI ================
    // Ela界面配置
    tables = new ElaTableView(this);
    QStandardItemModel*  model = new QStandardItemModel(0,2);
//    model->setRowCount(10);
    model->setHeaderData(0,Qt::Horizontal,"名称");
    model->setHeaderData(1,Qt::Horizontal,"数量");
    QStandardItem* nitem;
    QStandardItem* vitem;
    for(int i = 0;i<10;i++){
        nitem = new QStandardItem(QString("违禁品%1").arg(i));
        vitem = new QStandardItem("0");
        model->setItem(i,0,nitem);
        model->setItem(i,1,vitem);
    }
    tables->setModel(model);


    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("统计页面");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addWidget(tables);
    centerLayout->addStretch();
    addCentralWidget(centralWidget);
    // =============== UI ================
}
