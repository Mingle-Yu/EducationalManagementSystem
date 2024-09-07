//学生主界面头文件
#ifndef STU_MAINWINDOW_H
#define STU_MAINWINDOW_H

#include "qsqldatabase.h"
#include "qsqltablemodel.h"
#include "announceshowwindow.h"
#include "sqlmodelall.h"
#include<QSqlTableModel>
#include <QMainWindow>
#include<QSqlDatabase>
#include "scoreform.h"
#include "announceform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class stu_MainWindow; }
QT_END_NAMESPACE

class stu_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    stu_MainWindow(int id=1,QWidget *parent = nullptr);
    ~stu_MainWindow();

private slots:
    void on_actionAnnounce_triggered();//公告栏按钮

    void on_actionEvaluate_triggered();//评教按钮（学生评教）

    void on_actionSelect_triggered();//选课按钮（学生选课/退课）

    void on_actionScore_triggered();//成绩表按钮（学生查看成绩）

    void on_actionCourse_triggered();//课程表按钮（学生查看课程表）

    void on_actionChange_triggered();//修改信息按钮（学生修改信息）
    void closeChildWindow(int index);

    void on_stu_tabWidget_tabCloseRequested(int index);

signals:
    void isClosing();

private:
    void closeEvent(QCloseEvent *event);

    void paintEvent(QPaintEvent *event);

    void readFromSettings();

    void writeToSetting();

private:
    Ui::stu_MainWindow *ui;
    int studentId;
    StudentSql student;
    QSqlTableModel* model;

    QPixmap pixmap;
    QPoint mPos;//初始位置
    QSize mSize;//初始大小
};
#endif // STU_MAINWINDOW_H
