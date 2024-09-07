//教师修改信息界面
#include "changewindow.h"
#include "ui_changewindow.h"

#include<QMessageBox>

ChangeWindow::ChangeWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeWindow),teacherId(id)
{
    ui->setupUi(this);

    //设置年龄只能输入数字，且有上下限
    QIntValidator *valitor=new QIntValidator(15,140,this);
    ui->lineEditAge->setValidator(valitor);

    //初始默认不可编辑
    ui->lineEditAccount->setEnabled(false);
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setEnabled(false);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditJobTitle->setEnabled(false);
    ui->lineEditPhone->setReadOnly(true);
    ui->lineEditMailBox->setReadOnly(true);
    ui->lineEditIntroduct->setReadOnly(true);

    //读取数据库中数据
    QSqlRecord record = teacher.findSingleRecord(teacherId);
    ui->lineEditAccount->setText(record.value("teacherId").toString());
    ui->lineEditPassword->setText(record.value("teacherPassword").toString());
    ui->lineEditName->setText(record.value("teacherName").toString());
    ui->lineEditSex->setText(record.value("teacherSex").toString());
    ui->lineEditAge->setText(record.value("teacherAge").toString());
    ui->lineEditJobTitle->setText(record.value("teacherJobTitle").toString());
    ui->lineEditPhone->setText(record.value("teacherPhoneNum").toString());
    ui->lineEditMailBox->setText(record.value("teacherMailBox").toString());
    ui->lineEditIntroduct->setText(record.value("teacherIntroduct").toString());
}

ChangeWindow::~ChangeWindow()
{
    delete ui;
}



void ChangeWindow::on_EditButton_clicked()
{
    //点击编辑按钮后可编辑信息
    ui->lineEditAccount->setReadOnly(true);
    ui->lineEditPassword->setReadOnly(false);
    ui->lineEditName->setReadOnly(false);
    ui->lineEditSex->setReadOnly(false);
    ui->lineEditAge->setReadOnly(false);
    ui->lineEditJobTitle->setReadOnly(false);
    ui->lineEditPhone->setReadOnly(false);
    ui->lineEditMailBox->setReadOnly(false);
    ui->lineEditIntroduct->setReadOnly(false);
}


void ChangeWindow::on_SaveButton_clicked()
{

    if(ui->lineEditAge->text().toInt()<15)
    {
        QMessageBox::warning(this,"警告","年龄设置有疑议，最小不小于15岁");
        return;
    }

    //保存后不可编辑
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditPhone->setReadOnly(true);
    ui->lineEditMailBox->setReadOnly(true);

    //刷新数据
    QSqlRecord record = teacher.getNullRecordModel();
    record.setValue("teacherId", ui->lineEditAccount->text().toInt());
    record.setValue("teacherPassword", ui->lineEditPassword->text());
    record.setValue("teacherName", ui->lineEditName->text());
    record.setValue("teacherSex", ui->lineEditSex->text());
    record.setValue("teacherAge", ui->lineEditAge->text().toInt());
    record.setValue("teacherJobTitle",ui->lineEditJobTitle->text());
    record.setValue("teacherPhoneNum", ui->lineEditPhone->text());
    record.setValue("teacherMailBox", ui->lineEditMailBox->text());
    record.setValue("teacherIntroduct",ui->lineEditIntroduct->text());
    teacher.updateSingleRecord(record);
    QMessageBox::information(nullptr, "提示", "已保存");
}

