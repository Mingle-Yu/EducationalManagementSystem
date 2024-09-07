#include "admindialog1.h"
#include "ui_admindialog1.h"

#include <QIntValidator>

AdminDialog1::AdminDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog1)
{
    ui->setupUi(this);

    //设置年龄只能输入数字，且有上下限
    QIntValidator *valitor=new QIntValidator(15,140,this);
    ui->lineEditAge->setValidator(valitor);

    addItemsToCombox();
    clearAllWidget();

}

AdminDialog1::~AdminDialog1()
{
    delete ui;
}

bool AdminDialog1::isValid()
{
    bool flag = true;
    if (ui->lineEditPassword->text().isEmpty()) {
//        ui->lineEditPassword->setText("密码不能为空");
        flag = false;
    }
    if (ui->lineEditName->text().isEmpty()) {
//        ui->lineEditName->setText("姓名不能为空");
        flag =false;
    }
    if (ui->lineEditAge->text().isEmpty()) {
//        ui->lineEditAge->setText("年龄不能为空");
        flag = false;
    }
    if (ui->lineEditPhone->text().isEmpty()) {
//        ui->lineEditPhone->setText("电话不能为空");
        flag = false;
    }

    int age=ui->lineEditAge->text().toInt();
    if(age<15)
    {
        flag=false;
        QMessageBox::warning(this,"警告","年龄设置有疑议，最小不小于15岁");
    }

    return flag;
}

void AdminDialog1::initDialog1(int id, QSqlTableModel* m)
{
    clearAllWidget();

    addItemsToCombox();

    ui->lineEditAccount->setText(QString("%1").arg(id));
    teacherId = id;
    model = m;
}

void AdminDialog1::initDialog2(int id, QSqlTableModel *m)
{

    clearAllWidget();

    addItemsToCombox();

    teacherId = id;
    model = m;
    QSqlRecord record = tsql.findSingleRecord(id);

    //设置显示院系对应
    int departId=record.value("departmentId").toInt();
    ui->comboBoxDepartment->setCurrentIndex(departId-1);

    //设置性别
    QString sex = record.value("teacherSex").toString();
    if(sex=="男") ui->comboBoxSex->setCurrentText("男");
    else ui->comboBoxSex->setCurrentText("女");

    //设置职称
    QString jobTitle = record.value("teacherJobTitle").toString();
    if(jobTitle=="助教") ui->comboBoxJobTitle->setCurrentText("助教");
    else if(jobTitle=="讲师")   ui->comboBoxJobTitle->setCurrentText("讲师");
    else if(jobTitle=="副教授")   ui->comboBoxJobTitle->setCurrentText("副教授");
    else ui->comboBoxJobTitle->setCurrentText("教授");

    ui->lineEditAccount->setText(record.value("teacherId").toString());
    ui->lineEditPassword->setText(record.value("teacherPassword").toString());
    ui->lineEditName->setText(record.value("teacherName").toString());
    ui->lineEditAge->setText(record.value("teacherAge").toString());
    ui->lineEditPhone->setText(record.value("teacherPhoneNum").toString());
    ui->lineEditMail->setText(record.value("teacherMailBox").toString());
    ui->plainTextEditIntroduction->setPlainText(record.value("teacherIntroduction").toString());
}

void AdminDialog1::on_pushButtonEdit_clicked()
{
    ui->lineEditPassword->setReadOnly(false);
    ui->lineEditName->setReadOnly(false);
    ui->comboBoxSex->setEnabled(true);
    ui->lineEditAge->setReadOnly(false);
    ui->comboBoxJobTitle->setEnabled(true);
    ui->lineEditPhone->setReadOnly(false);
    ui->lineEditMail->setReadOnly(false);
    ui->plainTextEditIntroduction->setReadOnly(false);
    ui->comboBoxDepartment->setEnabled(true);
}


void AdminDialog1::on_pushButtonSave_clicked()
{
    if (isValid()) {
        QSqlRecord record = tsql.findSingleRecord(teacherId);
        bool flag = record.isNull("teacherId");
        record.setValue("teacherId", ui->lineEditAccount->text().toInt());
        record.setValue("teacherPassword", ui->lineEditPassword->text());
        record.setValue("teacherName", ui->lineEditName->text());
        record.setValue("teacherSex", ui->comboBoxSex->currentText());
        record.setValue("teacherAge", ui->lineEditAge->text().toInt());
        record.setValue("teacherJobTitle", ui->comboBoxJobTitle->currentText());
        record.setValue("teacherPhoneNum", ui->lineEditPhone->text());
        record.setValue("teacherMailBox", ui->lineEditMail->text());
        record.setValue("teacherIntroduction", ui->plainTextEditIntroduction->toPlainText());
        record.setValue("departmentId",ui->comboBoxDepartment->currentIndex()+1);
        if (flag) { //  添加新账户
            tsql.insertSingleRecord(record);
        }
        else {  //  更新账户信息
            tsql.updateSingleRecord(record);
        }
        model->select();
        this->close();
//        QMessageBox::information(this, "提示", "已保存");
    }
    else {
        QMessageBox::information(this, "提示", "请填写必要信息");
    }
}

void AdminDialog1::addItemsToCombox()
{
    //输入院系
    DepartmentSql depart;
    QSqlTableModel *departModel=depart.getTableModel(this);
    for(int i=0;i<departModel->rowCount();++i)
    {
        QModelIndex index=departModel->index(i,departModel->fieldIndex("departmentName"));
        QString name = departModel->data(index,Qt::EditRole).toString();
        ui->comboBoxDepartment->addItem(name);
    }


    //输入性别
    ui->comboBoxSex->addItem("男");
    ui->comboBoxSex->addItem("女");

    //输入职称
    ui->comboBoxJobTitle->addItem("助教");
    ui->comboBoxJobTitle->addItem("讲师");
    ui->comboBoxJobTitle->addItem("副教授");
    ui->comboBoxJobTitle->addItem("教授");
}

void AdminDialog1::clearAllWidget()
{
    ui->lineEditAccount->clear();
    ui->lineEditPassword->clear();
    ui->lineEditName->clear();
    ui->comboBoxSex->clear();
    ui->lineEditAge->clear();
    ui->comboBoxJobTitle->clear();
    ui->lineEditPhone->clear();
    ui->lineEditMail->clear();
    ui->plainTextEditIntroduction->clear();
    ui->comboBoxDepartment->clear();
    ui->comboBoxJobTitle->clear();
    ui->comboBoxSex->clear();

    //  设置只读
    ui->lineEditAccount->setReadOnly(true);
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditPhone->setReadOnly(true);
    ui->lineEditMail->setReadOnly(true);
    ui->plainTextEditIntroduction->setReadOnly(true);

    //设置comBox无法使用
    ui->comboBoxSex->setEnabled(false);
    ui->comboBoxJobTitle->setEnabled(false);
    ui->comboBoxDepartment->setEnabled(false);
}

