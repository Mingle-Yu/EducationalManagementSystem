//学生评教界面
#include "evaluateteacherwindow.h"
#include "ui_evaluateteacherwindow.h"
#include "globaldelegate.h"

#include    <QMessageBox>
#include    <QSqlRecord>

EvaluateTeacherWindow::EvaluateTeacherWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluateTeacherWindow),studentId(id)
{
    ui->setupUi(this);

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();

    //选择列用关系model,并且为教师编号设置关系
    model = evaluate.getRelationModel(this);
    ui->EvaluateTeachertableView->setModel(model);
    TeacherSql teacherList; QString teacherTableName=teacherList.getTableName();
    model->setHeaderData(3,Qt::Horizontal,"教师姓名");
    model->setRelation(3,QSqlRelation(teacherTableName,"teacherId","teacherName"));
    //设置选择模型
    select=new QItemSelectionModel(model);
    ui->EvaluateTeachertableView->setSelectionModel(select);
    connect(select,&QItemSelectionModel::currentChanged,this,&EvaluateTeacherWindow::on_Marking);

    //插入评教记录
    ScoreSql scoreList;
    CourseTableSql course;
    QString sqlstr;
    sqlstr=tr("select * from score_table where studentId=%1 and score is not null").arg(studentId);

    //设置所有学生的评教记录,先插一条记录，总分为空，再由学生添加成绩
    QSqlQuery query=scoreList.getQueryList(sqlstr);
    if(query.first())
    {
        do{
            QSqlRecord record = query.record();

            //成绩表中三个ID和课程学期
            int teacherId=record.value("teacherId").toInt();
            int courseId=record.value("courseId").toInt();
            int courseTerm=record.value("courseTerm").toInt();

            //课程记录,找到剩下三个属性
            QSqlRecord mRecord=course.findSingleRecord(courseId);
            QString courseName=mRecord.value("courseName").toString();
            int majorId=mRecord.value("majorId").toInt();
            int departmentId=mRecord.value("departmentId").toInt();

            //从评教表查找所有记录，如果都没有才可以插入记录
            QString sqlstr=tr("select * from evaluate_teacher_table where studentId=%1 and teacherId=%2 and courseId=%3 and courseTerm=%4 ").arg(studentId).arg(teacherId).arg(courseId).arg(courseTerm);

            QSqlQuery qry = evaluate.getQueryList(sqlstr);
            qry.first();
            record = qry.record();

            //如果该学生在该门课程已经有评教记录了，就不再插入,没有则插入
            if(record.isNull(0))
            {
                //在该门课程没有评教记录了
                record.setValue("studentId",studentId);
                record.setValue("teacherId",teacherId);
                record.setValue("courseId",courseId);
                record.setValue("courseTerm",courseTerm);
                record.setValue("courseName",courseName);
                record.setValue("majorId",majorId);
                record.setValue("departmentId",departmentId);

                evaluate.insertSingleRecord(record);
            }

        }while(query.next());
    }

    /*************************************************************************************************/
    /*************************************************************************************************/
    //隐藏列
    ui->EvaluateTeachertableView->setColumnHidden(0,1);//序号
    ui->EvaluateTeachertableView->setColumnHidden(1,1);//学号
    ui->EvaluateTeachertableView->setColumnHidden(2,1);//课程编号
    ui->EvaluateTeachertableView->setColumnHidden(5,1);//专业编号
    ui->EvaluateTeachertableView->setColumnHidden(6,1);//院系编号

    //只读代理
    ui->EvaluateTeachertableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(4, readOnlyDelegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(5, readOnlyDelegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(6, readOnlyDelegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(7, readOnlyDelegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(13, readOnlyDelegate);

    //打分代理
    EvaluareDelegate *dalegate=new EvaluareDelegate(this);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(8, dalegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(9, dalegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(10, dalegate);
    ui->EvaluateTeachertableView->setItemDelegateForColumn(11, dalegate);


    model->select();

}

EvaluateTeacherWindow::~EvaluateTeacherWindow()
{
    delete ui;
}

void EvaluateTeacherWindow::on_Marking(const QModelIndex &cur, const QModelIndex &pre)
{
    Q_UNUSED(pre)
    Q_UNUSED(cur)

    int sumCol = model->fieldIndex("sumScore");
    for(int i=0;i<model->rowCount();++i)
    {
        int sum = 0;
        for(int j=8;j<=11;++j)
        {
            QModelIndex index=model->index(i,j);
            sum+=model->data(index).toInt();
        }
        QModelIndex index=model->index(i,sumCol);
        model->setData(index,sum,Qt::EditRole);
    }
}

void EvaluateTeacherWindow::on_SubmitButton_clicked()                   //提交按钮
{

    //被更改过才提交
    if(model->isDirty())
    {
         int ret= QMessageBox::question(this,"提交窗口","是否确认提交？",QMessageBox::Yes|QMessageBox::No);
         if(ret==QMessageBox::Yes)
         {
             QMessageBox::about(this,"提示","提交成功");
             model->submitAll();
         }
    }
}


