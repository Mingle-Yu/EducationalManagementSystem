#include "studentmanagementwindow.h"
#include "ui_studentmanagementwindow.h"

StudentManagementWindow::StudentManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentManagementWindow)
{
    ui->setupUi(this);

    ui->lineEditSearch->setText("请输入学生账号");

    model = ssql.getRelationModel(this);
    //设置关系
    MajorSql major; DepartmentSql depart;
    QString majorTableName=major.getTableName();
    QString dapartTableName=depart.getTableName();
    model->setRelation(1,QSqlRelation(majorTableName,"majorId","majorName"));
    model->setRelation(2,QSqlRelation(dapartTableName,"departmentId","departmentName"));

    ui->tableView->setModel(model);
    model->select();

    //
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//    设置为只读
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//  单行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    selectionModel = ui->tableView->selectionModel();

    dialog2 = new AdminDialog2(this);
}

StudentManagementWindow::~StudentManagementWindow()
{
    delete ui;
}

void StudentManagementWindow::on_pushButtonAdd_clicked()
{
    int newId, rowCount = model->rowCount();
    if (rowCount == 0)
        newId = 1;
    else {
        QSqlRecord record = model->record(rowCount - 1);
        newId = record.value("studentId").toInt() + 1;
    }
    dialog2->initDialog1(newId, model);
    dialog2->open();
}


void StudentManagementWindow::on_pushButtonEdit_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QSqlRecord record = model->record(curRow);
        int id = record.value("studentId").toInt();
        dialog2->initDialog2(id, model);
        dialog2->open();
    }
}


void StudentManagementWindow::on_pushButtonDelete_clicked()
{
    int curRow = selectionModel->currentIndex().row();
    if (curRow != -1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除选中的行吗?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            // 删除选中的行
            StudentSql studentList;
            int id = model->data(model->index(curRow,0),Qt::EditRole).toInt();
            studentList.deleteSingleRecord(id);

            // 提交变更到数据库
            model->submitAll();

            // 刷新视图
            model->select();
        }
    }
}


void StudentManagementWindow::on_pushButtonSearch_clicked()
{
    QSqlRecord record = ssql.findSingleRecord(ui->lineEditSearch->text().toInt());
    if (record.isNull("studentId")) {
        QMessageBox::information(this, "提示", "学生账户不存在");
        return;
    }
    dialog2->initDialog2(record.value("studentId").toInt(), model);
    dialog2->open();
}

