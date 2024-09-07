#include "executepro.h"

#include <QMessageBox>
#include <QDebug>

ExecutePro::ExecutePro()
{
    DB = QSqlDatabase::addDatabase("QODBC");
    DB.setHostName("127.0.0.1");  //连接本地主机
    DB.setDatabaseName("数据库名");
    DB.setUserName("用户名");
    DB.setPassword("密码");

    if(!DB.open()){
        QMessageBox::warning(nullptr,"警告","打开数据库失败，原因为："+DB.lastError().text());
        qWarning("wrong get Database");
    }
    else {
        qDebug("数据库打开成功");
    }
}

ExecutePro::~ExecutePro()
{
    DB.close();
}

QSqlQueryModel *ExecutePro::getQueryModel(const QString &table, QObject *parent)
{
    QSqlQueryModel *model=new QSqlQueryModel(parent);
    model->setQuery(QObject::tr("select * from %1").arg(table));

    if(model->lastError().isValid()){
        QMessageBox::warning(nullptr,"警告","打开数据库失败，原因为："+model->lastError().text());
        return nullptr;
    }
    return model;
}

QSqlTableModel *ExecutePro::getTableModel(const QString &table, QObject *parent)
{
    QSqlTableModel *model=new QSqlTableModel(parent,getDatabase());
    model->setTable(table);
    if(model->lastError().isValid()){
        qDebug()<<model->lastError().text();
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if(model->select()==false){
        QMessageBox::warning(0,"警告","获取数据表失败，原因为："+model->lastError().text());
        return nullptr;
    }

    return model;
}

QSqlRelationalTableModel *ExecutePro::getRelationModel(const QString &table, QObject *parent)
{
    QSqlRelationalTableModel *model=new QSqlRelationalTableModel(parent,getDatabase());
    model->setTable(table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if(model->select()==false){
        QMessageBox::warning(0,"警告","获取数据表失败，原因为："+model->lastError().text());
        return nullptr;
    }

    return model;
}

QSqlQuery ExecutePro::getQueryList(const QString& sqlstr)
{
    QSqlQuery query(getDatabase());

    if(!query.exec(sqlstr)){
        QMessageBox::warning(0,"警告","获取数据表失败，原因为："+query.lastError().text());
        qWarning("wrong get QSqlQuery");
    }

    return query;
}

QSqlRecord ExecutePro::getNullRecordModel(const QString &table,const QString& idName)
{
    QSqlQuery query(getDatabase());
    QString sqlstr=QObject::tr(" select * from %1 where %2=%3 ;").arg(table).arg(idName).arg(-1);
    query.exec(sqlstr);
    return query.record();
}

bool ExecutePro::insertSingleRecord(const QString &table,const QSqlRecord &record)
{
    QSqlQuery query(getDatabase());

    int countCol=record.count();

    //先设置prepare语句
    QString sqlstr=QObject::tr(" insert into %1 (").arg(table);
    for(int i=1;i<countCol-1;++i)
        sqlstr+=record.fieldName(i)+",";

    sqlstr+=record.fieldName(countCol-1)+")values(";

    for(int i=1;i<countCol-1;++i){
        QString colName=record.fieldName(i);
        sqlstr+=QObject::tr(":%1,").arg(colName);
    }

    sqlstr+=QObject::tr(":%1)").arg(record.fieldName(countCol-1));

    query.prepare(sqlstr);

    //连接绑定值
    for(int i=1;i<countCol;++i){
        QString colName=record.fieldName(i);
        query.bindValue(":"+colName,record.value(i));
    }

    //执行
    if(!query.exec()){
        QMessageBox::warning(0,"警告","插入语句执行失败，原因为："+query.lastError().text());
        return false;
    }
    else{
        return true;
    }

}

bool ExecutePro::updateSingleRecord(const QString &table, const QSqlRecord &record)
{
    bool ok=false;
    int id=record.value(0).toInt(&ok);
    if(!ok){
        QMessageBox::critical(0,"出错",QObject::tr("插入时，将%1中的id转为int发生错误！").arg(table));
        return false;
    }

    QSqlQuery query(getDatabase());

    int countCol=record.count();

    //先设置prepare语句
    QString sqlstr=QObject::tr(" update %1 set ").arg(table);
    for(int i=1;i<countCol-1;++i){
        QString colName=record.fieldName(i);
        sqlstr+=QObject::tr(" %1=:%2,").arg(colName).arg(colName);
    }

    QString colName=record.fieldName(countCol-1);
    QString idName=record.fieldName(0);
    sqlstr+=QObject::tr(" %1=:%2 where %3=%4 ").arg(colName).arg(colName).arg(idName).arg(id);

    query.prepare(sqlstr);

    //连接绑定值
    for(int i=1;i<countCol;++i){
        QString colName=record.fieldName(i);
        query.bindValue(":"+colName,record.value(i));
    }

    //执行
    if(!query.exec()){
        QMessageBox::warning(0,"警告","更新语句执行失败，原因为："+query.lastError().text());
        return false;
    }
    else{
        return true;
    }

}

bool ExecutePro::deleteSingleRecord(const QString &table, const QString &idName, const int &id)
{
    QSqlQuery query(getDatabase());
    QString sqlstr=QObject::tr(" delete from %1 where %2=%3").arg(table).arg(idName).arg(id);

    //执行
    if(!query.exec(sqlstr)){
        QMessageBox::warning(0,"警告","删除语句执行失败，原因为："+query.lastError().text());
        qDebug()<<query.lastError().text();
        return false;
    }
    else{
        return true;
    }
}

QSqlRecord ExecutePro::findSingleRecord(const QString &table, const QString &idName, const int &id)
{
    QString sqlstr=QObject::tr(" select * from %1 where %2=%3").arg(table).arg(idName).arg(id);
    QSqlQuery query(getDatabase());

    //执行
    if(!query.exec(sqlstr)){
        QMessageBox::warning(0,"警告","查找语句执行失败，原因为："+query.lastError().text());
        qWarning(query.lastError().text().toUtf8().constData());
        return QSqlRecord();
    }
    else{
        query.first();
        return query.record();
    }
}
