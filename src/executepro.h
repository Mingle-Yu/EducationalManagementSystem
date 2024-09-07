#ifndef EXECUTEPRO_H
#define EXECUTEPRO_H

#include <QObject>
#include <QVector>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

class ExecutePro
{

private:
    QSqlDatabase DB;

protected:
    QSqlDatabase& getDatabase() { return DB;}

public:
    ExecutePro();
    ~ExecutePro();

    QSqlQueryModel* getQueryModel(const QString& table, QObject *parent);

    QSqlTableModel* getTableModel(const QString& table, QObject *parent);

    QSqlRelationalTableModel* getRelationModel(const QString& table, QObject *parent);

    QSqlQuery getQueryList(const QString& sqlstr);

    QSqlRecord getNullRecordModel(const QString& table, const QString &idName);

    bool insertSingleRecord(const QString& table, const QSqlRecord& record);

    bool updateSingleRecord(const QString& table,const QSqlRecord& record);

    bool deleteSingleRecord(const QString& table,const QString& idName,const int& id);

    QSqlRecord findSingleRecord(const QString& table,const QString& idName,const int& id);
};

#endif // EXECUTEPRO_H
