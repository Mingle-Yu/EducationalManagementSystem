#include "sqlmodelall.h"

/*************************************公告表**********************************************/
/****************************************************************************************/
void AnnounceSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"公告序号");
    model->setHeaderData(1,Qt::Horizontal,"公告类型");
    model->setHeaderData(2,Qt::Horizontal,"院   系");
    model->setHeaderData(3,Qt::Horizontal,"公告内容");
    model->setHeaderData(4,Qt::Horizontal,"公告联系人");
    model->setHeaderData(5,Qt::Horizontal,"联系人电话");
    model->setHeaderData(6,Qt::Horizontal,"联系人邮箱");
    model->setHeaderData(7,Qt::Horizontal,"发布日期");
}

/*************************************管理员表**********************************************/
/****************************************************************************************/
void AdministratorSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"编 号");
    model->setHeaderData(1,Qt::Horizontal,"密 码");
    model->setHeaderData(2,Qt::Horizontal,"姓 名");
    model->setHeaderData(3,Qt::Horizontal,"性 别");
    model->setHeaderData(4,Qt::Horizontal,"年 龄");
    model->setHeaderData(5,Qt::Horizontal,"电 话");
    model->setHeaderData(6,Qt::Horizontal,"邮 箱");
}

/*************************************课程表**********************************************/
/****************************************************************************************/
void CourseTableSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"课程编号");
    model->setHeaderData(1,Qt::Horizontal,"教师编号");
    model->setHeaderData(2,Qt::Horizontal,"专   业");
    model->setHeaderData(3,Qt::Horizontal,"院   系");
    model->setHeaderData(4,Qt::Horizontal,"课程学期");
    model->setHeaderData(5,Qt::Horizontal,"课程类型");
    model->setHeaderData(6,Qt::Horizontal,"学   时");
    model->setHeaderData(7,Qt::Horizontal,"学   分");
    model->setHeaderData(8,Qt::Horizontal,"开课时间");
    model->setHeaderData(9,Qt::Horizontal,"结课时间");
    model->setHeaderData(10,Qt::Horizontal,"教师姓名");
    model->setHeaderData(11,Qt::Horizontal,"课程名称");
    model->setHeaderData(12,Qt::Horizontal,"上课时间");
    model->setHeaderData(13,Qt::Horizontal,"上课地点");
    model->setHeaderData(14,Qt::Horizontal,"开课人数");
    model->setHeaderData(15,Qt::Horizontal,"选课人数");
}

bool CourseTableSql::deleteSingleRecord(const int &id)
{
    QString sqlmtr=QObject::tr("delete from select_course_table where courseId = %1").arg(id);
    myProgram->getQueryList(sqlmtr);
    if(myProgram->deleteSingleRecord(mTable,mIdName,id))
        return true;
    else
        return false;
}

/*************************************评教表**********************************************/
/****************************************************************************************/
void EvaluateTeacherSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"序   号");
    model->setHeaderData(1,Qt::Horizontal,"学生学号");
    model->setHeaderData(2,Qt::Horizontal,"课程编号");
    model->setHeaderData(3,Qt::Horizontal,"教师编号");
    model->setHeaderData(4,Qt::Horizontal,"课程学期");
    model->setHeaderData(5,Qt::Horizontal,"专   业");
    model->setHeaderData(6,Qt::Horizontal,"院   系");
    model->setHeaderData(7,Qt::Horizontal,"课程名称");
    model->setHeaderData(8,Qt::Horizontal,"教学态度");
    model->setHeaderData(9,Qt::Horizontal,"教学内容");
    model->setHeaderData(10,Qt::Horizontal,"教学方法");
    model->setHeaderData(11,Qt::Horizontal,"教学效果");
    model->setHeaderData(12,Qt::Horizontal,"建   议");
    model->setHeaderData(13,Qt::Horizontal,"总   分");
}

/*************************************成绩表**********************************************/
/****************************************************************************************/
void ScoreSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"序   号");
    model->setHeaderData(1,Qt::Horizontal,"课程编号");
    model->setHeaderData(2,Qt::Horizontal,"学生学号");
    model->setHeaderData(3,Qt::Horizontal,"教师编号");
    model->setHeaderData(4,Qt::Horizontal,"课程学期");
    model->setHeaderData(5,Qt::Horizontal,"分   数");
    model->setHeaderData(6,Qt::Horizontal,"通过状态");
    model->setHeaderData(7,Qt::Horizontal,"补考次数");
    model->setHeaderData(8,Qt::Horizontal,"学生姓名");
    model->setHeaderData(9,Qt::Horizontal,"老师姓名");
    model->setHeaderData(10,Qt::Horizontal,"课程名称");
}

