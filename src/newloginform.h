#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H

#include <QWidget>
#include <QPointF>
#include <QPixmap>
#include <QMouseEvent>
#include "adminwindow.h"
#include "tea_mainwindow.h"
#include "stu_mainwindow.h"

namespace Ui {
class NewLoginForm;
}

class NewLoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewLoginForm(QWidget *parent = 0);
    ~NewLoginForm();


private slots:
    void toShow();
private:

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    void readFromSettings();

    void writeToSetting();

private slots:
    void on_pbtYes_clicked();

    void on_pbtNo_clicked();

private:
    Ui::NewLoginForm *ui;

    QPixmap mPix;
    QPoint mLastPos;
    QString mUserName;

    int mTryNum=0;
    QPoint mPos;

};

#endif // NEWLOGINFORM_H
