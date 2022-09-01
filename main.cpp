#include "rollcall.h"
#include <QApplication>
#include <QFile>
#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char *argv[])
{
    QFile fileTemp(".\\output.txt");    //一打开程序就删除结果文件
    fileTemp.remove();
    fstream file;   //检测是否存在花名册文件，如果没有则创建
    file.open(".\\roster.txt",ios::in);
    if(!file)
    {
        QFile file(".\\roster.txt");
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    QApplication a(argc, argv);
    Rollcall w;
    w.show();
    return a.exec();
}
