#ifndef SQLMODELALL_H
#define SQLMODELALL_H

#include "sqlbase.h"
#include <QSettings>

/******************************************************************************/
/**********************************公告表***************************************/
class AnnounceSql:public SqlBase
{

protected:
    void setHeadData(QSqlQueryModel *model);
public:
    AnnounceSql():SqlBase("announce_table","announceId"){}
};
/******************************************************************************/
/**********************************管理员***************************************/
class AdministratorSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    AdministratorSql():SqlBase("administrator_table","adminId"){}
};

/******************************************************************************/
/**********************************课程表***************************************/
class CourseTableSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    CourseTableSql():SqlBase("course_table","courseId"){}
    bool deleteSingleRecord(const int &id);
};

/******************************************************************************/
/**********************************评教表***************************************/
class EvaluateTeacherSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    EvaluateTeacherSql():SqlBase("evaluate_teacher_table","evaluateId"){}
};

/******************************************************************************/
/**********************************成绩表***************************************/
class ScoreSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    ScoreSql():SqlBase("score_table","scoreId"){}
};

/******************************************************************************/
/**********************************选课表***************************************/
class SelectCourseSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    SelectCourseSql():SqlBase("select_course_table","selectId"){}

    QSqlRelationalTableModel* getRelationModel(QObject *parent, QTableView *tableView=nullptr, QItemSelectionModel *selectModel=nullptr);
};

/******************************************************************************/
/**********************************学生表***************************************/
class StudentSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    StudentSql():SqlBase("student_table","studentId"){}

    bool deleteSingleRecord(const int &id);
};

/******************************************************************************/
/**********************************教师表***************************************/
class TeacherSql:public SqlBase
{
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    TeacherSql():SqlBase("teacher_table","teacherId"){}

    bool deleteSingleRecord(const int &id);
};

class DepartmentSql: public SqlBase {
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    DepartmentSql():SqlBase("department_table","departmentId"){}
};

class MajorSql: public SqlBase {
protected:
    void setHeadData(QSqlQueryModel *model);
public:
    MajorSql():SqlBase("major_table","majorId"){}
};

#endif // SQLMODELALL_H
