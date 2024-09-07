#ifndef ANNOUNCESHOWWINDOW_H
#define ANNOUNCESHOWWINDOW_H

#include <QWidget>
#include"sqlmodelall.h"

namespace Ui {
class announceShowWindow;
}

class announceShowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit announceShowWindow(QWidget *parent = nullptr);
    ~announceShowWindow();

private slots:
    void on_searchButton_clicked();

private:
    Ui::announceShowWindow *ui;
    int studentId;
    int announceId;
    AnnounceSql announce;
    QSqlTableModel* model;
};

#endif // ANNOUNCESHOWWINDOW_H
