#include "selectcoursewindow.h"
#include "ui_selectcoursewindow.h"

SelectCourseWindow::SelectCourseWindow(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectCourseWindow),studentId(id)
{
    ui->setupUi(this);


}

SelectCourseWindow::~SelectCourseWindow()
{
    delete ui;
}
