//老师修改信息头文件
#ifndef CHANGEWINDOW_H
#define CHANGEWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>

namespace Ui {
class ChangeWindow;
}

class ChangeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeWindow(int id,QWidget *parent = nullptr);
    ~ChangeWindow();

private slots:
    void on_EditButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::ChangeWindow *ui;
    StudentSql student;
    TeacherSql teacher;
    int teacherId;
};

#endif // CHANGEWINDOW_H
