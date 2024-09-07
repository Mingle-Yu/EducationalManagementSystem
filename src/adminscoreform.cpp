#include "adminscoreform.h"
#include "ui_adminscoreform.h"

#include <QMessageBox>

AdminScoreForm::AdminScoreForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminScoreForm)
{
    ui->setupUi(this);

    ScoreSql scoreList;
    model=scoreList.getTableModel(this);

    ui->tableView->setModel(model);
    model->setFilter(" score is not null");
    ui->tableView->setColumnHidden(model->fieldIndex("studentName"),1);
    ui->tableView->setColumnHidden(model->fieldIndex("teacherName"),1);

    ui->tableView->setItemDelegateForColumn(model->fieldIndex("courseId"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("studentId"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("teacherId"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("courseTerm"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("courseName"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("studentReTryNum"),&readOnly);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("studentPass"),&passQues);
}

AdminScoreForm::~AdminScoreForm()
{
    delete ui;
}

void AdminScoreForm::on_pushButton_clicked()
{
    int row=model->rowCount();
    int col=model->fieldIndex("score");
    int itemCol=model->fieldIndex("studentPass");
    int tryCol=model->fieldIndex("studentReTryNum");
    for(int i=0;i<row;++i)
    {
        QModelIndex index=model->index(i,col);
        QModelIndex tryIndex=model->index(i,tryCol);
        QVariant data=model->data(tryIndex,Qt::EditRole);//是否补考

        float score=model->data(index,Qt::EditRole).toFloat();

        if(score<60){
            QModelIndex newIndex=model->index(i,itemCol);
            model->setData(newIndex,0,Qt::EditRole);

            if(data.isNull()){
                model->setData(tryIndex,1,Qt::EditRole);
            }
        }
        else{
            QModelIndex newIndex=model->index(i,itemCol);
            model->setData(newIndex,1,Qt::EditRole);

            if(data.isNull()){
                model->setData(tryIndex,0,Qt::EditRole);
            }
        }

    }
}

void AdminScoreForm::on_pushButton_2_clicked()
{
    if(model->isDirty())
    {
        int ret = QMessageBox::question(this,"上传","确认上传成绩？",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::No) return;

        model->submitAll();
    }

}
