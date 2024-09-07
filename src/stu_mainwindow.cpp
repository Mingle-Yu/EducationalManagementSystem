//ѧ��������
#include "stu_mainwindow.h"
#include "announceshowwindow.h"
#include "coursewindow.h"
#include "evaluateteacherwindow.h"
#include "qsqlerror.h"
#include "scorewindow.h"
#include "selectcourseform.h"
#include "sqlmodelall.h"
#include "changewindow.h"
#include "stu_changewindow.h"
#include "ui_stu_mainwindow.h"
#include "smallchooseform.h"
#include<QMessageBox>

stu_MainWindow::stu_MainWindow(int id,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stu_MainWindow),studentId(id)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    //���ڳ���λ�ã����ڴ�С
    readFromSettings();
    this->move(mPos);
    this->resize(mSize);

    pixmap.load(":/Image/my photos/main.jpg");
    ui->toolBar->setAllowedAreas(Qt::TopToolBarArea);
    ui->toolBar->setFloatable(false);

    //����ʾ�κ�ҳ��
    ui->stu_tabWidget->setVisible(false);
    //��������ҳ��
    ui->stu_tabWidget->clear();
    //������ҳ���رհ�ť
    ui->stu_tabWidget->setTabsClosable(true);
    //�رհ�ť���Ӳۺ���
    connect(ui->stu_tabWidget,&QTabWidget::tabCloseRequested,this, &stu_MainWindow::closeChildWindow);

}

stu_MainWindow::~stu_MainWindow()
{
    qDebug("ddd");
    delete ui;
}

void stu_MainWindow::on_actionAnnounce_triggered()                    //��������ť
{
    smallChooseForm* af = new smallChooseForm(this, false);
    af->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(af, QString("%1%2").arg(af->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);

}

void stu_MainWindow::on_actionEvaluate_triggered()                   //���̰�ť
{
    EvaluateTeacherWindow* etw = new EvaluateTeacherWindow(studentId,this);
    etw->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(etw, QString("%1%2").arg(etw->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);
}

void stu_MainWindow::on_actionSelect_triggered()                    //ѡ�ΰ�ť
{
    SelectCourseForm* scf = new SelectCourseForm(this, studentId, 0);
    scf->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(scf, QString("%1%2").arg(scf->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);
}


void stu_MainWindow::on_actionScore_triggered()                   //�ɼ�����ť
{
    ScoreForm* sf = new ScoreForm(this, studentId, 1);
    sf->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(sf, QString("%1%2").arg(sf->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);

}


void stu_MainWindow::on_actionCourse_triggered()                    //�γ̱���ť
{
    CourseWindow* cw = new CourseWindow(studentId,1,this);
    cw->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(cw, QString("%1%2").arg(cw->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);
}


void stu_MainWindow::on_actionChange_triggered()                    //ѧ���޸���Ϣ
{
    stu_ChangeWindow* scw_2 = new stu_ChangeWindow(studentId,this);
    scw_2->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->stu_tabWidget->addTab(scw_2, QString("%1%2").arg(scw_2->windowTitle()).arg(ui->stu_tabWidget->count() + 1));
    ui->stu_tabWidget->setCurrentIndex(cur);
    ui->stu_tabWidget->setVisible(true);
}

void stu_MainWindow::closeChildWindow(int index)
{
    ui->stu_tabWidget->removeTab(index);
}

void stu_MainWindow::closeEvent(QCloseEvent *event)
{
    emit isClosing();
    mPos=this->pos();
    writeToSetting();

    QMainWindow::closeEvent(event);
}

void stu_MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int ypos=ui->toolBar->height();
    int xpos=0;

    int W=this->width();
    int H=this->height() - ypos - ui->statusbar->height();
    painter.drawPixmap(xpos,ypos,W,H,pixmap.scaled(W,H));

    QMainWindow::paintEvent(event);
}

void stu_MainWindow::readFromSettings()
{
    QSettings mySettings("myProject","myLoginSettings");
    mPos  =  mySettings.value("endPos",pos()).toPoint();
    mSize = mySettings.value("windowSize",QSize(800,600)).toSize();
}

void stu_MainWindow::writeToSetting()
{
    QSettings mySettings("myProject","myLoginSettings");
    mySettings.setValue("endPos",mPos);
    mySettings.setValue("windowSize",this->size());
}

void stu_MainWindow::on_stu_tabWidget_tabCloseRequested(int index)
{
    if(ui->stu_tabWidget->count()<2)
    {
        ui->stu_tabWidget->setVisible(false);
    }

    QWidget * wid = ui->stu_tabWidget->widget(index);
    wid->close();
}

