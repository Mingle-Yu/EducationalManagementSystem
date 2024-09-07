#include "courseform.h"
#include "ui_courseform.h"

#include "sqlmodelall.h"
#include <QPalette>

CourseForm::CourseForm(QWidget *parent, int identity, int studentId) :
    QWidget(parent),
    ui(new Ui::CourseForm)
{
    ui->setupUi(this);

    setMaximumHeight(ui->groupBox->maximumHeight());
    setMinimumHeight(ui->groupBox->minimumHeight());

    ui->labPicutre->setPixmap(QPixmap(":/Image/my photos/begin.png").scaled(ui->labPicutre->rect().size()));
    ui->labCourseName->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    mIsStduent=identity;
    mStudentId=studentId;

    //2选课成功 1退选 0待筛选 -1选课失败
    if(mIsStduent) ui->pbtYes->setText("选课");
    else    ui->pbtYes->setText("选定该生");

}

CourseForm::~CourseForm()
{
    delete ui;
    qDebug("ddd");
}

void CourseForm::setCourseRecord(const QSqlRecord &record)
{
    //记录课程信息
    courseRecord=record;
    //读取课程记录中所有信息输入到控件页面
    QString name=record.value("courseName").toString();
    QString score=record.value("courseScore").toString();
    QString teacher=record.value("teacherName").toString();

    int departId=record.value("departmentId").toInt();
    DepartmentSql department;
    QString depart=department.findSingleRecord(departId).value("departmentName").toString();

    QString workDay=record.value("courseClassTime").toString();
    QString endDay=record.value("courseEndDate").toString();
    QString num=record.value("courseSelectNum").toString()
                +"/"+record.value("courseMaxCount").toString();

    int type=record.value("courseType").toInt();
    QString typeName;
    if(type==0) typeName="公必";
    else if(type==1) typeName="公选";
    else if(type==2) typeName="专必";
    else typeName="专选";

    //***********************************************//
    ui->tlbType->setText("课程类型："+typeName);
    ui->tlbDepart->setText("单位："+depart);
    ui->tlbScore->setText("学分"+score);
    ui->tlbFinalDate->setText("结课时间"+endDay);
    ui->labCourseName->setText(name);
    ui->labWork->setText("教师："+teacher + " 上课时间："+workDay);
    ui->labNum->setText("选课人数"+num);
}

void CourseForm::setCourseRecord(const QSqlRecord &record, const QSqlRecord &select)
{
    //非学生的选课界面
    selectRecord=select;
    setCourseRecord(record);

    ui->labWork->setText("学生学号：" + selectRecord.value("studentId").toString());

    int status=record.value("selectStatus").toInt();
    ui->labStatus->setAlignment(Qt::AlignCenter);
    //为0表示待筛选，1选课成功
    if(!status)
        ui->labStatus->setText("待筛选");

    //设置状态显示的背景颜色
    QPalette pl = ui->labStatus->palette();
    pl.setColor(QPalette::Window, Qt::yellow); // Set background color to red
    ui->labStatus->setAutoFillBackground(true);
    ui->labStatus->setPalette(pl);
}

void CourseForm::setSelectRecord(const QSqlRecord &record)
{
    //所有人的退课界面
    selectRecord=record;

    //已选课程页面才利用该函数，当前页面为已选页面,且已存在记录
    int courseId=record.value("courseId").toInt();
    CourseTableSql course;
    setCourseRecord(course.findSingleRecord(courseId));

    //根据老师和学生设定不同的按钮显示，如果是学生
    if(mIsStduent)
    {
        ui->pbtYes->setText("退课");
        int status=record.value("selectStatus").toInt();
        ui->labStatus->setAlignment(Qt::AlignCenter);
        QPalette pl = ui->labStatus->palette();
        pl.setColor(QPalette::Window, Qt::yellow); // Set background color to red
        ui->labStatus->setAutoFillBackground(true);
        ui->labStatus->setPalette(pl);

       //为0表示待筛选，1选课成功
       if(!status)
           ui->labStatus->setText("待筛选");
       else if(status==2)
           ui->labStatus->setText("选课成功");
        else
           ui->labStatus->setText("");

    }
    else
    {
        ui->labStatus->setAlignment(Qt::AlignCenter);
        ui->labStatus->setStyleSheet("QLabel:{background-color: rgb(85, 255, 255); color: rgb(0, 0, 0);}");

        ui->pbtYes->setText("淘汰该生");
        ui->labStatus->setText("已选定");
        ui->labWork->setText("学生学号：" + selectRecord.value("studentId").toString());
        QPalette pl = ui->labStatus->palette();
        pl.setColor(QPalette::Window, Qt::yellow); // Set background color to red
        ui->labStatus->setAutoFillBackground(true);
        ui->labStatus->setPalette(pl);
    }

}

void CourseForm::inPreViewPage()
{
    //学生选课界面只需要传课程信息就可以
    SelectCourseSql select;

    int courseID=courseRecord.value("courseId").toInt();
    int courseTerm=courseRecord.value("courseTerm").toInt();
    int teacherID=courseRecord.value("teacherId").toInt();

    QSqlRecord record;
    QString sqlstr=tr(" select * from select_course_table where courseId=%1 and courseTerm=%2 and teacherId=%3 and studentId=%4").arg(courseID).arg(courseTerm).arg(teacherID).arg(mStudentId);
    QSqlQuery query=select.getQueryList(sqlstr);

    //已存在学生的选课记录
    if(query.first()) {
        record=query.record();
        record.setValue("selectStatus",0);
        select.updateSingleRecord(record);
        return;
    }

    //不存在该学生的选课记录
    record=select.getNullRecordModel();
    QString name=courseRecord.value("courseName").toString();
    record.setValue("courseId",courseID);
    record.setValue("courseTerm",courseTerm);
    record.setValue("teacherId",teacherID);
    record.setValue("studentId",mStudentId);
    record.setValue("selectStatus",0);
    record.setValue("courseName",name);
    record.setValue("majorId",courseRecord.value("majorId").toInt());
    record.setValue("departmentId",courseRecord.value("departmentId").toInt());
    select.insertSingleRecord(record);
}

void CourseForm::on_pbtYes_clicked()
{
    CourseTableSql courseTable;
    int num=courseRecord.value("courseSelectNum").toInt();
    int maxNum=courseRecord.value("courseMaxCount").toInt();

    if(mIsStduent)
    {
        if(ui->pbtYes->text()=="选课"){
            //没满才可以添加
            if(num<maxNum){
                inPreViewPage();
                courseRecord.setValue("courseSelectNum",num+1);
                courseTable.updateSingleRecord(courseRecord);
            }
        }
        else{
            //退选
            selectRecord.setValue("selectStatus",1);
            SelectCourseSql select;
            select.updateSingleRecord(selectRecord);

            //是从选课成功到退选，选课人数减一
            courseRecord.setValue("courseSelectNum",num-1);
            courseTable.updateSingleRecord(courseRecord);

        }

        this->close();
    }
    //不是学生
    else
    {
        SelectCourseSql select;

        //选择该生，则变为2，淘汰该生再变为0
        if(ui->pbtYes->text()=="选定该生"){
            selectRecord.setValue("selectStatus",2);
            select.updateSingleRecord(selectRecord);
        }
        else{

            selectRecord.setValue("selectStatus",0);
            select.updateSingleRecord(selectRecord);
        }

        this->close();
    }
}
