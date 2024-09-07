#ifndef SMALLCHOOSEFORM_H
#define SMALLCHOOSEFORM_H

#include <QWidget>
#include "sqlmodelall.h"

namespace Ui {
class smallChooseForm;
}

class smallChooseForm : public QWidget
{
    Q_OBJECT
public:
    explicit smallChooseForm(QWidget *parent = 0,bool isAdmin=false);
    ~smallChooseForm();

private slots:
    void on_tableViewAdmin_doubleClicked(const QModelIndex &index);

    void on_tableViewDepart_doubleClicked(const QModelIndex &index);

    void on_cbxInterval_clicked(bool checked);

    void on_cbxDesOrder_clicked(bool checked);

    void on_cbxChangColWidth_clicked(bool checked);

    void on_pbtAddAnnounce_clicked();

    void on_pbtSubAnnounce_clicked();

    void on_updateAnnounce_clicked();

    void on_tableViewAdmin_clicked(const QModelIndex &index);

    void on_tableViewDepart_clicked(const QModelIndex &index);

private:
    Ui::smallChooseForm *ui;

    AnnounceSql announce;
    bool mIsAdmin;
    QSqlTableModel *adminModel;
    QSqlTableModel *departModel;
};

#endif // SMALLCHOOSEFORM_H
