#include "teachermanagementwindow.h"
#include "ui_teachermanagementwindow.h"

TeacherManagementWindow::TeacherManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherManagementWindow)
{
    ui->setupUi(this);
    ui->lineEditSearch->setText("请输入教师账号");

    model = tsql.getRelationModel(this);

    //设置关系
    DepartmentSql depart;
    QString dapartTableName=depart.getTableName();
    model->setRelation(5,QSqlRelation(dapartTableName,"departmentId","departmentName"));
    model->select();
    ui->tableView->setModel(model);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//    设置为只读
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//  单行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    selectionModel = ui->tableView->selectionModel();

    dialog1 = new AdminDialog1(this);
}

TeacherManagementWindow::~TeacherManagementWindow()
{
    delete ui;
}

void TeacherManagementWindow::on_pushButtonAdd_clicked()
{
    int newId, rowCount = model->rowCount();
    if (rowCount == 0)
        newId = 1;
    else {
        QSqlRecord record = model->record(rowCount - 1);
        newId = record.value("teacherId").toInt() + 1;
    }
    dialog1->initDialog1(newId, model);
    dialog1->open();
}


void TeacherManagementWindow::on_pushButtonEdit_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QSqlRecord record = model->record(curRow);
        int id = record.value("teacherId").toInt();
        dialog1->initDialog2(id, model);
        dialog1->open();
    }
}


void TeacherManagementWindow::on_pushButtonDelete_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除选中的行吗?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            // 删除选中的行
            TeacherSql teacherList;
            int id = model->data(model->index(curRow,0),Qt::EditRole).toInt();
            teacherList.deleteSingleRecord(id);

            // 提交变更到数据库
            model->submitAll();

            // 刷新视图
            model->select();
        }
    }
}


void TeacherManagementWindow::on_pushButtonSearch_clicked()
{
    QSqlRecord record = tsql.findSingleRecord(ui->lineEditSearch->text().toInt());
    if (record.isNull("teacherId")) {
        QMessageBox::information(this, "提示", "教师账号不存在");
        return;
    }
    dialog1->initDialog2(record.value("teacherId").toInt(), model);
    dialog1->open();
}

