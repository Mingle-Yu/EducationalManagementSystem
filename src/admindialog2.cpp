#include "admindialog2.h"
#include "ui_admindialog2.h"

#include <QValidator>

AdminDialog2::AdminDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog2)
{
    ui->setupUi(this);

    //设置年龄只能输入数字，且有上下限
    QIntValidator *valitor=new QIntValidator(15,140,this);
    ui->lineEditAge->setValidator(valitor);

    //读取专业
    MajorSql major;

    QSqlTableModel *majorModel=major.getTableModel(this);
    for(int i=0;i<majorModel->rowCount();++i)
    {
        QModelIndex index=majorModel->index(i,majorModel->fieldIndex("majorName"));
        QString name = majorModel->data(index,Qt::EditRole).toString();
        ui->comboBoxMajor->addItem(name);
    }

    //读取院系
    DepartmentSql depart;
    QSqlTableModel *departModel=depart.getTableModel(this);
    for(int i=0;i<departModel->rowCount();++i)
    {
        QModelIndex index=departModel->index(i,departModel->fieldIndex("departmentName"));
        QString name = departModel->data(index,Qt::EditRole).toString();
        ui->comboBoxDepartment->addItem(name);
    }

    //  设置只读
    ui->lineEditAccount->setReadOnly(true);
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->comboBoxDepartment->setEnabled(false);
    ui->comboBoxMajor->setEnabled(false);
    ui->lineEditSumScore->setEnabled(false);
}

AdminDialog2::~AdminDialog2()
{
    delete ui;
}

bool AdminDialog2::isValid()
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
    if (ui->lineEditSex->text().isEmpty()) {
        //        ui->lineEditSex->setText("性别不能为空");
        flag = false;
    }

    return flag;
}

void AdminDialog2::initDialog1(int id, QSqlTableModel *m)
{
    ui->lineEditAccount->clear();
    ui->lineEditPassword->clear();
    ui->lineEditName->clear();
    ui->lineEditSex->clear();
    ui->lineEditAge->clear();
    ui->comboBoxDepartment->clear();
    ui->comboBoxMajor->clear();
    ui->lineEditSumScore->clear();

    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->comboBoxDepartment->setEnabled(false);
    ui->comboBoxMajor->setEnabled(false);
    ui->lineEditSumScore->setReadOnly(true);

    //读取专业
    MajorSql major;

    QSqlTableModel *majorModel=major.getTableModel(this);
    for(int i=0;i<majorModel->rowCount();++i)
    {
        QModelIndex index=majorModel->index(i,majorModel->fieldIndex("majorName"));
        QString name = majorModel->data(index,Qt::EditRole).toString();
        ui->comboBoxMajor->addItem(name);
    }

    //读取院系
    DepartmentSql depart;
    QSqlTableModel *departModel=depart.getTableModel(this);
    for(int i=0;i<departModel->rowCount();++i)
    {
        QModelIndex index=departModel->index(i,departModel->fieldIndex("departmentName"));
        QString name = departModel->data(index,Qt::EditRole).toString();
        ui->comboBoxDepartment->addItem(name);
    }

    ui->lineEditAccount->setText(QString("%1").arg(id));
    studentId = id;
    model = m;
}

