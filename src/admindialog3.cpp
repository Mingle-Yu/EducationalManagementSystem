#include "admindialog3.h"
#include "ui_admindialog3.h"

#include <QCompleter>
#include <QIntValidator>
#include <QDoubleValidator>

#include <QDebug>

AdminDialog3::AdminDialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog3)
{
    ui->setupUi(this);

    //  设置只读

    nameList<<"公必"<<"公选"<<"专必"<<"专选";
    ui->comboBoxCouseType->addItems(nameList);
    ui->lineEditCourseId->setReadOnly(true);

    //设置三个只能输入数字
    QIntValidator *termValite=new QIntValidator(1,2,this);//学期
    ui->lineEditCourseTerm->setValidator(termValite);

    QIntValidator *hourValite=new QIntValidator(10,200,this);//学时
    ui->lineEditCourseHour->setValidator(hourValite);

    QIntValidator *personValite=new QIntValidator(1,9000,this);
    ui->lineEditHeadCount->setValidator(personValite);

    QIntValidator *peopleValite=new QIntValidator(1,9000,this);
    ui->lineEditSelectNum->setValidator(peopleValite);

    QDoubleValidator *scoreValite = new QDoubleValidator(0.5, 5, 1, this); // 学分
    scoreValite->setNotation(QDoubleValidator::StandardNotation); // 设置为标准表示法
    ui->lineEditCourseScore->setValidator(scoreValite);


    TeacherSql teacherList;
    QSqlTableModel *teacherModel=teacherList.getTableModel(this);
    QStringList idNames;
    for(int i=0;i<teacherModel->rowCount();++i)
    {
        QModelIndex index=teacherModel->index(i,0);
        QModelIndex nameIndex=teacherModel->index(i,teacherModel->fieldIndex("teacherName"));
        idNames<<teacherModel->data(index,Qt::EditRole).toString();
        mp.insert(teacherModel->data(index,Qt::EditRole).toString(),teacherModel->data(nameIndex,Qt::EditRole).toString());
    }

    QCompleter *compelter=new QCompleter(idNames,this);
    ui->lineEditTeacherId->setCompleter(compelter);

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

}

AdminDialog3::~AdminDialog3()
{
    delete ui;
}


void AdminDialog3::initDialog1(int id, QSqlTableModel *m)
{
    ui->lineEditTeacherId->clear();
    ui->lineEditTeacherName->clear();
    ui->lineEditCourseId->clear();
    ui->lineEditCourseName->clear();
    ui->lineEditCourseTerm->clear();
    ui->lineEditCourseScore->clear();
    ui->lineEditClassTime->clear();
    ui->lineEditClassLocal->clear();
    ui->lineEditHeadCount->clear();
    ui->lineEditSelectNum->clear();
    ui->lineEditCourseHour->clear();
    ui->dateEditBeginDate->setEnabled(false);
    ui->dateEditEndDate->setEnabled(false);


    ui->lineEditTeacherId->setReadOnly(true);
    ui->lineEditTeacherName->setReadOnly(true);
    ui->lineEditCourseId->setReadOnly(true);
    ui->lineEditCourseName->setReadOnly(true);
    ui->lineEditCourseTerm->setReadOnly(true);
    ui->lineEditCourseScore->setReadOnly(true);
    ui->lineEditClassTime->setReadOnly(true);
    ui->lineEditClassLocal->setReadOnly(true);
    ui->lineEditHeadCount->setReadOnly(true);
    ui->lineEditSelectNum->setReadOnly(true);
    ui->lineEditCourseHour->setReadOnly(true);

    ui->comboBoxCouseType->clear();
    ui->comboBoxCouseType->setEnabled(false);
    ui->comboBoxCouseType->addItems(nameList);

    ui->comboBoxDepartment->clear();
    ui->comboBoxMajor->clear();
    ui->comboBoxDepartment->setEnabled(false);
    ui->comboBoxMajor->setEnabled(false);
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


    ui->lineEditCourseId->setText(QString("%1").arg(id));
    courseId = id;
    model = m;
}

