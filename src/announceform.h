#ifndef ANNOUNCEFORM_H
#define ANNOUNCEFORM_H

#include <QWidget>
#include "sqlmodelall.h"

namespace Ui {
class AnnounceForm;
}


class AnnounceForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnnounceForm(QWidget *parent = 0,bool isHeadSys=false,
                          bool isAdmin=false);
    ~AnnounceForm();

public:
    void insertRecord(const QSqlRecord& record);

    void showRecord(const QSqlRecord& record);

    void updateRecord(const QSqlRecord& record);

    QSqlRecord getSingleRecord() const{
        return mRecord;
    }

private:
    //opKind = 2表示展示，1表示编辑，0表示插入
    void updateControlTools();

    void saveValueToRecord();

    void closeEvent(QCloseEvent *event){
        emit regectSignal();
        return QWidget::closeEvent(event);
    }

signals:
    void accptSignal();
    void regectSignal();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::AnnounceForm *ui;
    QSqlRecord mRecord;
    bool mIsAdmin;
    bool mIsHeadSys;

    AnnounceSql announce;
};

#endif // ANNOUNCEFORM_H
