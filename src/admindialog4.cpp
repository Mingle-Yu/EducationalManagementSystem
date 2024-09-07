#include "admindialog4.h"
#include "ui_admindialog4.h"

AdminDialog4::AdminDialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog4)
{
    ui->setupUi(this);

    ui->lineEditEvaluateId->setReadOnly(true);
}

AdminDialog4::~AdminDialog4()
{
    delete ui;
}

void AdminDialog4::initDialog1(int id, QSqlTableModel *m)
{
    ui->lineEditEvaluateId->clear();
    ui->lineEditStudentId->clear();
    ui->lineEditCourseId->clear();
    ui->lineEditCourseTerm->clear();
    ui->lineEditTeacherId->clear();
    ui->lineEditCourseName->clear();
    ui->lineEditStatus->clear();
    ui->lineEditContent->clear();
    ui->lineEditMethod->clear();
    ui->lineEditEffect->clear();
    ui->lineEditSumScore->clear();

    ui->lineEditEvaluateId->setReadOnly(true);
    ui->lineEditStudentId->setReadOnly(true);
    ui->lineEditCourseId->setReadOnly(true);
    ui->lineEditCourseTerm->setReadOnly(true);
    ui->lineEditTeacherId->setReadOnly(true);
    ui->lineEditCourseName->setReadOnly(true);
    ui->lineEditStatus->setReadOnly(true);
    ui->lineEditContent->setReadOnly(true);
    ui->lineEditMethod->setReadOnly(true);
    ui->lineEditEffect->setReadOnly(true);
    ui->lineEditSumScore->setReadOnly(true);


    ui->lineEditEvaluateId->setText(QString("%1").arg(id));
    evaluateId = id;
    model = m;
}

void AdminDialog4::initDialog2(int id, QSqlTableModel *m)
{
    ui->lineEditEvaluateId->clear();
    ui->lineEditStudentId->clear();
    ui->lineEditCourseId->clear();
    ui->lineEditCourseTerm->clear();
    ui->lineEditTeacherId->clear();
    ui->lineEditCourseName->clear();
    ui->lineEditStatus->clear();
    ui->lineEditContent->clear();
    ui->lineEditMethod->clear();
    ui->lineEditEffect->clear();
    ui->lineEditSumScore->clear();

    ui->lineEditEvaluateId->setReadOnly(true);
    ui->lineEditStudentId->setReadOnly(true);
    ui->lineEditCourseId->setReadOnly(true);
    ui->lineEditCourseTerm->setReadOnly(true);
    ui->lineEditTeacherId->setReadOnly(true);
    ui->lineEditCourseName->setReadOnly(true);
    ui->lineEditStatus->setReadOnly(true);
    ui->lineEditContent->setReadOnly(true);
    ui->lineEditMethod->setReadOnly(true);
    ui->lineEditEffect->setReadOnly(true);
    ui->lineEditSumScore->setReadOnly(true);

    evaluateId = id;
    model = m;
    QSqlRecord record = etsql.findSingleRecord(id);

    ui->lineEditEvaluateId->setText(record.value("evaluateId").toString());
    ui->lineEditStudentId->setText(record.value("studentId").toString());
    ui->lineEditCourseId->setText(record.value("courseId").toString());
    ui->lineEditCourseTerm->setText(record.value("courseTerm").toString());
    ui->lineEditTeacherId->setText(record.value("teacherId").toString());
    ui->lineEditCourseName->setText(record.value("courseName").toString());
    ui->lineEditStatus->setText(record.value("evaluateStatus").toString());
    ui->lineEditContent->setText(record.value("evaluateContent").toString());
    ui->lineEditMethod->setText(record.value("evaluateMethod").toString());
    ui->lineEditEffect->setText(record.value("evaluateEffect").toString());
    ui->lineEditSumScore->setText(record.value("sumScore").toString());
}

void AdminDialog4::on_pushButtonEdit_clicked()
{
    ui->lineEditStudentId->setReadOnly(false);
    ui->lineEditCourseId->setReadOnly(false);
    ui->lineEditCourseTerm->setReadOnly(false);
    ui->lineEditTeacherId->setReadOnly(false);
    ui->lineEditCourseName->setReadOnly(false);
    ui->lineEditStatus->setReadOnly(false);
    ui->lineEditContent->setReadOnly(false);
    ui->lineEditMethod->setReadOnly(false);
    ui->lineEditEffect->setReadOnly(false);
    ui->lineEditSumScore->setReadOnly(false);
}


void AdminDialog4::on_pushButtonSave_clicked()
{
    QSqlRecord record = etsql.findSingleRecord(evaluateId);
    bool flag = record.isNull("evaluateId");
    record.setValue("evaluateId", ui->lineEditEvaluateId->text().toInt());
    record.setValue("studentId", ui->lineEditStudentId->text().toInt());
    record.setValue("courseId", ui->lineEditCourseId->text().toInt());
    record.setValue("courseTerm", ui->lineEditCourseTerm->text().toInt());
    record.setValue("teacherId", ui->lineEditTeacherId->text().toFloat());
    record.setValue("courseName", ui->lineEditCourseName->text());
    record.setValue("evaluateStatus", ui->lineEditStatus->text().toInt());
    record.setValue("evaluateContent", ui->lineEditContent->text().toInt());
    record.setValue("evaluateMethod", ui->lineEditMethod->text().toInt());
    record.setValue("evaluateEffect", ui->lineEditEffect->text().toInt());
    record.setValue("sumScore", ui->lineEditSumScore->text().toInt());

    if (flag) { //  添加新账户
        etsql.insertSingleRecord(record);
    }
    else {  //  更新账户信息
        etsql.updateSingleRecord(record);
    }
    model->select();
    this->close();
//    QMessageBox::information(this, "提示", "已保存");
}

