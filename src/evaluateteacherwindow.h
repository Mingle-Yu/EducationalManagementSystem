//学生评教界面头文件
#ifndef EVALUATETEACHERWINDOW_H
#define EVALUATETEACHERWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>
#include <QItemSelectionModel>
#include "qitemdelegate.h"
#include"globaldelegate.h"

namespace Ui {
class EvaluateTeacherWindow;
}

class EvaluateTeacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluateTeacherWindow(int id,QWidget *parent = nullptr);
    ~EvaluateTeacherWindow();

private slots:

    void on_Marking(const QModelIndex& cur,const QModelIndex& pre);

    void on_SubmitButton_clicked();

private:
    Ui::EvaluateTeacherWindow *ui;
    int studentId;
    QItemSelectionModel *select;
    EvaluateTeacherSql evaluate;
    //QSqlTableModel *model;
    QSqlRelationalTableModel* model;
};

#endif // EVALUATETEACHERWINDOW_H
