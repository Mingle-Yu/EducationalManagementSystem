#include "scoreform.h"
#include "ui_scoreform.h"


#include "sqlmodelall.h"

#include <QDebug>
#include <QBarSet>
#include <QValueAxis>
#include <QBarSeries>
#include <QPieSeries>
#include <QMessageBox>
#include <QBarCategoryAxis>


ScoreForm::ScoreForm(QWidget *parent,int idName,int isStudent) :
QWidget(parent),
ui(new Ui::ScoreForm)
{
    ui->setupUi(this);
    mIsStudent=isStudent;
    mIdName=idName;

    resize(1060,600);

    //为4个chartView设置chart，和动画效果
    t1=new QChart();
    t1->setAnimationDuration(QChart::SeriesAnimations);
    t1->setTitle("学生成绩");
    ui->teacherBarView->setChart(t1);

    t2=new QChart();
    t2->setAnimationDuration(QChart::SeriesAnimations);
    t2->setTitle("学生成绩");
    ui->teacherPieView->setChart(t2);

    s1=new QChart();
    s1->setAnimationDuration(QChart::SeriesAnimations);
    s1->setTitle("学生成绩");
    ui->studentBarChartView->setChart(s1);

    s2=new QChart();
    s2->setAnimationDuration(QChart::SeriesAnimations);
    s2->setTitle("学生成绩");
    ui->studentPieChartView->setChart(s2);


    //根据身份显示StackWiget不同页面
    if(mIsStudent) ui->stackedWidget->setCurrentIndex(0);
    else ui->stackedWidget->setCurrentIndex(1);

    xList<<"60分以下"<<"70分以下"<<"80分以下"<<"90分以下"<<"90分及以上";

    forTeacherModel = nullptr;

    if(mIsStudent) {
        initialStudent();
        this->annalyzeDataForStudent();
        drawBarChartForStudent();
        drawPieChartForStudent();
        ui->cbxAll->setChecked(1);
        changeShowForStudent();
    }
    else{
        TeacherSql teacherList;
        QSqlRecord record = teacherList.findSingleRecord(mIdName);
        teacherName=record.value("teacherName").toString();
        initialTeacher();
    }

}

void ScoreForm::initialTeacher()
{
    //设置课程选择的combox，从课程表中读取
    SelectCourseSql select;
    QString sqlstr;
    sqlstr=tr("select * from course_table where teacherId=%1 ").arg(mIdName);
    QSqlQuery query=select.getQueryList(sqlstr);

    if(query.first()){
        do{
            QSqlRecord record = query.record();
            int id=record.value("courseId").toInt();
            QString name=record.value("courseName").toString();
            ui->comboBox->addItem(name);
            mp.insert(name,id);
        }while(query.next());
    }

    //没有课程直接返回
    if(!ui->comboBox->count()) return;
    ui->comboBox->setCurrentIndex(0);

    //设置所有学生的成绩记录,先插一条记录，成绩为空，再由老师添加成绩
    sqlstr=tr("select * from select_course_table where teacherId=%1 ").arg(mIdName);
    query=select.getQueryList(sqlstr);
    ScoreSql scoreList;
    if(query.first())
    {
        do{
            QSqlRecord record = query.record();

            int studentId=record.value("studentId").toInt();

            if(studentId==0){
                qDebug()<<"it is wrong"<<endl;
            }

            int courseId=record.value("courseId").toInt();
            QString courseName=record.value("courseName").toString();
            int courseTerm=record.value("courseTerm").toInt();

            StudentSql studentList;
            QSqlRecord mRecord=studentList.findSingleRecord(studentId);
            QString studentName=mRecord.value("studentName").toString();

            //从成绩表查找所有记录，如果都没有才可以插入记录
            QString sqlstr=tr("select * from score_table where studentId=%1 and teacherId=%2 and courseId=%3 and courseTerm=%4 ").arg(studentId).arg(mIdName).arg(courseId).arg(courseTerm);
            QSqlQuery qry = scoreList.getQueryList(sqlstr);
            qry.first();
            record = qry.record();

            //如果该学生在该门课程已经有成绩记录了，就不再插入,没有则插入
            if(record.value("studentId").isNull())
            {
                qDebug()<<studentId<<endl;
                //在该门课程没有成绩记录了
                record.setValue("studentId",studentId);
                record.setValue("teacherId",mIdName);
                record.setValue("courseId",courseId);
                record.setValue("courseTerm",courseTerm);
                record.setValue("courseName",courseName);
                record.setValue("studentName",studentName);
                record.setValue("teacherName",teacherName);

                scoreList.insertSingleRecord(record);
            }



        }while(query.next());
    }

    drawTableViewForTeacher();
}

