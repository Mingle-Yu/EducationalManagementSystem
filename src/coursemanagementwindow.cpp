#include "coursemanagementwindow.h"
#include "ui_coursemanagementwindow.h"

#include <QDebug>
CourseManagementWindow::CourseManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseManagementWindow)
{
    ui->setupUi(this);
    ui->lineEditSearch->setText("请输入课程编号");

    model = csql.getRelationModel(this);

    //设置关系
    MajorSql major; DepartmentSql depart;
    QString majorTableName=major.getTableName();
    QString dapartTableName=depart.getTableName();
    model->setRelation(2,QSqlRelation(majorTableName,"majorId","majorName"));
    model->setRelation(3,QSqlRelation(dapartTableName,"departmentId","departmentName"));

    ui->tableView->setModel(model);
    model->select();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//    设置为只读
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//  单行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //隐藏课程类型
    ui->tableView->setColumnHidden(5,1);
    selectionModel = ui->tableView->selectionModel();

    dialog3 = new AdminDialog3(this);
}

CourseManagementWindow::~CourseManagementWindow()
{
    delete ui;
}

void CourseManagementWindow::on_pushButtonAdd_clicked()
{
    int newId, rowCount = model->rowCount();
    if (rowCount == 0)
        newId = 1;
    else {
        QSqlRecord record = model->record(rowCount - 1);
        newId = record.value("courseId").toInt() + 1;
    }
    dialog3->initDialog1(newId, model);
    dialog3->open();
}

void CourseManagementWindow::on_pushButtonEdit_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QSqlRecord record = model->record(curRow);
        int id = record.value("courseId").toInt();
        qDebug() << id;
        dialog3->initDialog2(id, model);
        dialog3->open();
    }
}

void CourseManagementWindow::on_pushButtonDelete_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除选中的行吗?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            // 删除选中的行
            CourseTableSql courseList;
            int id = model->data(model->index(curRow,0),Qt::EditRole).toInt();
            courseList.deleteSingleRecord(id);

            // 提交变更到数据库
            model->submitAll();

            // 刷新视图
            model->select();
        }
    }
}


void CourseManagementWindow::on_pushButtonSearch_clicked()
{
    QSqlRecord record = csql.findSingleRecord(ui->lineEditSearch->text().toInt());
    if (record.isNull("courseId")) {
        QMessageBox::information(this, "提示", "课程不存在");
        return;
    }
    dialog3->initDialog2(record.value("courseId").toInt(), model);
    dialog3->open();
}




