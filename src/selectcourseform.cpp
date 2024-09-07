#include "selectcourseform.h"
#include "ui_selectcourseform.h"

#include "courseform.h"
#include "sqlmodelall.h"
#include <QVBoxLayout>

SelectCourseForm::SelectCourseForm(QWidget *parent, int humanId, int isStudent) :
    QWidget(parent),
    ui(new Ui::SelectCourseForm)
{
    ui->setupUi(this);
    //0表示学生登录，1表示老师登录，2表示管理员登录
    mIsStudent = isStudent==0;
    mIsAdmin = isStudent==2;

    ui->rbtPreView->setChecked(1);
    ui->rbtAll->setChecked(1);

    if(mIsStudent) mStudenId=humanId;
    else mTeacherId=humanId;

    if(mIsStudent==false) {
        ui->groupBox_2->setVisible(false);
        ui->groupBox_2->setEnabled(false);
        ui->rbtPreView->setText("筛选学生列表");
        ui->rbtSelected->setText("选定列表");
    }

    //为了一开始调用setRecord函数时，一开始能取出widget才使用的
    QWidget *widget=new QWidget(this);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    ui->scrollArea->setWidget(widget);

    setRecord();
}

SelectCourseForm::~SelectCourseForm()
{
    delete ui;
}

QString SelectCourseForm::getStudentSqlstr()
{
    QString firstString;

    if(ui->rbtPreView->isChecked()){
        firstString=tr("SELECT * FROM course_table WHERE courseId NOT IN ( SELECT courseId FROM select_course_table where studentId=%1 and (selectStatus=2 or selectStatus=0)) and teacherId is not NULL ").arg(mStudenId);
    }
    else if(ui->rbtSelected->isChecked())
    {
        firstString=tr("SELECT * FROM select_course_table where studentId=%1 AND (selectStatus=2 OR selectStatus=0)").arg(mStudenId);
    }

    //已选界面返回选课记录就行
    if(ui->rbtSelected->isChecked()) return firstString;

    QString lastString;

    //先取得学生的专业编号
    StudentSql student;
    QSqlRecord record=student.findSingleRecord(mStudenId);
    int majorId=record.value("majorId").toInt();

    if(ui->rbtAll->isChecked()){
        lastString="";
    }
    else if(ui->rbtMyMajor->isChecked())
    {
        lastString=tr(" and majorId = %1 ").arg(majorId);
    }
    else if(ui->rbtPublic->isChecked()){

        lastString=tr(" and ( majorId != %1 or courseType=1) ").arg(majorId);
    }
    else if(ui->rbtOtherMajor){
        lastString=tr(" and majorId != %1 ").arg(majorId);
    }

    return firstString+lastString;
}

QString SelectCourseForm::getOtherSqlstr()
{
    QString firstString;

    if(ui->rbtPreView->isChecked()  && mIsAdmin){
        firstString=tr("SELECT * FROM select_course_table where selectStatus=0 ");
    }
    else if(ui->rbtPreView->isChecked() && !mIsAdmin){
        firstString=tr("SELECT * FROM select_course_table where selectStatus=0 and teacherId = %1").arg(mTeacherId);
    }
    else if(ui->rbtSelected->isChecked() && mIsAdmin)
    {
        firstString=tr("SELECT * FROM select_course_table where selectStatus=2 ");
    }
    else if(ui->rbtSelected->isChecked() && !mIsAdmin){
        firstString=tr("SELECT * FROM select_course_table where selectStatus=2 and teacherId=%1").arg(mTeacherId);
    }

    return firstString;
}

void SelectCourseForm::setRecord()
{
    //根据不同身份和选项设置语句
    QString sqlstr;
    if(mIsStudent) sqlstr=getStudentSqlstr();
    else sqlstr=getOtherSqlstr();


    //获得执行完语句之后的所有记录，学生返回课程记录，选课记录，
    SelectCourseSql select;
    CourseTableSql course;
    QSqlQuery query=select.getQueryList(sqlstr);


    //先清除原scrollArea里面的控件
    QWidget* widget=ui->scrollArea->widget();
    widget->close();
    //增加新的widget
    QWidget *newWidget=new QWidget(this);
    newWidget->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout *vLayout=new QVBoxLayout(newWidget);

    //确保第一条记录是有效的
    if(query.first())
    {
        do{
            QSqlRecord record=query.record();
            CourseForm *form;

            //当前是学生登录
            if(mIsStudent){
                //现在是选课界面，返回课程记录,否则返回选课记录
                if(ui->rbtPreView->isChecked()){
                    form=new CourseForm(0,1,mStudenId);
                    form->setCourseRecord(record);
                }
                else {
                    //现在是退课界面
                    form=new CourseForm(0,1,mStudenId);
                    form->setSelectRecord(record);
                }

            }
            else{
                //现在是选课界面
                if(ui->rbtPreView->isChecked()){
                    //不是学生登录返回的都是选课记录
                    int courseId=record.value("courseId").toInt();
                    QSqlRecord courseRecord=course.findSingleRecord(courseId);
                    form=new CourseForm();
                    form->setCourseRecord(courseRecord,record);
                }
                else{
                    //现在是已选界面
                    form=new CourseForm();
                    form->setSelectRecord(record);
                }
            }

            form->setAttribute(Qt::WA_DeleteOnClose);
            vLayout->addWidget(form);
        }while(query.next());
    }


    newWidget->setLayout(vLayout);
    ui->scrollArea->setWidget(newWidget);
}

void SelectCourseForm::on_rbtPreView_clicked()
{
    if(ui->rbtPreView->isChecked()){
        //进入选课界面
        if(mIsStudent){
            ui->groupBox_2->setVisible(true);
            ui->groupBox_2->setEnabled(true);
        }
            setRecord();
    }
}

void SelectCourseForm::on_rbtSelected_clicked()
{
    if(ui->rbtSelected->isChecked()){
        //进入已选界面
        if(mIsStudent){
            ui->groupBox_2->setVisible(false);
            ui->groupBox_2->setEnabled(false);
        }

        setRecord();
    }

}

void SelectCourseForm::on_rbtAll_clicked()
{
    if(ui->rbtAll->isChecked()){
            setRecord();
    }
}

void SelectCourseForm::on_rbtMyMajor_clicked()
{
        if(ui->rbtMyMajor->isChecked()){
            setRecord();
        }
}

void SelectCourseForm::on_rbtPublic_clicked()
{
    if(ui->rbtPublic->isChecked()){
            setRecord();
    }
}

void SelectCourseForm::on_rbtOtherMajor_clicked()
{
    if(ui->rbtOtherMajor->isChecked()){
            setRecord();
    }
}
