#ifndef TEACHERMANAGEMENTWINDOW_H
#define TEACHERMANAGEMENTWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include "sqlmodelall.h"
#include "admindialog1.h"

namespace Ui {
class TeacherManagementWindow;
}

class TeacherManagementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherManagementWindow(QWidget *parent = nullptr);
    ~TeacherManagementWindow();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::TeacherManagementWindow *ui;
    AdminDialog1* dialog1;
    QSqlRelationalTableModel* model;
    QItemSelectionModel* selectionModel;

    TeacherSql tsql;
};

#endif // TEACHERMANAGEMENTWINDOW_H
