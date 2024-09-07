#ifndef ADMINDIALOG3_H
#define ADMINDIALOG3_H

#include <QDialog>
#include <QMap>
#include "sqlmodelall.h"
#include <QMessageBox>

namespace Ui {
class AdminDialog3;
}

class AdminDialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog3(QWidget *parent = nullptr);
    ~AdminDialog3();
//    bool isValid();
    void initDialog1(int id, QSqlTableModel* m);
    void initDialog2(int id, QSqlTableModel* m);

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

    void on_comboBoxDepartment_currentIndexChanged(int index);

    void on_lineEditTeacherId_returnPressed();

private:
    Ui::AdminDialog3 *ui;
    int courseId;
    CourseTableSql csql;
    QSqlTableModel* model;
    QList<QString> nameList;
    QMap<QString,QString> mp;
};

#endif // ADMINDIALOG3_H
