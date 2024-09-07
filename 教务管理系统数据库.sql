CREATE DATABASE educational_management_table;

CREATE TABLE department_table (
    departmentId INT PRIMARY KEY AUTO_INCREMENT,
    departmentName NVARCHAR(40) NOT NULL
);

CREATE TABLE major_table (
    majorId INT PRIMARY KEY AUTO_INCREMENT,
    departmentId INT,
    majorName NVARCHAR(40) NOT NULL,
    majorSum INT
);

CREATE TABLE announce_table (
    announceId INT PRIMARY KEY AUTO_INCREMENT,
    announceType INT CHECK (announceType >= 0 AND announceType <= 1) NOT NULL,
    departmentId INT, -- 当是院系公告时管用
    announceContent TEXT,
    announceLinkman NVARCHAR(8), -- 联系人
    announcePhone NVARCHAR(20),
    announceMailbox NVARCHAR(30),
    announceDate DATE DEFAULT (CURRENT_DATE())
);

CREATE TABLE administrator_table (
    adminId INT PRIMARY KEY AUTO_INCREMENT,
    adminPassword NVARCHAR(20) NOT NULL,
    adminName NVARCHAR(8) NOT NULL,
    adminSex VARCHAR(2) CHECK (adminSex IN ('男', '女')) NOT NULL,
    adminAge INT NOT NULL,
    adminPhoneNum NVARCHAR(20) NOT NULL,
    adminMailbox NVARCHAR(30)
);
alter table administrator_table modify adminId int default 10000000;

CREATE TABLE teacher_table (
    teacherId INT PRIMARY KEY AUTO_INCREMENT,
    teacherPassword NVARCHAR(20) NOT NULL,
    teacherName NVARCHAR(8) NOT NULL,
    teacherSex NVARCHAR(2) CHECK(teacherSex IN ('男', '女')) NOT NULL,
    teacherAge INT NOT NULL,
    departmentId INT, -- 老师所属院系
    teacherJobTitle NVARCHAR(8) NOT NULL,
    teacherPhoneNum NVARCHAR(20) NOT NULL,
    teacherMailbox NVARCHAR(30),
    teacherIntroduction TEXT
);
alter table teacher_table modify teacherId int default 20000000;

CREATE TABLE student_table (
    studentId INT PRIMARY KEY AUTO_INCREMENT,
    majorId INT,
    departmentId INT, -- 学生所属院系
    studentPassword NVARCHAR(20) NOT NULL,
    studentName NVARCHAR(8) NOT NULL,
    studentSex NVARCHAR(2) CHECK(studentSex IN ('男', '女')) NOT NULL,
    studentAge INT,
    studentSumScore INT DEFAULT 0
);
alter table student_table modify studentId int default 30000000;

CREATE TABLE course_table (
    courseId INT PRIMARY KEY AUTO_INCREMENT,
    teacherId INT,
    majorId INT,
    departmentId INT, -- 课程所属院系
    courseTerm INT CHECK(courseTerm >= 1 AND courseTerm <= 2),
    courseType INT,
    courseHour INT,
    courseScore FLOAT,
    courseBeginDate DATE,
    courseEndDate DATE,
    teacherName NVARCHAR(20),
    courseName NVARCHAR(40),
    courseClassTime TEXT, -- '星期三一二节课，星期四五六节课'
    placeOfClass NVARCHAR(100),
    courseMaxCount INT,
    courseSelectNum INT,
    FOREIGN KEY (teacherId) REFERENCES teacher_table(teacherId)
);

CREATE TABLE evaluate_teacher_table (
    evaluateId INT PRIMARY KEY AUTO_INCREMENT,
    studentId INT REFERENCES student_table(studentId),
    courseId INT REFERENCES course_table(courseId),
    teacherId INT REFERENCES teacher_table(teacherId),
    courseTerm INT,
    majorId INT,
    departmentId INT, -- 课程所属院系
    courseName NVARCHAR(20),
    evaluateStatus INT CHECK (evaluateStatus <= 25),
    evaluateContent INT CHECK (evaluateContent <= 30),
    evaluateMethod INT CHECK (evaluateMethod <= 30),
    evaluateEffect INT CHECK (evaluateEffect <= 15),
    evaluateSuggest TEXT,
    sumScore INT
);

CREATE TABLE select_course_table (
    selectId INT PRIMARY KEY AUTO_INCREMENT,
    courseId INT NOT NULL,
    teacherId INT NOT NULL,
    studentId INT NOT NULL,
    majorId INT,
    departmentId INT, -- 课程所属院系
    courseTerm INT CHECK (courseTerm >= 1 AND courseTerm <= 2) NOT NULL,
    selectStatus INT CHECK (selectStatus >= -1 AND selectStatus <= 2),
    courseName NVARCHAR(40),
    FOREIGN KEY (courseId) REFERENCES course_table(courseId),
    FOREIGN KEY (teacherId) REFERENCES teacher_table(teacherId),
    FOREIGN KEY (studentId) REFERENCES student_table(studentId)
);

CREATE TABLE score_table (
    scoreId INT PRIMARY KEY AUTO_INCREMENT,
    courseId INT NOT NULL,
    studentId INT NOT NULL,
    teacherId INT NOT NULL,
    courseTerm INT CHECK (courseTerm >= 1 AND courseTerm <= 2),
    score FLOAT,
    studentPass INT,
    studentRetryNum INT DEFAULT 0,
    FOREIGN KEY (courseId) REFERENCES course_table(courseId),
    FOREIGN KEY (studentId) REFERENCES student_table(studentId),
    FOREIGN KEY (teacherId) REFERENCES teacher_table(teacherId)
);