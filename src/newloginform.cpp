#include "newloginform.h"
#include "ui_newloginform.h"

#include <QSettings>
#include <QMessageBox>
#include <QPainter>
#include <QGraphicsBlurEffect>


NewLoginForm::NewLoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewLoginForm)
{
    ui->setupUi(this);

    qApp->setStyleSheet("QMainWindow {background-color: rgb(181, 255, 200); }");

    mPix.load(":/Image/my photos/login.png");

    this->setWindowFlags(Qt::FramelessWindowHint);

    int w=ui->groupBox->width();
    int h=ui->groupBox->height();

    setFixedSize(800,600);
    ui->groupBox->move((this->width()-w)/2,(this->height()-h)/2);

    readFromSettings();

    if(mUserName!=""){
        move(mPos);
        ui->editName->setText(mUserName);
    }

}

NewLoginForm::~NewLoginForm()
{
    delete ui;
}

void NewLoginForm::toShow()
{
    this->show();

    ui->editName->setReadOnly(0);
    ui->editPassword->setReadOnly(0);

}

void NewLoginForm::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        QPoint point=event->globalPos()-mLastPos;
        this->move(point);
    }
}

void NewLoginForm::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        mLastPos=event->globalPos()-this->pos();
    }
}

void NewLoginForm::on_pbtYes_clicked()
{
    if(ui->editName->text().trimmed()==""  || ui->editPassword->text().trimmed()==""){
        QMessageBox msgBox;
        msgBox.move(pos());
        msgBox.setStyleSheet("QMessageBox{background-color:yellow;}");
        msgBox.setIconPixmap(QPixmap(":/Image/my photos/hint.png"));
        msgBox.setWindowIcon(QIcon(":/Image/my photos/warning.png"));
        msgBox.setWindowTitle("警告");
        msgBox.setText("账号和密码都不能为空。");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.exec();
        return;
    }


    //***********************************************************************
    //**********************基本信息输入完成************************************
    //***********************************************************************
    bool ok=false;
    int memberId=ui->editName->text().toInt(&ok);

    //此时账户密码身份都不能更改
    ui->editName->setReadOnly(1);
    ui->editPassword->setReadOnly(1);


    //输入的编号有错误，不能转成int
    if(!ok){
        QMessageBox::critical(this,"错误","账户编号输入异常",QMessageBox::Ok);
        //恢复可以编辑
         ui->editName->setReadOnly(0);
         ui->editPassword->setReadOnly(0);
        return;
    }

    //找到编号相同的记录
    QSqlRecord record;
    QString passName;
    int identity=0;
    if(ui->rbtTeacher->isChecked()) identity=1;
    else if(ui->rbtStduent->isChecked()) identity=2;
    switch (identity) {
    //管理员
    case 0: {
        AdministratorSql admin;
        record=admin.findSingleRecord(memberId);
        passName="adminPassword";
        break;
        }
    //教师
    case 1: {
        TeacherSql teacher;
        record=teacher.findSingleRecord(memberId);
        passName="teacherPassword";
        break;
        }
    //学生
    case 2: {
        StudentSql student;
        record=student.findSingleRecord(memberId);
        passName="studentPassword";
        break;
        }
    }

    //记录为空，表示没有找到记录
    if(record.isEmpty() || record.isNull(0)) {
        QMessageBox::critical(this,"错误","账户不存在，请检查账户输入或身份选择是否正确！",QMessageBox::Ok);
        //恢复可以编辑
         ui->editName->setReadOnly(0);
         ui->editPassword->setReadOnly(0);
        return;
    }


    //输入密码不正确
    if(record.value(passName).toString()!=ui->editPassword->text()){
        QMessageBox msgBox;
        msgBox.move(pos());
        msgBox.setStyleSheet("QMessageBox{background-color:yellow;}");
        msgBox.setIconPixmap(QPixmap(":/Image/my photos/hint.png"));
        msgBox.setWindowIcon(QIcon(":/Image/my photos/warning.png"));
        msgBox.setWindowTitle("警告");
        msgBox.setText("密码错误，请确认输入密码是否正确");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.exec();
        //恢复可以编辑
         ui->editName->setReadOnly(0);
         ui->editPassword->setReadOnly(0);
    }
    else
    {
        mPos=pos();
        mUserName=ui->editName->text();
        writeToSetting();

        if(ui->rbtAdmin->isChecked())
        {
            int id = record.value("adminId").toInt();
            AdminWindow* admin = new AdminWindow(id);

            admin->show();
            this->hide();
            connect(admin,&AdminWindow::isClosing,this,&NewLoginForm::toShow);
        }
        else if(ui->rbtTeacher->isChecked())
        {
            int id = record.value("teacherId").toInt();
            tea_MainWindow* teacher = new tea_MainWindow(id);

            teacher->show();
            this->hide();
            connect(teacher,&tea_MainWindow::isClosing,this,&NewLoginForm::toShow);
        }
        else if (ui->rbtStduent->isChecked())
        {
            int id = record.value("studentId").toInt();
            stu_MainWindow* student = new stu_MainWindow(id);

            student->show();
            this->hide();
            connect(student,&stu_MainWindow::isClosing,this,&NewLoginForm::toShow);
        }
    }
}

void NewLoginForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    int w=this->width();
    int h=this->height();
    painter.drawPixmap(0,0,w,h,mPix.scaledToWidth(w*2));
}

void NewLoginForm::readFromSettings()
{
    QSettings mySettings("myProject","myLoginSettings");
    mPos  =  mySettings.value("startPos",pos()).toPoint();
    mUserName = mySettings.value("userName","").toString();
}

void NewLoginForm::writeToSetting()
{
    QSettings mySettings("myProject","myLoginSettings");
    mySettings.setValue("startPos",mPos);
    mySettings.setValue("userName",mUserName);
}


void NewLoginForm::on_pbtNo_clicked()
{
    this->close();
}