void AdminDialog3::initDialog2(int id, QSqlTableModel *m)
{
    ui->lineEditTeacherId->clear();
    ui->lineEditTeacherName->clear();
    ui->lineEditCourseId->clear();
    ui->lineEditCourseName->clear();
    ui->lineEditCourseTerm->clear();
    ui->lineEditClassTime->clear();
    ui->lineEditClassLocal->clear();
    ui->lineEditHeadCount->clear();
    ui->lineEditSelectNum->clear();
    ui->lineEditCourseHour->clear();

    ui->lineEditTeacherId->setReadOnly(true);
    ui->lineEditTeacherName->setReadOnly(true);
    ui->lineEditCourseId->setReadOnly(true);
    ui->lineEditCourseName->setReadOnly(true);
    ui->lineEditCourseTerm->setReadOnly(true);
    ui->lineEditCourseScore->setReadOnly(true);
    ui->lineEditClassTime->setReadOnly(true);
    ui->lineEditClassLocal->setReadOnly(true);
    ui->lineEditHeadCount->setReadOnly(true);
    ui->lineEditSelectNum->setReadOnly(true);
    ui->lineEditCourseHour->setReadOnly(true);
    ui->dateEditBeginDate->setEnabled(false);
    ui->dateEditEndDate->setEnabled(false);


    ui->comboBoxCouseType->clear();
    ui->comboBoxCouseType->addItems(nameList);

    ui->comboBoxDepartment->clear();
    ui->comboBoxMajor->clear();

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



    courseId = id;
    model = m;
    QSqlRecord record = csql.findSingleRecord(id);

    ui->lineEditTeacherId->setText(record.value("teacherId").toString());
    ui->lineEditTeacherName->setText(record.value("teacherName").toString());
    ui->lineEditCourseId->setText(record.value("courseId").toString());
    ui->lineEditCourseName->setText(record.value("courseName").toString());
    ui->lineEditCourseTerm->setText(record.value("courseTerm").toString());
    ui->lineEditCourseScore->setText(record.value("courseScore").toString());
    ui->dateEditBeginDate->setDate(QDate::fromString(record.value("courseBeginDate").toString(),"yyyy-MM-dd"));
    ui->dateEditEndDate->setDate(QDate::fromString(record.value("courseEndDate").toString(),"yyyy-MM-dd"));
    ui->lineEditClassTime->setText(record.value("courseClassTime").toString());
    ui->lineEditClassLocal->setText(record.value("placeOfClass").toString());
    ui->lineEditHeadCount->setText(record.value("courseMaxCount").toString());
    ui->lineEditSelectNum->setText(record.value("courseSelectNum").toString());
    ui->lineEditCourseHour->setText(record.value("courseHour").toString());

    ui->comboBoxCouseType->setCurrentIndex(record.value("courseType").toInt());
    ui->comboBoxDepartment->setCurrentIndex(record.value("departmentId").toInt()-1);

    int majorId = record.value("majorId").toInt();
    QSqlRecord majorRecord = major.findSingleRecord(majorId);

    ui->comboBoxMajor->setCurrentText(majorRecord.value("majorName").toString());


    ui->comboBoxDepartment->setEnabled(false);
    ui->comboBoxMajor->setEnabled(false);
    ui->comboBoxCouseType->setEnabled(false);

}

void AdminDialog3::on_pushButtonEdit_clicked()
{
    ui->lineEditTeacherId->setReadOnly(false);
    ui->lineEditTeacherName->setReadOnly(false);
    ui->lineEditCourseName->setReadOnly(false);
    ui->lineEditCourseTerm->setReadOnly(false);
    ui->lineEditCourseScore->setReadOnly(false);
    ui->lineEditClassTime->setReadOnly(false);
    ui->lineEditClassLocal->setReadOnly(false);
    ui->lineEditHeadCount->setReadOnly(false);
    ui->lineEditSelectNum->setReadOnly(false);
    ui->lineEditCourseHour->setReadOnly(false);
    ui->dateEditBeginDate->setEnabled(true);
    ui->dateEditEndDate->setEnabled(true);
    ui->comboBoxDepartment->setEnabled(true);
    ui->comboBoxMajor->setEnabled(true);
    ui->comboBoxCouseType->setEnabled(true);
}

void AdminDialog3::on_pushButtonSave_clicked()
{
    QDate beginDate=ui->dateEditBeginDate->date();
    QDate endDate=ui->dateEditEndDate->date();

    if(endDate < beginDate){
        QMessageBox::warning(this,"警告","开课时间晚于结课时间");
        return;
    }

    if(ui->lineEditCourseTerm->text().toInt() < 1 ){
        QMessageBox::warning(this,"警告","课程学期设置出错，请输入1 或 输入2");
        return;
    }

    if(ui->lineEditHeadCount->text().toInt() < ui->lineEditSelectNum->text().toInt()){
        QMessageBox::warning(this,"警告","课程人数小于选课人数，设置无效");
        return;
    }

    if(ui->lineEditCourseScore->text().toDouble()==0){
           QMessageBox::warning(this,"警告","课程学分设置无效");
           return;
    }

    QSqlRecord record = csql.findSingleRecord(courseId);
    bool flag = record.isNull("courseId");
    record.setValue("teacherId", ui->lineEditTeacherId->text().toInt());
    record.setValue("teacherName", ui->lineEditTeacherName->text());
    record.setValue("courseId", ui->lineEditCourseId->text().toInt());
    record.setValue("courseName", ui->lineEditCourseName->text());
    record.setValue("courseTerm", ui->lineEditCourseTerm->text().toInt());
    record.setValue("courseType", ui->comboBoxCouseType->currentIndex());
    record.setValue("courseScore", ui->lineEditCourseScore->text().toDouble());
    record.setValue("majorId", ui->comboBoxMajor->itemData(ui->comboBoxMajor->currentIndex()).toInt());
    record.setValue("courseBeginDate",beginDate.toString("yyyy-MM-dd"));
    record.setValue("courseEndDate",endDate.toString("yyyy-MM-dd"));
    record.setValue("courseClassTime", ui->lineEditClassTime->text());
    record.setValue("placeOfClass", ui->lineEditClassLocal->text());
    record.setValue("courseMaxCount", ui->lineEditHeadCount->text().toInt());
    record.setValue("courseSelectNum", ui->lineEditSelectNum->text().toInt());
    record.setValue("courseHour", ui->lineEditCourseHour->text().toInt());
    record.setValue("departmentId", ui->comboBoxDepartment->currentIndex()+1);

    if (flag) { //  添加新账户
        csql.insertSingleRecord(record);
    }
    else {  //  更新账户信息
        csql.updateSingleRecord(record);
    }
    model->select();
    this->close();
//    QMessageBox::information(this, "提示", "已保存");
}


void AdminDialog3::on_comboBoxDepartment_currentIndexChanged(int index)
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


void AdminDialog3::on_lineEditTeacherId_returnPressed()
{
    QString idName=ui->lineEditTeacherId->text();
    if(mp.count(idName)>0)
    {
        ui->lineEditTeacherName->setText(mp.value(idName));
    }
}

