#ifndef TEA_MAINWINDOW_H
#define TEA_MAINWINDOW_H

//��ʦ������ͷ�ļ�
#include "sqlmodelall.h"
#include <QMainWindow>
#include "scoreform.h"
#include "announceform.h"

namespace Ui {
class tea_MainWindow;
}

class tea_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tea_MainWindow(int id=1,QWidget *parent = nullptr);
    ~tea_MainWindow();

private slots:

    void on_actionScore_2_triggered();//�ɼ���ť����ʦ�޸ĳɼ���

    void on_actionEvaluate_2_triggered();//���̰�ť����ʦ�鿴���̽�����

    void on_actionCourse_2_triggered();//�γ̱���ť����ʦ�鿴�ڿα���

    void on_actionAnnounce_2_triggered();//��������ť����ʦ�鿴��������

    void on_actionChange_2_triggered();//�޸���Ϣ��ť����ʦ�޸���Ϣ��

    void closeChildWindow(int index);

    void on_actiontea_SelectCourse_triggered();

    void on_tea_tabWidget_tabCloseRequested(int index);

signals:
    void isClosing();

private:
    void closeEvent(QCloseEvent *event);

    void paintEvent(QPaintEvent *event);

    void readFromSettings();

    void writeToSetting();

private:
    Ui::tea_MainWindow *ui;
    TeacherSql teacher;
    QSqlTableModel* model;
    int teacherId;

    QPixmap pixmap;
    QPoint mPos;//初始位置
    QSize mSize;//初始大小
};

#endif // TEA_MAINWINDOW_H
