//教师成绩单界面
#include "scorewindow.h"
#include "ui_scorewindow.h"

#include<QMessageBox>

ScoreWindow::ScoreWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWindow),teacherId(id)
{
    ui->setupUi(this);

    model = score.getTableModel(this);                               //显示成绩表
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->scoretableView->setModel(model);
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::on_SaveButton_clicked()//老师提交学生成绩
{
    model->submitAll();
}


void ScoreWindow::on_searchButton_clicked()//查找学生
{
    QSqlRecord record = score.findSingleRecord(ui->searchlineEdit->text().toInt());//搜索栏查找公告
    if(record.isNull("studentId"))
        QMessageBox::warning(this,"警告","该学生不存在！");
    else
    {
        model->setTable("score"); // 设置你的表名
        model->setFilter(QString("studentId = %1").arg(ui->searchlineEdit->text().toInt())); // 设置过滤条件
        model->select(); // 执行查询
        ui->scoretableView->setModel(model); // 将模型设置到视图
    }
}

