#include "announceshowwindow.h"
#include "ui_announceshowwindow.h"
#include <QMessageBox>


announceShowWindow::announceShowWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::announceShowWindow)
{
    ui->setupUi(this);

    ui->searchline->setReadOnly(false);
        model = announce.getTableModel(this);                               //显示公告表
        model->select();
        ui->announcetableView->setModel(model);

}

announceShowWindow::~announceShowWindow()
{
    delete ui;
}

void announceShowWindow::on_searchButton_clicked()
{
    QSqlRecord record = announce.findSingleRecord(ui->searchline->text().toInt());//搜索栏查找公告
    if(record.isNull("announceId"))
        QMessageBox::warning(this,"警告","该公告不存在！");
    else
    {
        model->setTable("announce"); // 设置你的表名
        model->setFilter(QString("announceId = %1").arg(ui->searchline->text().toInt())); // 设置过滤条件
        model->select(); // 执行查询
        ui->announcetableView->setModel(model); // 将模型设置到视图
    }
}
