#ifndef STUDENTMANAGEMENTWINDOW_H
#define STUDENTMANAGEMENTWINDOW_H

#include <QWidget>
#include "sqlmodelall.h"
#include "admindialog2.h"
#include <QMessageBox>

namespace Ui {
class StudentManagementWindow;
}

class StudentManagementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentManagementWindow(QWidget *parent = nullptr);
    ~StudentManagementWindow();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::StudentManagementWindow *ui;
    AdminDialog2* dialog2;

    QSqlRelationalTableModel* model;
    QItemSelectionModel* selectionModel;

    StudentSql ssql;
};

#endif // STUDENTMANAGEMENTWINDOW_H
