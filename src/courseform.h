#ifndef COURSEFORM_H
#define COURSEFORM_H

#include <QWidget>
#include <QSqlRecord>

namespace Ui {
class CourseForm;
}

class CourseForm : public QWidget
{
    Q_OBJECT

public:
    explicit CourseForm(QWidget *parent = 0,int identity=0,int studentId=0);
    ~CourseForm();
public:
    void setCourseRecord(const QSqlRecord& record);

    void setCourseRecord(const QSqlRecord &record,const QSqlRecord &select);

    void setSelectRecord(const QSqlRecord& record);

protected:
    void inPreViewPage();

signals:
    void acceptDecide();

private slots:
    void on_pbtYes_clicked();

private:
    Ui::CourseForm *ui;
    int mIsStduent;
    int mStudentId;
    QSqlRecord courseRecord;
    QSqlRecord selectRecord;
};

#endif // COURSEFORM_H
