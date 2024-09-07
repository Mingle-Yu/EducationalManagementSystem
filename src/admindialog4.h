#ifndef ADMINDIALOG4_H
#define ADMINDIALOG4_H

#include <QDialog>
#include "sqlmodelall.h"
#include <QMessageBox>

namespace Ui {
class AdminDialog4;
}

class AdminDialog4 : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog4(QWidget *parent = nullptr);
    ~AdminDialog4();
    //    bool isValid();
    void initDialog1(int id, QSqlTableModel* m);
    void initDialog2(int id, QSqlTableModel* m);

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::AdminDialog4 *ui;

    int evaluateId;
    EvaluateTeacherSql etsql;
    QSqlTableModel* model;
};

#endif // ADMINDIALOG4_H
