//学生修改信息界面
#include "stu_changewindow.h"
#include "qsqlrecord.h"
#include "ui_stu_changewindow.h"

#include<QMessageBox>
#include "sqlmodelall.h"

stu_ChangeWindow::stu_ChangeWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_ChangeWindow),studentId(id)
{
    ui->setupUi(this);
    //设置年龄只能输入数字，且有上下限
    QIntValidator *valitor=new QIntValidator(15,140,this);
    ui->lineEditAge->setValidator(valitor);

    //初始不可编辑
    ui->lineEditPassword->setReadOnly(true);
    ui->lineEditName->setReadOnly(true);
    ui->lineEditSex->setReadOnly(true);
    ui->lineEditAge->setReadOnly(true);
    ui->lineEditSumScore->setReadOnly(true);
    ui->lineEditMajorId->setReadOnly(true);


    //读取数据
    QSqlRecord record = student.findSingleRecord(studentId);
    ui->lineEditAccount->setText(record.value("studentId").toString());
    ui->lineEditPassword->setText(record.value("studentPassword").toString());
    ui->lineEditName->setText(record.value("studentName").toString());
    ui->lineEditSex->setText(record.value("studentSex").toString());
    ui->lineEditAge->setText(record.value("studentAge").toString());

    //通过专业编号找到专业名称
    int majorId = record.value("majorId").toInt();
    MajorSql major;
    QString majorName = major.findSingleRecord(majorId).value("majorName").toString();
    ui->lineEditMajorId->setText(majorName);
    ui->lineEditMajorId->setEnabled(false);

    //计算学生成绩表中通过后的总学分
    ScoreSql list;
    QString tableName=list.getTableName();
    QSqlQuery query=list.getQueryList(tr(" select * from %1 where studentId = %2 and studentPass = 1 ").arg(tableName).arg(studentId));

    int sum=0;//总学分
    //计算有成绩的课程的学分
    if(query.first())
    {
        CourseTableSql courseList;

        do{
            QSqlRecord newRecord=query.record();
            int courseId = newRecord.value("courseId").toInt();

            //通过课程ID得知课程学分
            int num = courseList.findSingleRecord(courseId).value("courseScore").toInt();
            sum+=num;
        }while(query.next());

        int nowSum=record.value("studentSumScore").toInt();

        //总学分发生变化才更新
        if(record.value("studentSumScore").isNull() || nowSum!=sum)
        {
            record.setValue("studentSumScore",sum);
            student.updateSingleRecord(record);
        }
    }

    ui->lineEditSumScore->setText(QString::number(sum));
    ui->lineEditSumScore->setEnabled(false);
    ui->lineEditAccount->setEnabled(false);
}

stu_ChangeWindow::~stu_ChangeWindow()
{
    delete ui;
}

void stu_ChangeWindow::on_pushButtonEdit_clicked()
{
    //按编辑按钮之后可编辑
    ui->lineEditPassword->setReadOnly(false);
    ui->lineEditName->setReadOnly(false);
    ui->lineEditSex->setReadOnly(false);
    ui->lineEditAge->setReadOnly(false);
}


void stu_ChangeWindow::on_pushButtonSave_clicked()
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

    //刷新数据
    QSqlRecord record = student.getNullRecordModel();
    record.setValue("studentId", ui->lineEditAccount->text().toInt());
    record.setValue("studentPassword", ui->lineEditPassword->text());
    record.setValue("studentName", ui->lineEditName->text());
    record.setValue("studentSex", ui->lineEditSex->text());
    record.setValue("studentAge", ui->lineEditAge->text().toInt());
    record.setValue("studentMajorId",ui->lineEditMajorId->text());
    record.setValue("studentSumScore",ui->lineEditSumScore->text().toInt());

    student.updateSingleRecord(record);
    QMessageBox::information(nullptr, "提示", "已保存");
}