void ScoreForm::initialStudent()
{
    ScoreSql scoreList;
    forStduentModel=scoreList.getTableModel(this);
    forStduentModel->setFilter(tr(" studentId=%1 and score is not null and studentPass is not null ").arg(mIdName));
    ui->myScoreTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->myScoreTableView->setModel(forStduentModel);
    ui->myScoreTableView->setColumnHidden(0,1);//序号
    ui->myScoreTableView->setColumnHidden(2,1);//学生编号
    ui->myScoreTableView->setColumnHidden(3,1);//教师编号
    ui->myScoreTableView->setColumnHidden(6,1);
}


void ScoreForm::drawTableViewForTeacher()
{
    //展示当前combox选择的成绩和对应的课程
    if(ui->comboBox->count()==0) return;

    ScoreSql scoreList;
    int courseId=mp.value(ui->comboBox->currentText());
    forTeacherModel = scoreList.getTableModel(this);
    forTeacherModel->setFilter(tr(" teacherId = %1 and courseId = %2").arg(mIdName).arg(courseId));
    forTeacherModel->setSort(forTeacherModel->fieldIndex("studentId"),Qt::AscendingOrder);
    ui->studentTableView->setModel(forTeacherModel);


    ui->studentTableView->setColumnHidden(0,1);//序号
    ui->studentTableView->setColumnHidden(3,1);//教师编号
    ui->studentTableView->setColumnHidden(forTeacherModel->fieldIndex("studentReTryNum"),1);
    ui->studentTableView->setColumnHidden(forTeacherModel->fieldIndex("studentPass"),1);

    //设置只读代理
    ui->studentTableView->setItemDelegateForColumn(forTeacherModel->fieldIndex("courseId"),&readOnly);
    ui->studentTableView->setItemDelegateForColumn(forTeacherModel->fieldIndex("studentId"),&readOnly);
    ui->studentTableView->setItemDelegateForColumn(forTeacherModel->fieldIndex("courseTerm"),&readOnly);
    ui->studentTableView->setItemDelegateForColumn(forTeacherModel->fieldIndex("courseName"),&readOnly);

    analyzeDataForTeacher();
}

void ScoreForm::analyzeDataForTeacher()
{
    //设置每个分数段的人数，显示在treeWidget上
    scoreList.clear();
    int less60=0,less70=0,less80=0,less90=0,more90=0,noscore=0;
    int mMax=0,mMin=100;
    qreal sum=0;

    int row=0;
    if(forTeacherModel!=nullptr)
    {
        row = forTeacherModel->rowCount();
        int itemCol=forTeacherModel->fieldIndex("score");
        for(int i=0;i<row;++i){
            QModelIndex index=forTeacherModel->index(i,itemCol);

            QVariant data = forTeacherModel->data(index,Qt::EditRole);

            if(data.isNull()){
                noscore++;
                continue;
            }
            else{

                float num=data.toFloat();

                if(num<60) less60++;
                else if(num<70) less70++;
                else if(num<80) less80++;
                else if(num<90) less90++;
                else more90++;

                sum+=num;
                mMax= mMax > num ? mMax:num;
                mMin= mMin < num ? mMin:num;
            }
        }
    }

    QTreeWidgetItem *item=ui->scoreSituationTree->topLevelItem(0);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",less60));


    item=ui->scoreSituationTree->topLevelItem(1);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",less70));

    item=ui->scoreSituationTree->topLevelItem(2);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",less80));

    item=ui->scoreSituationTree->topLevelItem(3);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",less90));

    item=ui->scoreSituationTree->topLevelItem(4);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",more90));


    item=ui->scoreSituationTree->topLevelItem(5);
    item->setTextAlignment(1,Qt::AlignCenter);
    if(noscore!=row)    item->setText(1,QString::asprintf("%d",mMax));
    else    item->setText(1,"");

    item=ui->scoreSituationTree->topLevelItem(6);
    item->setTextAlignment(1,Qt::AlignCenter);
    if(noscore!=row)    item->setText(1,QString::asprintf("%d",mMin));
    else    item->setText(1,"");

    item=ui->scoreSituationTree->topLevelItem(7);
    item->setTextAlignment(1,Qt::AlignCenter);
    int valid=row-noscore;
    if(valid)   item->setText(1,QString::asprintf("%.4lf",sum/valid));
    else item->setText(1,"");

    item=ui->scoreSituationTree->topLevelItem(8);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%d",noscore));

    scoreList<<less60<<less70<<less80<<less90<<more90;

}

