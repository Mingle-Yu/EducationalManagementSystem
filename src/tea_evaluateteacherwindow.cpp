//教师评教界面
#include "tea_evaluateteacherwindow.h"
#include "ui_tea_evaluateteacherwindow.h"
#include"globaldelegate.h"

#include <QBarSet>
#include <QValueAxis>
#include <QBarSeries>
#include <QPieSeries>
#include <QMessageBox>
#include <QBarCategoryAxis>

tea_EvaluateTeacherWindow::tea_EvaluateTeacherWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tea_EvaluateTeacherWindow),teacherId(id)
{
    ui->setupUi(this);
    model = evaluate.getTableModel(this);
    model->setFilter(tr(" teacherId = %1 and evaluateStatus is not null and evaluateEffect is not null and evaluateMethod is not null and evaluateContent is not null ").arg(teacherId));
    model->select();

    qDebug("%d",model->rowCount());

    ui->evaluatetableView->setModel(model);
    ui->evaluatetableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->evaluatetableView->setColumnHidden(0,1);
    ui->evaluatetableView->setColumnHidden(2,1);
    ui->evaluatetableView->setColumnHidden(4,1);
    ui->evaluatetableView->setColumnHidden(5,1);
    ui->evaluatetableView->setColumnHidden(1,1);
    ui->evaluatetableView->setColumnHidden(6,1);

    nameList<<"教学态度"<<"教学内容"<<"教学方法"<<"教学效果";

    s1=new QChart();
    s1->setAnimationDuration(QChart::SeriesAnimations);
    s1->setTitle("评教分数统计");
    s2=new QChart();
    s2->setAnimationDuration(QChart::SeriesAnimations);
    s2->setTitle("评教分数统计");

    ui->teacherBarView->setChart(s1);
    ui->teacherPieView->setChart(s2);

    //初始化数据和绘图
    analayzeDataForTeacher();
    drawBarChartForTeacher();
    drawPieChartForTeacher();
}


void tea_EvaluateTeacherWindow::drawBarChartForTeacher()
{
    QChart *chart=ui->teacherBarView->chart();

    if(chart->series().isEmpty()==false)
        chart->removeAllSeries();

    if(chart->axisX()!=nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }

    //设置数据集合
    QBarSet *perNum=new QBarSet("得分",this);
    perNum->append(scoreList);
    //设置数据序列
    QBarSeries *series=new QBarSeries(this);
    series->append(perNum);
    chart->addSeries(series);

    //坐标，横坐标为分数段
    QBarCategoryAxis *axisX=new QBarCategoryAxis(this);
    axisX->append(nameList);
    chart->setAxisX(axisX,series);//为序列添加横坐标

    //纵坐标
    QValueAxis *axisY=new QValueAxis(this);
    axisY->setRange(0,31);
    axisY->setTitleText("分数");
    axisY->setLabelFormat("%.0f");
    axisY->setTickCount(9);
    chart->setAxisY(axisY,series);//为序列添加纵坐标

    chart->legend()->setVisible(1);//序列标签
    chart->legend()->setAlignment(Qt::AlignRight);
}

