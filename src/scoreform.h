#ifndef SCOREFORM_H
#define SCOREFORM_H


#include <QWidget>
#include <QMap>
#include <QList>
#include <QChartView>
#include <QSqlRelationalTableModel>
#include <QItemSelectionModel>
#include "sqlmodelall.h"
#include "globaldelegate.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ScoreForm;
}

class ScoreForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreForm(QWidget *parent,int idName,int isStudent=0);
    ~ScoreForm();

protected:
    void initialTeacher();

    void initialStudent();

    void drawTableViewForTeacher();

    void analyzeDataForTeacher();

    void annalyzeDataForStudent();

    void drawBarChartForTeacher();

    void drawPieChartForTeacher();

    void drawBarChartForStudent();

    void drawPieChartForStudent();

    void changeShowForStudent();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_TableViewChanged(const QModelIndex& cur,const QModelIndex &pre){
        Q_UNUSED(pre)
        if(cur.isValid()) analyzeDataForTeacher();
    }

    void on_pbtBarNew_clicked();

    void on_ptbSave_clicked();

    void on_pbtPieNew_clicked();

    void on_cbxAll_clicked();

    void on_cbxAllMust_clicked();

    void on_cbxAllChoose_clicked();

    void on_cbxMyMust_clicked();

    void on_cbxMyChoose_clicked();

private:
    Ui::ScoreForm *ui;
    int mIsStudent;
    int mIdName;

    QSqlTableModel *forStduentModel;
    QSqlTableModel *forTeacherModel;

    ReadOnlyDelegate readOnly;//只读代理
    QMap<QString,int> mp;//记录comBox中课程的Id
    QString teacherName;//记录老师姓名

    //绘制图形
    QList<qreal> scoreList;//每个分数段人数
    QList<QString> xList;//bar图形x轴名称
    QChart *s1;//学生Bar
    QChart *s2;//学生Pie
    QChart *t1;//教师Bar
    QChart *t2;//教师Pie
};

#endif // SCOREFORM_H