void ScoreForm::annalyzeDataForStudent()
{
    //设置每个分数段的人数，显示在treeWidget上
    int row=forStduentModel->rowCount();

    scoreList.clear();

    int less60=0,less70=0,less80=0,less90=0,more90=0;

    int itemCol=forStduentModel->fieldIndex("score");
    for(int i=0;i<row;++i){
        QModelIndex index=forStduentModel->index(i,itemCol);

        float num =forStduentModel->data(index,Qt::EditRole).toFloat();

        if(num<60) less60++;
        else if(num<70) less70++;
        else if(num<80) less80++;
        else if(num<90) less90++;
        else more90++;
    }
    scoreList<<less60<<less70<<less80<<less90<<more90;
}

void ScoreForm::on_comboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    delete forTeacherModel;
    forTeacherModel=nullptr;
    drawTableViewForTeacher();
}

void ScoreForm::on_pbtBarNew_clicked()
{
    analyzeDataForTeacher();
    drawBarChartForTeacher();
}

void ScoreForm::drawBarChartForTeacher()
{
    QChart *chart=ui->teacherBarView->chart();

    if(mIsStudent) chart=ui->studentBarChartView->chart();

    if(chart->series().isEmpty()==false)
        chart->removeAllSeries();

    if(chart->axisX()!=nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }

    //设置数据集合
    QBarSet *perNum=new QBarSet("人数",this);
    perNum->append(scoreList);
    //设置数据序列
    QBarSeries *series=new QBarSeries(this);
    series->append(perNum);
    chart->addSeries(series);
    if(mIsStudent) perNum->setLabel("科目门数");

    //坐标，横坐标为分数段
    QBarCategoryAxis *axisX=new QBarCategoryAxis(this);
    axisX->append(xList);
    chart->setAxisX(axisX,series);//为序列添加横坐标

    QValueAxis *axisY=new QValueAxis(this);
    int mMax=0;
    for(int i=0;i<scoreList.count();++i)
        mMax= scoreList.at(i) > mMax ? scoreList.at(i):mMax;

    mMax= mMax>0 ? mMax : 1;

    axisY->setRange(0,mMax);
    axisY->setTitleText("人数");
    if(mIsStudent) axisY->setTitleText("科目门数");
    axisY->setLabelFormat("%.2f");
    axisY->setTickCount(mMax);
    chart->setAxisY(axisY,series);//为序列添加纵坐标

    chart->legend()->setVisible(1);//序列标签
    chart->legend()->setAlignment(Qt::AlignRight);
}

void ScoreForm::drawPieChartForTeacher()
{
    QChart *chart=ui->teacherPieView->chart();

    if(mIsStudent) chart=ui->studentPieChartView->chart();

    if(chart->series().isEmpty()==false)
        chart->removeAllSeries();

    //为序列添加值
    QPieSeries *series=new QPieSeries(this);
//    series->setHoleSize(0.01);
    for(int i=0;i<scoreList.count();++i)
        series->append(xList.at(i),scoreList.at(i));

    QPieSlice *slice;
    for(int i=0;i<scoreList.count();++i)
    {
        slice=series->slices().at(i);
        if(mIsStudent){
            slice->setLabel(slice->label()+QString::asprintf(":%.0f门，%.1f%%",
                slice->value(),slice->percentage()*100));
        }
        else{
            slice->setLabel(slice->label()+QString::asprintf(":%.0f人，%.1f%%",
                slice->value(),slice->percentage()*100));
        }


        //突出效果
        connect(slice,&QPieSlice::hovered,[=](bool show){
            slice->setExploded(show);
        });

    }

    //
    series->setLabelsVisible(1);
    chart->addSeries(series);
    chart->legend()->setVisible(1);
    chart->legend()->setAlignment(Qt::AlignRight);

}

