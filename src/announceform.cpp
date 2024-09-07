#include "announceform.h"
#include "ui_announceform.h"

#include <QDate>
#include <QCloseEvent>
#include <QPlainTextEdit>

AnnounceForm::AnnounceForm(QWidget *parent, bool isHeadSys, bool isAdmin) :
    QWidget(parent),
    ui(new Ui::AnnounceForm)
{
    ui->setupUi(this);

    mIsAdmin=isAdmin;
    mIsHeadSys=isHeadSys;

    setWindowTitle("公告页面");

    //设置标签中文字显示位置
    ui->labContent->setAlignment(Qt::AlignCenter);
    ui->labAnnounceNumber->setAlignment(Qt::AlignLeft);
    ui->labAnnounceNumber->setFixedSize(30,20);
    ui->labType->setAlignment(Qt::AlignRight);

    //显示公告类型
    if(mIsHeadSys) ui->labType->setText("教务公告");

    setMinimumSize(600,400);
}

AnnounceForm::~AnnounceForm()
{
    delete ui;
}

void AnnounceForm::insertRecord(const QSqlRecord &record)
{
    mRecord = record;
    //执行插入时，时间使用数据库的当前随时间，公告序号不存在
    ui->labDate->setVisible(false);
    ui->dateEdit->setVisible(false);
    ui->labAnnounceNumber->setText("");
    ui->dateEdit->setDate(QDate::currentDate());
}

void AnnounceForm::showRecord(const QSqlRecord &record)
{
    mRecord=record;
    //只展示时任何控件都不能改变
    ui->dateEdit->setReadOnly(1);
    ui->nameLineEdit->setReadOnly(1);
    ui->phoneLineEdit->setReadOnly(1);
    ui->mailLineEdit->setReadOnly(1);
    ui->plainTextEdit->setReadOnly(1);
    ui->plainTextEdit->setFocusPolicy(Qt::NoFocus);


    updateControlTools();
}

void AnnounceForm::updateRecord(const QSqlRecord &record)
{
    mRecord=record;
    //编辑时不能改变发布时间
    ui->dateEdit->setReadOnly(1);

    updateControlTools();
}

void AnnounceForm::updateControlTools()
{
    QString number=mRecord.value("announcePhone").toString();
    QString name=mRecord.value("announceAuthor").toString();
    QString mail=mRecord.value("announceMailBox").toString();
    QString content=mRecord.value("announceContent").toString();
    QString id=mRecord.value("announceId").toString();
    QString date=mRecord.value("announceDate").toString();

    //设置控件
    ui->nameLineEdit->setText(name);
    ui->phoneLineEdit->setText(number);
    ui->mailLineEdit->setText(mail);
    ui->plainTextEdit->setPlainText(content);
    ui->labAnnounceNumber->setText(id);
    ui->dateEdit->setDate(QDate::fromString(date,"yyyy-MM-dd"));
}

void AnnounceForm::saveValueToRecord()
{
    QString number=ui->phoneLineEdit->text();
    QString name=ui->nameLineEdit->text();
    QString mail=ui->mailLineEdit->text();
    QString content=ui->plainTextEdit->toPlainText();
    int     type = mIsHeadSys;

    mRecord.setValue("announcePhone",number);
    mRecord.setValue("announceLinkman",name);
    mRecord.setValue("announceMailBox",mail);
    mRecord.setValue("announceContent",content);
    mRecord.setValue("announceType",type);
}

void AnnounceForm::on_pushButtonSave_clicked()
{
    if(mIsAdmin)
    {
        saveValueToRecord();
        emit accptSignal();
    }

    this->close();
}
