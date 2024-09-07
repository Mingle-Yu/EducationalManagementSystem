//课程表界面
#include "coursewindow.h"
#include "ui_coursewindow.h"

CourseWindow::CourseWindow(int id, bool isStudent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseWindow),userId(id)
{
    ui->setupUi(this);

    mIsStudent=isStudent;

    model = course.getTableModel(this);   //显示课程表


    QMap<int,int> mp;

    if(mIsStudent==false)
    {
        model->setFilter(tr(" teacherId = %1 ").arg(userId));
    }
    else
    {
        SelectCourseSql select;

        QSqlQuery query = select.getQueryList(tr(" select * from %1 where studentId = %2 and selectStatus = 2 ").arg(select.getTableName()).arg(userId));

        if(query.first())
        {
            do{
                QSqlRecord record = query.record();
                int id = record.value("courseId").toInt();
                mp.insert(id,id);
            }while(query.next());
        }

        for(int i=0;i<model->rowCount();++i)
        {
            QModelIndex index = model->index(i,0);

            int id = model->data(index).toInt();

            if(mp.count(id)==0) ui->coursetableView->setRowHidden(i,1);
        }
    }

    model->select();
    ui->coursetableView->setModel(model);
    ui->coursetableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if(mIsStudent)
    {
        for(int i=0;i<model->rowCount();++i)
        {
            QModelIndex index = model->index(i,0);

            int id = model->data(index).toInt();

            if(mp.count(id)==0) ui->coursetableView->setRowHidden(i,1);
        }
    }

    ui->coursetableView->setColumnHidden(0,1);
    ui->coursetableView->setColumnHidden(1,1);
    ui->coursetableView->setColumnHidden(2,1);
    ui->coursetableView->setColumnHidden(3,1);
    ui->coursetableView->setColumnHidden(5,1);


}

CourseWindow::~CourseWindow()
{
    delete ui;
}