void tea_EvaluateTeacherWindow::drawPieChartForTeacher()
{
    QChart *chart=ui->teacherPieView->chart();

    if(chart->series().isEmpty()==false)
        chart->removeAllSeries();

    //为序列添加值
    QPieSeries *series=new QPieSeries(this);
//    series->setHoleSize(0.01);
    for(int i=0;i<scoreList.count();++i)
        series->append(nameList.at(i),scoreList.at(i));

    QPieSlice *slice;
    for(int i=0;i<scoreList.count();++i)
    {
        slice=series->slices().at(i);
        slice->setLabel(slice->label()+QString::asprintf(":%.2f分，%.1f%%",
                                                         slice->value(),slice->percentage()*100));

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

tea_EvaluateTeacherWindow::~tea_EvaluateTeacherWindow()
{
    delete ui;
    delete s1;
    delete s2;
}



void tea_EvaluateTeacherWindow::on_toolButton_clicked()
{
    analayzeDataForTeacher();
}

void tea_EvaluateTeacherWindow::analayzeDataForTeacher()
{
    //设置每个分数段的人数，显示在treeWidget上
    scoreList.clear();
    float status=0,effct=0,method=0,content=0;
    int statusMax=0,statusMin=100,effctMax=0,effctMin=100,methodMax=0,methodMin=100,contentMax=0,contentMin=100;
    qreal statusSum=0,effctSum=0,methodSum=0,contentSum=0;


    int statusCol=model->fieldIndex("evaluateStatus");
    int effectCol=model->fieldIndex("evaluateEffect");
    int methodCol=model->fieldIndex("evaluateMethod");
    int contentCol=model->fieldIndex("evaluateContent");

    int row=model->rowCount();
    for(int i=0;i<row;++i){
        QModelIndex statusIndex=model->index(i,statusCol);
        QModelIndex effectIndex=model->index(i,effectCol);
        QModelIndex methodIndex=model->index(i,methodCol);
        QModelIndex contentIndex=model->index(i,contentCol);

        int statusData = model->data(statusIndex,Qt::EditRole).toInt();
        int effectData = model->data(effectIndex,Qt::EditRole).toInt();
        int methodData = model->data(methodIndex,Qt::EditRole).toInt();
        int contentData = model->data(contentIndex,Qt::EditRole).toInt();


        //总分求和
        statusSum+=statusData;
        effctSum+=effectData;
        contentSum+=contentData;
        methodSum+=methodData;

        //各自最大最小值
        statusMax= statusMax > statusData ? statusMax : statusData;
        statusMin= statusMin < statusData ? statusMin : statusData;

        effctMax=effctMax > effectData ? effctMax : effectData;
        effctMin=effctMin < effectData ? effctMin : effectData;

        contentMax=contentMax > contentData ? contentMax : contentData;
        contentMin=contentMin < contentData ? contentMin : contentData;

        methodMax=methodMax > methodData ? methodMax : methodData;
        methodMin=methodMin < methodData ? methodMin : methodData;

    }

    //各自的均分
    if(row!=0)
    {
        status=statusSum/row;
        effct=effctSum/row;
        content=contentSum/row;
        method=methodSum/row;
    }

    //四大均分之和
    qreal sum=status + effct + content + method;

    //均分
    QTreeWidgetItem *item=ui->treeWidget->topLevelItem(0);
    item->setTextAlignment(1,Qt::AlignCenter);
    item->setText(1,QString::asprintf("%.2f",sum));
    item->setTextAlignment(2,Qt::AlignCenter);
    item->setText(2,QString::asprintf("%.2f",status));
    item->setTextAlignment(3,Qt::AlignCenter);
    item->setText(3,QString::asprintf("%.2f",content));
    item->setTextAlignment(4,Qt::AlignCenter);
    item->setText(4,QString::asprintf("%.2f",method));
    item->setTextAlignment(5,Qt::AlignCenter);
    item->setText(5,QString::asprintf("%.2f",effct));

    //最高分
    item=ui->treeWidget->topLevelItem(1);
    item->setTextAlignment(2,Qt::AlignCenter);
    item->setText(2,QString::asprintf("%d",statusMax));
    item->setTextAlignment(3,Qt::AlignCenter);
    item->setText(3,QString::asprintf("%d",contentMax));
    item->setTextAlignment(4,Qt::AlignCenter);
    item->setText(4,QString::asprintf("%d",methodMax));
    item->setTextAlignment(5,Qt::AlignCenter);
    item->setText(5,QString::asprintf("%d",effctMax));

    if(row==0) statusMin=contentMin=methodMin=effctMin=0;
    //最低分
    item=ui->treeWidget->topLevelItem(2);
    item->setTextAlignment(2,Qt::AlignCenter);
    item->setText(2,QString::asprintf("%d",statusMin));
    item->setTextAlignment(3,Qt::AlignCenter);
    item->setText(3,QString::asprintf("%d",contentMin));
    item->setTextAlignment(4,Qt::AlignCenter);
    item->setText(4,QString::asprintf("%d",methodMin));
    item->setTextAlignment(5,Qt::AlignCenter);
    item->setText(5,QString::asprintf("%d",effctMin));

    //占比
    item=ui->treeWidget->topLevelItem(3);
    item->setTextAlignment(2,Qt::AlignCenter);
    item->setText(2,QString::asprintf("%d%%",25));
    item->setTextAlignment(3,Qt::AlignCenter);
    item->setText(3,QString::asprintf("%d%%",30));
    item->setTextAlignment(4,Qt::AlignCenter);
    item->setText(4,QString::asprintf("%d%%",30));
    item->setTextAlignment(5,Qt::AlignCenter);
    item->setText(5,QString::asprintf("%d%%",15));

    scoreList<<status<<content<<method<<effct;
}


