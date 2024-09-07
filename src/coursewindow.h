//课程表头文件
#ifndef COURSEWINDOW_H
#define COURSEWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>

namespace Ui {
class CourseWindow;
}

class CourseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CourseWindow(int id,bool isStudent=0,QWidget *parent = nullptr);
    ~CourseWindow();

private:
    Ui::CourseWindow *ui;
    int userId;
    bool mIsStudent;
    CourseTableSql course;
    QSqlTableModel* model;
};

#endif // COURSEWINDOW_H
