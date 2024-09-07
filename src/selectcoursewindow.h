#ifndef SELECTCOURSEWINDOW_H
#define SELECTCOURSEWINDOW_H

#include "sqlmodelall.h"
#include <QWidget>

namespace Ui {
class SelectCourseWindow;
}

class SelectCourseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCourseWindow(int id,QWidget *parent = nullptr);
    ~SelectCourseWindow();

private:
    Ui::SelectCourseWindow *ui;
    int studentId;
};

#endif // SELECTCOURSEWINDOW_H
