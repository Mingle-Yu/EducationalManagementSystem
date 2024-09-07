//  学生管理对话框
#ifndef ADMINDIALOG2_H
#define ADMINDIALOG2_H

#include <QDialog>
#include "sqlmodelall.h"
#include <QMessageBox>

namespace Ui {
class AdminDialog2;
}

class AdminDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog2(QWidget *parent = nullptr);
    ~AdminDialog2();
    bool isValid();
    void initDialog1(int id, QSqlTableModel* m);
    void initDialog2(int id, QSqlTableModel* m);

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

    void on_comboBoxDepartment_currentIndexChanged(int index);

    void on_comboBoxMajor_currentIndexChanged(int index);

private:
    Ui::AdminDialog2 *ui;
    int studentId;
    StudentSql ssql;

    QSqlTableModel* model;
};

#endif // ADMINDIALOG2_H
