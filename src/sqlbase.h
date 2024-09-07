#ifndef SQLBASE_H
#define SQLBASE_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QItemSelectionModel>
#include "executepro.h"

extern ExecutePro *myProgram;

class SqlBase
{

protected:
    const QString mTable;   //  表名
    const QString mIdName;  //  表的主键名

protected:
    virtual void setHeadData(QSqlQueryModel *model)=0;

public:
    SqlBase(const QString& table,const QString& idName):mTable(table),mIdName(idName){}


    virtual QSqlQueryModel* getQueryModel(QObject *parent,QTableView *tableView=nullptr,
                                          QItemSelectionModel *selectModel=nullptr){
        QSqlQueryModel *model = myProgram->getQueryModel(mTable,parent);
        setHeadData(model);
        if(!tableView && !selectModel){}
        return model;
    }


    virtual QSqlTableModel* getTableModel(QObject *parent,QTableView *tableView=nullptr,
                                          QItemSelectionModel *selectModel=nullptr){
        QSqlTableModel *model = myProgram->getTableModel(mTable,parent);
        setHeadData(model);
        if(!tableView && !selectModel){}
        return model;
    }

    virtual QSqlRelationalTableModel* getRelationModel(QObject *parent,QTableView *tableView=nullptr,
                                                       QItemSelectionModel *selectModel=nullptr){
        QSqlRelationalTableModel *model= myProgram->getRelationModel(mTable,parent);
        setHeadData(model);
        if(!tableView && !selectModel){}
        return model;
    }

    virtual QSqlQuery getQueryList(const QString& sqlstr){
        return myProgram->getQueryList(sqlstr);
    }

    virtual QSqlRecord getNullRecordModel(){
        return  myProgram->getNullRecordModel(mTable,mIdName);
    }

    virtual bool insertSingleRecord(const QSqlRecord& record){
        return myProgram->insertSingleRecord(mTable,record);
    }

    virtual bool updateSingleRecord(const QSqlRecord& record){
        return myProgram->updateSingleRecord(mTable,record);
    }

    virtual bool deleteSingleRecord(const int& id){
        return myProgram->deleteSingleRecord(mTable,mIdName,id);
    }

    virtual const QSqlRecord findSingleRecord(const int& id){
        return myProgram->findSingleRecord(mTable,mIdName,id);
    }

    virtual QString getTableName() const{
        return mTable;
    }

    virtual QString getIdName() const{
        return mIdName;
    }


};

#endif // SQLBASE_H


