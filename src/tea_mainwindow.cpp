//��ʦ������
#include "tea_mainwindow.h"
#include "announceshowwindow.h"
#include "coursewindow.h"
#include "evaluateteacherwindow.h"
#include "scorewindow.h"
#include "changewindow.h"
#include "tea_evaluateteacherwindow.h"
#include "ui_tea_mainwindow.h"
#include "smallchooseform.h"
#include"admindialog3.h"
#include"selectcourseform.h"

#include <QPainter>

tea_MainWindow::tea_MainWindow(int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tea_MainWindow),teacherId(id)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    pixmap.load(":/Image/my photos/main.jpg");

    //窗口出现位置，窗口大小
    readFromSettings();
    this->move(mPos);
    this->resize(mSize);

    ui->toolBar->setAllowedAreas(Qt::TopToolBarArea);
    ui->toolBar->setFloatable(false);

    //����ʾ�κ�ҳ��
    ui->tea_tabWidget->setVisible(false);
    //��������ҳ��
    ui->tea_tabWidget->clear();
    //������ҳ���رհ�ť
    ui->tea_tabWidget->setTabsClosable(true);
    //�رհ�ť���Ӳۺ���
    connect(ui->tea_tabWidget,&QTabWidget::tabCloseRequested,this, &tea_MainWindow::closeChildWindow);
}

tea_MainWindow::~tea_MainWindow()
{
    qDebug("ddd");
    delete ui;
}
void tea_MainWindow::on_actionScore_2_triggered()        //�ɼ�����ť����ʦ�޸ĳɼ���
{
    ScoreForm* sf = new ScoreForm(this, teacherId, 0);
    sf->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->tea_tabWidget->addTab(sf, QString("%1%2").arg(sf->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}
void tea_MainWindow::on_actionEvaluate_2_triggered()          //���̰�ť����ʦ�鿴���̽�����
{
    tea_EvaluateTeacherWindow* etw = new tea_EvaluateTeacherWindow(teacherId,this);
    etw->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->tea_tabWidget->addTab(etw, QString("%1%2").arg(etw->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}
void tea_MainWindow::on_actionCourse_2_triggered()          //�γ̱���ť����ʦ�鿴�ڿα���
{
    CourseWindow* cw = new CourseWindow(teacherId,0,this);
    cw->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->tea_tabWidget->addTab(cw, QString("%1%2").arg(cw->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}
void tea_MainWindow::on_actionAnnounce_2_triggered()        //��������ť����ʦ�鿴���棩
{
    smallChooseForm* af = new smallChooseForm(this, false);
    af->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->tea_tabWidget->addTab(af, QString("%1%2").arg(af->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}
void tea_MainWindow::on_actionChange_2_triggered()          //�޸���Ϣ����ʦ�޸���Ϣ��
{
    ChangeWindow* scw_2 = new ChangeWindow(teacherId,this);
    scw_2->setAttribute(Qt::WA_DeleteOnClose);    //  �ر�ʱ�Զ�ɾ��
    int cur = ui->tea_tabWidget->addTab(scw_2, QString("%1%2").arg(scw_2->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}

void tea_MainWindow::on_actiontea_SelectCourse_triggered()
{
    SelectCourseForm* tsc = new SelectCourseForm(this,teacherId,1);
    tsc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tea_tabWidget->addTab(tsc, QString("%1%2").arg(tsc->windowTitle()).arg(ui->tea_tabWidget->count() + 1));
    ui->tea_tabWidget->setCurrentIndex(cur);
    ui->tea_tabWidget->setVisible(true);
}


void tea_MainWindow::closeChildWindow(int index)
{
    ui->tea_tabWidget->removeTab(index);
}

void tea_MainWindow::closeEvent(QCloseEvent *event)
{
    emit isClosing();
    mPos=this->pos();
    writeToSetting();

    QMainWindow::closeEvent(event);
}

void tea_MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int ypos=ui->toolBar->height();
    int xpos=0;

    int W=this->width();
    int H=this->height() - ypos - ui->statusbar->height();
    painter.drawPixmap(xpos,ypos,W,H,pixmap.scaled(W,H));

    QMainWindow::paintEvent(event);
}

void tea_MainWindow::readFromSettings()
{
    QSettings mySettings("myProject","myLoginSettings");
    mPos  =  mySettings.value("endPos",pos()).toPoint();
    mSize = mySettings.value("windowSize",QSize(800,600)).toSize();
}

void tea_MainWindow::writeToSetting()
{
    QSettings mySettings("myProject","myLoginSettings");
    mySettings.setValue("endPos",mPos);
    mySettings.setValue("windowSize",this->size());
}

void tea_MainWindow::on_tea_tabWidget_tabCloseRequested(int index)
{
    if(ui->tea_tabWidget->count()<2)
    {
        ui->tea_tabWidget->setVisible(false);
    }

    QWidget * wid = ui->tea_tabWidget->widget(index);
    wid->close();
}