void AdminDialog2::initDialog2(int id, QSqlTableModel *m)
{
    ui->lineEditAccount->clear();
    ui->lineEditPassword->clear();
    ui->lineEditName->clear();
    ui->lineEditSex->clear();
    ui->lineEditAge->clear();
    ui->comboBoxDepartment->clear();
    ui->comboBoxMajor->clear();
    ui->lineEditSumScore->clear();

    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->comboBoxDepartment->setEnabled(false);
    ui->comboBoxMajor->setEnabled(false);
    ui->lineEditSumScore->setReadOnly(true);

    //读取专业
    MajorSql major;

    QSqlTableModel *majorModel=major.getTableModel(this);
    for(int i=0;i<majorModel->rowCount();++i)
    {
        QModelIndex index=majorModel->index(i,majorModel->fieldIndex("majorName"));
        QString name = majorModel->data(index,Qt::EditRole).toString();
        ui->comboBoxMajor->addItem(name);
    }

    //读取院系
    DepartmentSql depart;
    QSqlTableModel *departModel=depart.getTableModel(this);
    for(int i=0;i<departModel->rowCount();++i)
    {
        QModelIndex index=departModel->index(i,departModel->fieldIndex("departmentName"));
        QString name = departModel->data(index,Qt::EditRole).toString();
        ui->comboBoxDepartment->addItem(name);
    }


    studentId = id;
    model = m;
    QSqlRecord record = ssql.findSingleRecord(id);

    ui->lineEditAccount->setText(record.value("studentId").toString());
    ui->lineEditPassword->setText(record.value("studentPassword").toString());
    ui->lineEditName->setText(record.value("studentName").toString());
    ui->lineEditSex->setText(record.value("studentSex").toString());
    ui->lineEditAge->setText(record.value("studentAge").toString());
    ui->lineEditSumScore->setText(record.value("studentSumScore").toString());

    ui->comboBoxDepartment->setCurrentIndex(record.value("departmentId").toInt()-1);

    int majorId = record.value("majorId").toInt();
    QSqlRecord majorRecord = major.findSingleRecord(majorId);

    ui->comboBoxMajor->setCurrentText(majorRecord.value("majorName").toString());
}


void AdminDialog2::on_pushButtonEdit_clicked()
{
    ui->lineEditPassword->setReadOnly(false);
    ui->lineEditName->setReadOnly(false);
    ui->lineEditSex->setReadOnly(false);
    ui->lineEditAge->setReadOnly(false);
    ui->comboBoxDepartment->setEnabled(true);
    ui->comboBoxMajor->setEnabled(true);
    ui->lineEditSumScore->setReadOnly(false);
}


void AdminDialog2::on_pushButtonSave_clicked()
{
    if(ui->lineEditSex->text() != "男" && ui->lineEditSex->text()!="女")
    {

        QMessageBox::warning(this,"警告","性别设置有疑议");
        return;
    }

    if(ui->lineEditAge->text().toInt() < 15){

        QMessageBox::warning(this,"警告","年龄设置有疑议，最小不小于15岁");
        return;
    }


    if (isValid()) {
        QSqlRecord record = ssql.findSingleRecord(studentId);
        bool flag = record.isNull("studentId");
        record.setValue("studentId", ui->lineEditAccount->text().toInt());
        record.setValue("studentPassword", ui->lineEditPassword->text());
        record.setValue("studentName", ui->lineEditName->text());
        record.setValue("studentSex", ui->lineEditSex->text());
        record.setValue("studentAge", ui->lineEditAge->text().toInt());
        record.setValue("departmentId", ui->comboBoxDepartment->currentIndex() + 1);
        record.setValue("majorId", ui->comboBoxMajor->itemData(ui->comboBoxMajor->currentIndex()));
        record.setValue("studentSumScore", ui->lineEditSumScore->text().toInt());
        if (flag) { //  添加新账户
            ssql.insertSingleRecord(record);
        }
        else {  //  更新账户信息
            ssql.updateSingleRecord(record);
        }
        model->select();
        this->close();
//        QMessageBox::information(this, "提示", "已保存");
    }
    else {
        QMessageBox::information(this, "提示", "请填写必要信息");
    }
}


void AdminDialog2::on_comboBoxDepartment_currentIndexChanged(int index)
{
    int dapartId=index+1;

    ui->comboBoxMajor->clear();

    MajorSql major;

    QSqlTableModel *majorModel=major.getTableModel(this);
    for(int i=0;i<majorModel->rowCount();++i)
    {
        QModelIndex departIndex=majorModel->index(i,majorModel->fieldIndex("departmentId"));
        if(majorModel->data(departIndex,Qt::EditRole).toInt()==dapartId)
        {
            QModelIndex index=majorModel->index(i,majorModel->fieldIndex("majorName"));
            QString name = majorModel->data(index,Qt::EditRole).toString();

            ui->comboBoxMajor->addItem(name,i+1);
        }

    }
    
}


void AdminDialog2::on_comboBoxMajor_currentIndexChanged(int index)
{
    int majorId = index+1;

    MajorSql majorList;

    QSqlRecord record = majorList.findSingleRecord(majorId);

    ui->lineEditSumScore->setText(record.value("majorSum").toString());

}
