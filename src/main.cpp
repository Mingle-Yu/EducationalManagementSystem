#include "newloginform.h"

#include <QApplication>
#include <QStyle>

#include "adminwindow.h"
#include "sqlmodelall.h"

ExecutePro* myProgram;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle("");

    myProgram = new ExecutePro();
    NewLoginForm login;
    login.show();


    return a.exec();
}
