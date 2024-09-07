#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QToolBar>
#include <QMouseEvent>

#include "sqlmodelall.h"
#include "accountsettingswindow.h"
#include "teachermanagementwindow.h"
#include "studentmanagementwindow.h"
#include "coursemanagementwindow.h"
#include "eteachermanagementwindow.h"
#include "selectcourseform.h"
#include "adminscoreform.h"
#include "announceform.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(int Id = 1, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_personalAccountSettings_triggered();

    void on_teacherManagement_triggered();

    void on_studentManagement_triggered();

    void on_courseManagement_triggered();

    void on_teachingEvaluationManagement_triggered();

    void on_courseSelectionManagement_triggered();

    void on_gradeManagement_triggered();

    void on_announcementManagement_triggered();

    void closeChildWindow(int index);

    void on_tabWidget_tabCloseRequested(int index);

signals:
    void isClosing();

private:
    void closeEvent(QCloseEvent *event);

    void paintEvent(QPaintEvent *event);

    void readFromSettings();

    void writeToSetting();

private:
    Ui::AdminWindow *ui;
    int adminId;    //  管理员编号（账号）
    AnnounceSql announce;      //   数据库操作类
    AdministratorSql admin;
    CourseTableSql cousre;
    EvaluateTeacherSql eteacher;
    ScoreSql score;
    SelectCourseSql scourse;
    StudentSql student;
    TeacherSql teacher;

    QSqlRecord record;

    QPixmap pixmap;//背景图片
    QPoint mPos;//初始位置
    QSize mSize;//初始大小
};

#endif // ADMINWINDOW_H