void ScoreForm::changeShowForStudent()
{
    if(ui->cbxAll->isChecked()) return;

    //先取得chebx的选择
    bool publicChoose=0,publicMust=0,onlyChoose=0,onlyMust=0;
    publicMust=ui->cbxAllMust->isChecked();
    publicChoose=ui->cbxAllChoose->isChecked();
    onlyChoose=ui->cbxMyChoose->isChecked();
    onlyMust=ui->cbxMyMust->isChecked();

    qDebug("%d %d %d %d",publicMust,publicChoose,onlyChoose,onlyMust);
    StudentSql studentList;
    CourseTableSql courseList;

    //记录学生的专业Id
    QSqlRecord record=studentList.findSingleRecord(mIdName);
    int majorIdOfStudent=record.value("majorId").toInt();

    //将学生的专业Id和课程Id比较，判断是不是公选，再判断课程是不是公选
    int row=forStduentModel->rowCount();
    int courseIdCol=forStduentModel->fieldIndex("courseId");
    for(int i=0;i<row;++i)
    {
        QModelIndex index=forStduentModel->index(i,courseIdCol);
        int courseId=forStduentModel->data(index,Qt::EditRole).toInt();

        record=courseList.findSingleRecord(courseId);
        int courseMajorId=record.value("majorId").toInt();

        qDebug("%d %d",courseMajorId,majorIdOfStudent);
        //专业Id相同

        if(courseMajorId==majorIdOfStudent){
            //0公必 1公选 2专必 3专选
            int type=record.value("courseType").toInt();
            //不要公选
            if(!publicChoose && type==1) ui->myScoreTableView->setRowHidden(i,1);
            //不要公必
            else if(!publicMust && type==0) ui->myScoreTableView->setRowHidden(i,1);
            //不要专选
            else if(!onlyChoose && type==3) ui->myScoreTableView->setRowHidden(i,1);
            //不要专必
            else if(!onlyMust && type==2) ui->myScoreTableView->setRowHidden(i,1);
            //都要
            else
                ui->myScoreTableView->setRowHidden(i,0);
        }
        else{
            if(!publicChoose) ui->myScoreTableView->hideRow(i);
            else ui->myScoreTableView->setRowHidden(i,0);
        }
    }

}

void ScoreForm::drawBarChartForStudent()
{
    drawBarChartForTeacher();
}

void ScoreForm::drawPieChartForStudent()
{
    drawPieChartForTeacher();
}

ScoreForm::~ScoreForm()
{
    delete ui;
    delete s1;
    delete s2;
    delete t1;
    delete t2;
}

void ScoreForm::on_ptbSave_clicked()
{
    if(forTeacherModel && forTeacherModel->isDirty())
    {
        int ret = QMessageBox::question(this,"上传","确认上传成绩？",QMessageBox::Yes|QMessageBox::No);

        if(ret==QMessageBox::No) return;

        forTeacherModel->submitAll();
    }

}

void ScoreForm::on_pbtPieNew_clicked()
{
    analyzeDataForTeacher();
    drawPieChartForTeacher();
}

void ScoreForm::on_cbxAll_clicked()
{
    changeShowForStudent();
}

void ScoreForm::on_cbxAllMust_clicked()
{
    changeShowForStudent();
}

void ScoreForm::on_cbxAllChoose_clicked()
{
    changeShowForStudent();
}

void ScoreForm::on_cbxMyMust_clicked()
{
    changeShowForStudent();
}

void ScoreForm::on_cbxMyChoose_clicked()
{
    changeShowForStudent();
}
