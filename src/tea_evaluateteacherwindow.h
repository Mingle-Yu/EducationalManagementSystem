//教师评教界面头文件
#ifndef TEA_EVALUATETEACHERWINDOW_H
#define TEA_EVALUATETEACHERWINDOW_H

#include "qsqltablemodel.h"
#include "sqlmodelall.h"
#include <QWidget>
#include <QChart>
#include <QChartView>
#include"globaldelegate.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class tea_EvaluateTeacherWindow;
}

class tea_EvaluateTeacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit tea_EvaluateTeacherWindow(int id,QWidget *parent = nullptr);
    ~tea_EvaluateTeacherWindow();

private slots:
    void on_toolButton_clicked();

protected:
    void analayzeDataForTeacher();

    void drawBarChartForTeacher();

    void drawPieChartForTeacher();

private:
    Ui::tea_EvaluateTeacherWindow *ui;
    int teacherId;
    EvaluateTeacherSql evaluate;
    QSqlTableModel* model;
    QChart *s1;
    QChart *s2;

    QList<qreal> scoreList;
    QList<QString> nameList;
};

#endif // TEA_EVALUATETEACHERWINDOW_H
