#ifndef SELECTCOURSEFORM_H
#define SELECTCOURSEFORM_H

#include <QWidget>

namespace Ui {
class SelectCourseForm;
}

class SelectCourseForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCourseForm(QWidget *parent,int humanId, int isStudent=0);
    ~SelectCourseForm();

protected:
    QString getStudentSqlstr();

    QString getOtherSqlstr();

    void setRecord();

private slots:
    void on_rbtPreView_clicked();

    void on_rbtSelected_clicked();

    void on_rbtAll_clicked();

    void on_rbtMyMajor_clicked();

    void on_rbtPublic_clicked();

    void on_rbtOtherMajor_clicked();

private:
    Ui::SelectCourseForm *ui;
    int mIsStudent;
    int mIsAdmin;
    int mStudenId;
    int mTeacherId;
};

#endif // SELECTCOURSEFORM_H
