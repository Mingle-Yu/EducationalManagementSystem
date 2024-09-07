#include "smallchooseform.h"
#include "ui_smallchooseform.h"

#include "announceform.h"

#include <QDate>
#include <QTableView>
#include <QMessageBox>
#include <QSqlTableModel>


smallChooseForm::smallChooseForm(QWidget *parent, bool isAdmin) :
    QWidget(parent),
    ui(new Ui::smallChooseForm)
{
    ui->setupUi(this);

    mIsAdmin=isAdmin;

    //按身份设置增删改控件是否可用
    ui->groupBox->setVisible(mIsAdmin);
    ui->groupBox->setEnabled(mIsAdmin);

    ui->tabWidget->setCurrentIndex(0);

    adminModel=announce.getTableModel(this);
    adminModel->setFilter("announceType = 1");

    departModel=announce.getTableModel(this);
    departModel->setFilter("announceType = 0");


    ui->tableViewAdmin->setModel(adminModel);
    ui->tableViewDepart->setModel(departModel);

    //设置每个View都不能直接更改
    ui->tableViewAdmin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewDepart->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置每个View都隐藏类型列
    ui->tableViewAdmin->setColumnHidden(1,true);
    ui->tableViewDepart->setColumnHidden(1,true);

}

smallChooseForm::~smallChooseForm()
{
    delete ui;
}

void smallChooseForm::on_tableViewAdmin_doubleClicked(const QModelIndex &index)
{
    if(index.isValid()==false) return;

    //双击view，调用更改显示
    QSqlRecord record=adminModel->record(index.row());

    AnnounceForm *form=new AnnounceForm(0,1,mIsAdmin);
    form->show();
    form->setAttribute(Qt::WA_DeleteOnClose);

    if(mIsAdmin)    form->updateRecord(record);
    else form->showRecord(record);

    connect(form,&AnnounceForm::accptSignal,[=](){
        QSqlRecord record=form->getSingleRecord();
        announce.updateSingleRecord(record);
        adminModel->select();
    });


}

void smallChooseForm::on_tableViewDepart_doubleClicked(const QModelIndex &index)
{
    if(index.isValid()==false) return;

    //双击view，调用更改显示
    QSqlRecord record=departModel->record(index.row());

    AnnounceForm *form=new AnnounceForm(0,0,mIsAdmin);
    form->show();
    form->setAttribute(Qt::WA_DeleteOnClose);

    if(mIsAdmin)    form->updateRecord(record);
    else form->showRecord(record);

    connect(form,&AnnounceForm::accptSignal,[=](){
        QSqlRecord record=form->getSingleRecord();
        announce.updateSingleRecord(record);
        departModel->select();
    });

}

void smallChooseForm::on_cbxInterval_clicked(bool checked)
{
    //间隔显示
    ui->tableViewAdmin->setAlternatingRowColors(checked);
    ui->tableViewDepart->setAlternatingRowColors(checked);
}

void smallChooseForm::on_cbxDesOrder_clicked(bool checked)
{
    //按序号排序的方式
    if(checked)
    {
        adminModel->sort(0,Qt::DescendingOrder);
        departModel->sort(0,Qt::DescendingOrder);
    }
    else
    {
        adminModel->sort(0,Qt::AscendingOrder);
        departModel->sort(0,Qt::AscendingOrder);
    }
}

void smallChooseForm::on_cbxChangColWidth_clicked(bool checked)
{
    //设置列宽
    if(checked)
    {
        ui->tableViewAdmin->resizeColumnsToContents();
        ui->tableViewDepart->resizeColumnsToContents();
    }
    else
    {
        int col=adminModel->columnCount();

        for(int i=0;i<col;++i)
        {
            ui->tableViewAdmin->setColumnWidth(i,140);
            ui->tableViewDepart->setColumnWidth(i,140);
        }
    }
}

void smallChooseForm::on_pbtAddAnnounce_clicked()
{
    QSqlRecord record;

    //isHead判断当前页是不是教务公告，0是，1不是
    int isHead=ui->tabWidget->currentIndex();

    if(!isHead) record=adminModel->record();
    else record=departModel->record();

    AnnounceForm *form=new AnnounceForm(0,!isHead,mIsAdmin);
    form->show();
    form->setAttribute(Qt::WA_DeleteOnClose);
    form->insertRecord(record);

    //如果页面的accept被触发，将记录插入表中，然后重新读取表格
    connect(form,&AnnounceForm::accptSignal,[=](){
        QSqlRecord record=form->getSingleRecord();
        record.setValue("announceDate",QDate::currentDate().toString("yyyy-MM-dd"));
        announce.insertSingleRecord(record);
        if(!isHead) adminModel->select();
        else departModel->select();
    });
}

void smallChooseForm::on_pbtSubAnnounce_clicked()
{

    //isHead判断当前页是不是教务公告，0是，1不是
    int isHead=ui->tabWidget->currentIndex();

    QModelIndex index;
    QSqlRecord record;

    //读取view中的索引和记录
    if(!isHead) {
        index=ui->tableViewAdmin->currentIndex();
        record=adminModel->record(index.row());
    }
    else {
        index=ui->tableViewDepart->currentIndex();
        record=departModel->record(index.row());
    }

    if(index.isValid()==false) return;

    //询问是否删除公告
    int ret= QMessageBox::question(this,"删除公告","是否删除该条公告？",QMessageBox::Yes|QMessageBox::No);

    if(ret==QMessageBox::No) return;

    int id=record.value("announceId").toInt();
    announce.deleteSingleRecord(id);

    if(!isHead) adminModel->select();
    else departModel->select();
}

void smallChooseForm::on_updateAnnounce_clicked()
{
    //isHead判断当前页是不是教务公告，0是，1不是
    int isHead=ui->tabWidget->currentIndex();

    QModelIndex index;
    QSqlRecord record;

    //读取view中的索引和记录
    if(!isHead) {
        index=ui->tableViewAdmin->currentIndex();
        record=adminModel->record(index.row());
    }
    else {
        index=ui->tableViewDepart->currentIndex();
        record=adminModel->record(index.row());
    }

    //双击view，调用更改显示
    AnnounceForm *form=new AnnounceForm(0,!isHead,mIsAdmin);
    form->show();
    form->setAttribute(Qt::WA_DeleteOnClose);
    form->updateRecord(record);

    //如果页面的accept被触发，将记录插入表中，然后重新读取表格
    connect(form,&AnnounceForm::accptSignal,[=](){
        QSqlRecord record=form->getSingleRecord();
        announce.updateSingleRecord(record);
        if(!isHead) adminModel->select();
        else departModel->select();
    });

}

void smallChooseForm::on_tableViewAdmin_clicked(const QModelIndex &index)
{
    QString str=tr("当前索引为教务公告列表： %1 行 %2 列").arg(index.row()).arg(index.column());
    ui->labIndex->setText(str);
}

void smallChooseForm::on_tableViewDepart_clicked(const QModelIndex &index)
{
    QString str=tr("当前索引为院系公告列表： %1 行 %2 列").arg(index.row()).arg(index.column());
    ui->labIndex->setText(str);
}
