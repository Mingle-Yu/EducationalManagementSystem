#ifndef COURSEMANAGEMENTWINDOW_H
#define COURSEMANAGEMENTWINDOW_H

#include <QWidget>
#include "sqlmodelall.h"
#include "admindialog3.h"
#include <QMessageBox>

namespace Ui {
class CourseManagementWindow;
}

class CourseManagementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CourseManagementWindow(QWidget *parent = nullptr);
    ~CourseManagementWindow();

private slots:


    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::CourseManagementWindow *ui;

    AdminDialog3* dialog3;
    //QSqlTableModel* model;
    QSqlRelationalTableModel *model;
    QItemSelectionModel* selectionModel;

    CourseTableSql csql;
};

#endif // COURSEMANAGEMENTWINDOW_H
