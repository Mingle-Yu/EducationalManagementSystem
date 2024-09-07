#include "adminwindow.h"
#include "ui_adminwindow.h"

#include "smallchooseform.h"
#include "sqlmodelall.h"

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>

extern ExecutePro* myProgram;

AdminWindow::AdminWindow(int Id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    adminId(Id)
{
    ui->setupUi(this);
    pixmap.load(":/Image/my photos/main.jpg");
    this->setAttribute(Qt::WA_DeleteOnClose);


    //窗口出现位置，窗口大小
    readFromSettings();
    this->move(mPos);
    this->resize(mSize);

    //工具栏位置初始在顶层
    ui->toolBar->setAllowedAreas(Qt::TopToolBarArea);
    ui->toolBar->setFloatable(false);

    //  不显示任何页面
    ui->tabWidget->setVisible(false);
    //  清除所有页面
    ui->tabWidget->clear();
    //  启用页面的关闭按钮
    ui->tabWidget->setTabsClosable(true);
    //  关闭按钮连接槽函数，以关闭页面
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &closeChildWindow);
}

AdminWindow::~AdminWindow()
{
    qDebug("ddd");
    delete ui;
}

void AdminWindow::on_personalAccountSettings_triggered()
{
    //  设置AccountSettingsWindow的一些属性
    AccountSettingsWindow* asw = new AccountSettingsWindow(adminId, this);
    asw->setAttribute(Qt::WA_DeleteOnClose);    //  关闭时自动删除
    int cur = ui->tabWidget->addTab(asw, QString("%1%2").arg(asw->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_teacherManagement_triggered()
{
    TeacherManagementWindow* tmw = new TeacherManagementWindow(this);
    tmw->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(tmw, QString("%1%2").arg(tmw->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);

}


void AdminWindow::on_studentManagement_triggered()
{
    StudentManagementWindow* smw = new StudentManagementWindow(this);
    smw->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(smw, QString("%1%2").arg(smw->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_courseManagement_triggered()
{
    CourseManagementWindow* cmw = new CourseManagementWindow(this);
    cmw->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(cmw, QString("%1%2").arg(cmw->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_teachingEvaluationManagement_triggered()
{
    ETeacherManagementWindow* etmw = new ETeacherManagementWindow(this);
    etmw->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(etmw, QString("%1%2").arg(etmw->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_courseSelectionManagement_triggered()
{
    SelectCourseForm* scf = new SelectCourseForm(this, adminId, 2);
    scf->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(scf, QString("%1%2").arg(scf->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_gradeManagement_triggered()
{
    AdminScoreForm* asf = new AdminScoreForm(this);
    asf->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(asf, QString("%1%2").arg(asf->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void AdminWindow::on_announcementManagement_triggered()
{
    smallChooseForm* as = new smallChooseForm(this, true);
    as->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(as, QString("%1%2").arg(as->windowTitle()).arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void AdminWindow::closeChildWindow(int index)
{
    ui->tabWidget->removeTab(index);
}

void AdminWindow::closeEvent(QCloseEvent *event)
{
    emit isClosing();
    mPos=this->pos();
    writeToSetting();

    QMainWindow::closeEvent(event);
}

void AdminWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int ypos=ui->toolBar->height();
    int xpos=0;

    int W=this->width();
    int H=this->height() - ypos - ui->statusbar->height();
    painter.drawPixmap(xpos,ypos,W,H,pixmap.scaledToWidth(W));
    QMainWindow::paintEvent(event);
}

void AdminWindow::readFromSettings()
{
    QSettings mySettings("myProject","myLoginSettings");
    mPos  =  mySettings.value("endPos",pos()).toPoint();
    mSize = mySettings.value("windowSize",QSize(800,600)).toSize();
}

void AdminWindow::writeToSetting()
{

    QSettings mySettings("myProject","myLoginSettings");
    mySettings.setValue("endPos",mPos);
    mySettings.setValue("windowSize",this->size());
}

void AdminWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(ui->tabWidget->count()<2)
    {
        ui->tabWidget->setVisible(false);
    }

    QWidget * wid = ui->tabWidget->widget(index);
    wid->close();

}

