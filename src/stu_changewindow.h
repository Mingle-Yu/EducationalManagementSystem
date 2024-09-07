//学生修改信息界面头文件
#ifndef STU_CHANGEWINDOW_H
#define STU_CHANGEWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>

namespace Ui {
class stu_ChangeWindow;
}

class stu_ChangeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit stu_ChangeWindow(int id,QWidget *parent = nullptr);
    ~stu_ChangeWindow();

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::stu_ChangeWindow *ui;
    int studentId;
    StudentSql student;
};

#endif // STU_CHANGEWINDOW_H
