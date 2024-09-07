#ifndef ADMINSCOREFORM_H
#define ADMINSCOREFORM_H

#include <QWidget>

#include "sqlmodelall.h"
#include "globaldelegate.h"

namespace Ui {
class AdminScoreForm;
}

class AdminScoreForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScoreForm(QWidget *parent = 0);
    ~AdminScoreForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AdminScoreForm *ui;
    QSqlTableModel *model;
    ReadOnlyDelegate readOnly;
    PassDelegate passQues;
};

#endif // ADMINSCOREFORM_H
