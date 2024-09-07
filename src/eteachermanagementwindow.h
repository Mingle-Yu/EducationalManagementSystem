#ifndef ETEACHERMANAGEMENTWINDOW_H
#define ETEACHERMANAGEMENTWINDOW_H

#include <QWidget>
#include "sqlmodelall.h"
#include "admindialog4.h"
#include <QMessageBox>

namespace Ui {
class ETeacherManagementWindow;
}

class ETeacherManagementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ETeacherManagementWindow(QWidget *parent = nullptr);
    ~ETeacherManagementWindow();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::ETeacherManagementWindow *ui;

    AdminDialog4* dialog4;
    QSqlRelationalTableModel* model;
    QItemSelectionModel* selectionModel;

    EvaluateTeacherSql etsql;
};

#endif // ETEACHERMANAGEMENTWINDOW_H
