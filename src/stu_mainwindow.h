//ѧ��������ͷ�ļ�
#ifndef STU_MAINWINDOW_H
#define STU_MAINWINDOW_H

#include "qsqldatabase.h"
#include "qsqltablemodel.h"
#include "announceshowwindow.h"
#include "sqlmodelall.h"
#include<QSqlTableModel>
#include <QMainWindow>
#include<QSqlDatabase>
#include "scoreform.h"
#include "announceform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class stu_MainWindow; }
QT_END_NAMESPACE

class stu_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    stu_MainWindow(int id=1,QWidget *parent = nullptr);
    ~stu_MainWindow();

private slots:
    void on_actionAnnounce_triggered();//��������ť

    void on_actionEvaluate_triggered();//���̰�ť��ѧ�����̣�

    void on_actionSelect_triggered();//ѡ�ΰ�ť��ѧ��ѡ��/�˿Σ�

    void on_actionScore_triggered();//�ɼ���ť��ѧ���鿴�ɼ���

    void on_actionCourse_triggered();//�γ̱�ť��ѧ���鿴�γ̱�

    void on_actionChange_triggered();//�޸���Ϣ��ť��ѧ���޸���Ϣ��
    void closeChildWindow(int index);

    void on_stu_tabWidget_tabCloseRequested(int index);

signals:
    void isClosing();

private:
    void closeEvent(QCloseEvent *event);

    void paintEvent(QPaintEvent *event);

    void readFromSettings();

    void writeToSetting();

private:
    Ui::stu_MainWindow *ui;
    int studentId;
    StudentSql student;
    QSqlTableModel* model;

    QPixmap pixmap;
    QPoint mPos;//��ʼλ��
    QSize mSize;//��ʼ��С
};
#endif // STU_MAINWINDOW_H
