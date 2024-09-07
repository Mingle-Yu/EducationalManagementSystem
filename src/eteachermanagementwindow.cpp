#include "eteachermanagementwindow.h"
#include "ui_eteachermanagementwindow.h"

#include <QDebug>

ETeacherManagementWindow::ETeacherManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ETeacherManagementWindow)
{
    ui->setupUi(this);
    ui->lineEditSearch->setText("请输入评教记录编号");

    model = etsql.getRelationModel(this);
    ui->tableView->setModel(model);
    //设置关系
    MajorSql major; DepartmentSql depart;
    QString majorTableName=major.getTableName();
    QString dapartTableName=depart.getTableName();
    model->setRelation(5,QSqlRelation(majorTableName,"majorId","majorName"));
    model->setRelation(6,QSqlRelation(dapartTableName,"departmentId","departmentName"));

    model->select();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//    设置为只读
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//  单行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0,1);//隐藏序号
    selectionModel = ui->tableView->selectionModel();

    dialog4 = new AdminDialog4(this);
}

ETeacherManagementWindow::~ETeacherManagementWindow()
{
    delete ui;
}

void ETeacherManagementWindow::on_pushButtonAdd_clicked()
{
    int newId, rowCount = model->rowCount();
    if (rowCount == 0)
        newId = 1;
    else {
        QSqlRecord record = model->record(rowCount - 1);
        newId = record.value("evaluateId").toInt() + 1;
    }
    dialog4->initDialog1(newId, model);
    dialog4->open();
}


void ETeacherManagementWindow::on_pushButtonEdit_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QSqlRecord record = model->record(curRow);
        int id = record.value("evaluateId").toInt();
        dialog4->initDialog2(id, model);
        dialog4->open();
    }
}


void ETeacherManagementWindow::on_pushButtonDelete_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除选中的行吗?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            // 删除选中的行
            model->removeRow(curRow);

            // 提交变更到数据库
            model->submitAll();

            // 刷新视图
            model->select();
        }
    }
}

void ETeacherManagementWindow::on_pushButtonSearch_clicked()
{
    QSqlRecord record = etsql.findSingleRecord(ui->lineEditSearch->text().toInt());
    if (record.isNull("evaluateId")) {
        QMessageBox::information(this, "提示", "评教记录不存在");
        return;
    }
    dialog4->initDialog2(record.value("evaluateId").toInt(), model);
    dialog4->open();
}