/*************************************选课表**********************************************/
/****************************************************************************************/
void SelectCourseSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"序   号");
    model->setHeaderData(1,Qt::Horizontal,"课程编号");
    model->setHeaderData(2,Qt::Horizontal,"教师姓名");
    model->setHeaderData(3,Qt::Horizontal,"学生姓名");
    model->setHeaderData(4,Qt::Horizontal,"课程学期");
    model->setHeaderData(5,Qt::Horizontal,"选课状态");
    model->setHeaderData(6,Qt::Horizontal,"课程名称");
}

QSqlRelationalTableModel *SelectCourseSql::getRelationModel(QObject *parent, QTableView *tableView, QItemSelectionModel *selectModel)
{
    Q_UNUSED(tableView)
    Q_UNUSED(selectModel)

    QSqlRelationalTableModel *model=myProgram->getRelationModel(mTable,parent);
    setHeadData(model);
    model->setRelation(1,QSqlRelation("CourseTable","courseId","courseName"));
    model->setRelation(2,QSqlRelation("TeacherTable","teacherId","teacherName"));
    model->setRelation(1,QSqlRelation("StudentTable","studentId","studentName"));

    return model;
}

/*************************************学生表**********************************************/
/****************************************************************************************/
void StudentSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"学   号");
    model->setHeaderData(1,Qt::Horizontal,"专   业");
    model->setHeaderData(2,Qt::Horizontal,"院   系");
    model->setHeaderData(3,Qt::Horizontal,"密   码");
    model->setHeaderData(4,Qt::Horizontal,"姓   名");
    model->setHeaderData(5,Qt::Horizontal,"性   别");
    model->setHeaderData(6,Qt::Horizontal,"年   龄");
    model->setHeaderData(7,Qt::Horizontal,"总 学 分");
}

bool StudentSql::deleteSingleRecord(const int &id)
{
    QString sqlmtr=QObject::tr("delete from select_course_table where studentId = %1").arg(id);
    myProgram->getQueryList(sqlmtr);
    if(myProgram->deleteSingleRecord(mTable,mIdName,id))
        return true;
    else
        return false;
}

/*************************************教师表**********************************************/
/****************************************************************************************/
void TeacherSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"编   号");
    model->setHeaderData(1,Qt::Horizontal,"密   码");
    model->setHeaderData(2,Qt::Horizontal,"姓   名");
    model->setHeaderData(3,Qt::Horizontal,"性   别");
    model->setHeaderData(4,Qt::Horizontal,"年   龄");
    model->setHeaderData(5,Qt::Horizontal,"院   系");
    model->setHeaderData(6,Qt::Horizontal,"职   称");
    model->setHeaderData(7,Qt::Horizontal,"电   话");
    model->setHeaderData(8,Qt::Horizontal,"邮   箱");
    model->setHeaderData(9,Qt::Horizontal,"简   介");
}

bool TeacherSql::deleteSingleRecord(const int &id)
{
    QString sqlstr=QObject::tr("UPDATE course_table SET teacherId = NULL, teacherName = NULL where teacherId = %1").arg(id);
    myProgram->getQueryList(sqlstr);
    QString sqlmtr=QObject::tr("delete from select_course_table where  teacherId = %1").arg(id);
    myProgram->getQueryList(sqlmtr);
    if(myProgram->deleteSingleRecord(mTable,mIdName,id))
        return true;
    else
        return false;
}


/*************************************专业表**********************************************/
/****************************************************************************************/
void MajorSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"专业编号");
    model->setHeaderData(1,Qt::Horizontal,"院系编号");
    model->setHeaderData(2,Qt::Horizontal,"专业名称");
    model->setHeaderData(3,Qt::Horizontal,"毕业总学分");
}

/*************************************院系表**********************************************/
/****************************************************************************************/
void DepartmentSql::setHeadData(QSqlQueryModel *model)
{
    model->setHeaderData(0,Qt::Horizontal,"院系编号");
    model->setHeaderData(1,Qt::Horizontal,"院系名称");
}
