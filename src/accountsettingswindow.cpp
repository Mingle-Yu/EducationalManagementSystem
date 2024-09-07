#include "accountsettingswindow.h"
#include "ui_accountsettingswindow.h"
#include <QMessageBox>

AccountSettingsWindow::AccountSettingsWindow(int Id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountSettingsWindow),
    adminId(Id)
{
    ui->setupUi(this);

    QIntValidator *valitor=new QIntValidator(15,140,this);
    ui->lineEditAge->setValidator(valitor);

    //  QLineEdit设置为只读
    ui->lineEditAccount->setEnabled(false); //  账户全程不能更改
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setEnabled(false);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditPhone->setReadOnly(true);
    ui->lineEditMailBox->setReadOnly(true);


    //  读取数据库，设置QLineEdit的内容
    QSqlRecord record = admin.findSingleRecord(adminId);
    ui->lineEditAccount->setText(record.value("adminId").toString());
    ui->lineEditPassword->setText(record.value("adminPassword").toString());
    ui->lineEditName->setText(record.value("adminName").toString());
    ui->lineEditSex->setText(record.value("adminSex").toString());
    ui->lineEditAge->setText(record.value("adminAge").toString());
    ui->lineEditPhone->setText(record.value("adminPhoneNum").toString());
    ui->lineEditMailBox->setText(record.value("adminMailBox").toString());
}

AccountSettingsWindow::~AccountSettingsWindow()
{
    delete ui;
}

void AccountSettingsWindow::on_pushButtonEdit_clicked()
{
    ui->lineEditPassword->setReadOnly(false);
    ui->lineEditName->setReadOnly(false);
    ui->lineEditSex->setReadOnly(false);
    ui->lineEditAge->setReadOnly(false);
    ui->lineEditPhone->setReadOnly(false);
    ui->lineEditMailBox->setReadOnly(false);
}


void AccountSettingsWindow::on_pushButtonSave_clicked()
{

    if(ui->lineEditSex->text() != "男" && ui->lineEditSex->text()!="女")
    {

        QMessageBox::warning(this,"警告","性别设置有疑议");
        return;
    }

    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditPhone->setReadOnly(true);
    ui->lineEditMailBox->setReadOnly(true);

    QSqlRecord record = admin.getNullRecordModel();
    record.setValue("adminId", ui->lineEditAccount->text().toInt());
    record.setValue("adminPassword", ui->lineEditPassword->text());
    record.setValue("adminName", ui->lineEditName->text());
    record.setValue("adminSex", ui->lineEditSex->text());
    record.setValue("adminAge", ui->lineEditAge->text().toInt());
    record.setValue("adminPhoneNum", ui->lineEditPhone->text());
    record.setValue("adminMailBox", ui->lineEditMailBox->text());
    admin.updateSingleRecord(record);
    QMessageBox::information(nullptr, "提示", "已保存");
}

