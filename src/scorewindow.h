//教师成绩单界面头文件
#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>

namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWindow(int id,QWidget *parent = nullptr);
    ~ScoreWindow();

private slots:


    void on_SaveButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::ScoreWindow *ui;
    int teacherId;
    ScoreSql score;

    QSqlTableModel* model;
};

#endif // SCOREWINDOW_H
