QT += core gui sql charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountsettingswindow.cpp \
    admindialog1.cpp \
    admindialog2.cpp \
    admindialog3.cpp \
    admindialog4.cpp \
    adminscoreform.cpp \
    adminwindow.cpp \
    announceform.cpp \
    announceshowwindow.cpp \
    changewindow.cpp \
    courseform.cpp \
    coursemanagementwindow.cpp \
    coursewindow.cpp \
    eteachermanagementwindow.cpp \
    evaluateteacherwindow.cpp \
    executepro.cpp \
    main.cpp \
    newloginform.cpp \
    scoreform.cpp \
    scorewindow.cpp \
    selectcourseform.cpp \
    smallchooseform.cpp \
    sqlmodelall.cpp \
    stu_changewindow.cpp \
    stu_mainwindow.cpp \
    studentmanagementwindow.cpp \
    tea_evaluateteacherwindow.cpp \
    tea_mainwindow.cpp \
    teachermanagementwindow.cpp

HEADERS += \
    accountsettingswindow.h \
    admindialog1.h \
    admindialog2.h \
    admindialog3.h \
    admindialog4.h \
    adminscoreform.h \
    adminwindow.h \
    announceform.h \
    announceshowwindow.h \
    changewindow.h \
    courseform.h \
    coursemanagementwindow.h \
    coursewindow.h \
    eteachermanagementwindow.h \
    evaluateteacherwindow.h \
    executepro.h \
    globaldelegate.h \
    newloginform.h \
    scoreform.h \
    scorewindow.h \
    selectcourseform.h \
    smallchooseform.h \
    sqlbase.h \
    sqlmodelall.h \
    stu_changewindow.h \
    stu_mainwindow.h \
    studentmanagementwindow.h \
    tea_evaluateteacherwindow.h \
    tea_mainwindow.h \
    teachermanagementwindow.h

FORMS += \
    accountsettingswindow.ui \
    admindialog1.ui \
    admindialog2.ui \
    admindialog3.ui \
    admindialog4.ui \
    adminscoreform.ui \
    adminwindow.ui \
    announceform.ui \
    announceshowwindow.ui \
    changewindow.ui \
    courseform.ui \
    coursemanagementwindow.ui \
    coursewindow.ui \
    eteachermanagementwindow.ui \
    evaluateteacherwindow.ui \
    newloginform.ui \
    scoreform.ui \
    scorewindow.ui \
    selectcourseform.ui \
    smallchooseform.ui \
    stu_changewindow.ui \
    stu_mainwindow.ui \
    studentmanagementwindow.ui \
    tea_evaluateteacherwindow.ui \
    tea_mainwindow.ui \
    teachermanagementwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
