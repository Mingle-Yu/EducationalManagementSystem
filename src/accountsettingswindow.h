#ifndef ACCOUNTSETTINGSWINDOW_H
#define ACCOUNTSETTINGSWINDOW_H

#include <QWidget>
#include "sqlmodelall.h"

namespace Ui {
class AccountSettingsWindow;
}

class AccountSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AccountSettingsWindow(int Id, QWidget *parent = nullptr);
    ~AccountSettingsWindow();

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::AccountSettingsWindow *ui;
    int adminId;    //  管理员编号（账号）
    AdministratorSql admin;
};

#endif // ACCOUNTSETTINGSWINDOW_H
