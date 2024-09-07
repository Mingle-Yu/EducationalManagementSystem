//  教师管理对话框
#ifndef ADMINDIALOG1_H
#define ADMINDIALOG1_H

#include <QDialog>
#include "sqlmodelall.h"
#include <QMessageBox>

namespace Ui {
class AdminDialog1;
}

//  教师管理窗口的子窗口
class AdminDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog1(QWidget *parent = nullptr);
    ~AdminDialog1();
    bool isValid();
    void initDialog1(int id, QSqlTableModel* m);
    void initDialog2(int id, QSqlTableModel* m);

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

protected:
    void addItemsToCombox();

    void clearAllWidget();

private:
    Ui::AdminDialog1 *ui;
    int teacherId;
    TeacherSql tsql;
    QSqlTableModel* model;
};

#endif // ADMINDIALOG1_H
