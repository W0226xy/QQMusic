#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlError>
#include<QSqlQuery>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_connectDB_clicked()
{
    //1.导入数据库驱动
    QSqlDatabase sqlite=QSqlDatabase::addDatabase("QSQLITE");
    //2.设置数据库名称
    sqlite.setDatabaseName("studentDB.db");
    //3.如果studentDB存在，则直接打开，如果不存在，先创建后打开
    if(!sqlite.open())//打开失败
    {
        qDebug()<<"创建连接数据库studentDB.db失败"<<sqlite.lastError().text();
    }

    qDebug()<<"数据库创建成功";

}

void Widget::on_createTab_clicked()
{
    //student表: id(主键) name(not null) age gpa
    QString sql("create table student( \
                  id integer primary key autoincrement,\
                  name varchar(50) not null, \
                  age integer, \
                  gpa real) \
                   ");
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qDebug()<<"创建学生表student"<<query.lastError().text();
    }
    qDebug()<<"创建学生表成功";
}

void Widget::on_closeDB_clicked()
{
    sqlite.close();
}

void Widget::on_insert_clicked()
{
//    QString sql("insert into student(id,name,age,gpa)\
//                values(1,'wxy',24,3.8)");
    QString sql("insert into student values(%1,'%2',%3,%4)");
    sql=sql.arg(3,1,10)//arg(数值，最小宽度，进制),把数字 3 按十进制形式输出，最小宽度为 1
            .arg("王五")
            .arg(20,2,10)
            .arg(3.8);//实际是3,'王五',20,3.8
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qDebug()<<"数据插入失败"<<query.lastError().text();
        return;
    }
    qDebug()<<"插入数据成功";
}
