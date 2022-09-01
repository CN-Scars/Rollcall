#include "rollcall.h"
#include "ui_rollcall.h"
#include<QMessageBox>
#include<QDebug>
#include<QDesktopServices>
#include<QInputDialog>
#include<QDialog>
#include<QFile>
#include<qdesktopservices.h>
#include<iostream>
#include<math.h>
#include<cstring>
#include<iomanip>
#include<fstream>
#include<windows.h>
using namespace std;
Rollcall::Rollcall(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rollcall)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/res/Rollcall.ico"));
}



Rollcall::~Rollcall()
{
    delete ui;
}

int Coutlines(char *filename)   //读取花名册文件行数函数
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);
    if(ReadFile.fail())     //文件打开失败，返回0
        return n=-1;
    else    //文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();   //关闭文件
        return n;   //n为花名册文件行数
    }
}

void Rollcall::on_checkprecautions_clicked()    //查看注意事项按钮
{
    // 提示对话框
    int ret2 = QMessageBox::information(this, tr("注意事项"),
    tr("1.结果将会在下次打开程序后清除"
       "\n2.如果进行多次点名，则最新的结果将会显示在下方"     //对话框内容太长了，分行写
       "\n3.如本程序有问题，欢迎到作者视频评论区提出，不一定及时修复"), QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok) qDebug() << tr("注意事项！");
}

void Rollcall::on_inputBt_clicked()     //开始点名按钮
{
    int data=QInputDialog::getInt(this,"开始抽人","请输入抽取人数：");
    ui->textBrowser_2->setText(QString::number(data));
    int number;   //读取花名册文件行数
    char filename[]=".\\roster.txt";
    number=Coutlines(filename);     //number为花名册人数
    if(data>0&&data<=number)
    {
        if(number==-1)      //花名册文件不存在
            ui->textBrowser->setText("错误！未找到花名册信息，请自定义花名册，注意逐行输入人名！");
        else    //花名册文件存在
        {
            string b[number];   //存放人名信息的数组
            fstream file;   //逐行读取人名到数组b[number]
            file.open(".\\roster.txt");
            if(!file)   //如果未找到roster.txt花名册文件
            ui->textBrowser->setText("错误！未找到花名册信息，请自定义花名册，注意逐行输入人名！");
            int pos=0;
            while(!file.eof())  //检查是否到文件末尾
            {
                file>>b[pos];
                pos++;
                if(pos>=number)
                break;
            }
            file.close();
            if(number==0)      //花名册文件无数据
            {
                ui->textBrowser->setText("错误！花名册内未填入信息，请填入人名信息，注意逐行输入人名！");
            }
            srand(unsigned(time(NULL)));
            int i,j,a[number],s;
            memset(a,0,sizeof(a));
            for(i=1;i<=data;i++)
            {
                s=floor(rand()%number+1);   //在此处修改人数
                for(j=1;j<i;j++)
                    if(s==a[j]) s=0;
                if(s==0)
                {
                    i--;
                }
                else
                {
                    a[i]=s;
                }
            }
            ofstream dataFile;
            for(i=1;i<=data;i++)
            {
                dataFile.open(".\\output.txt",ofstream::app);	//朝.txt文档中写入数据
                dataFile<<" "<<b[a[i]-1];
                dataFile.close();	//关闭文档
            }
            dataFile.open(".\\output.txt",ofstream::app);	//朝.txt文档中写入数据
            dataFile<<"\n"<<"--------------------";     //输出分割线
            dataFile.close();	//关闭文档
            dataFile.open(".\\output.txt",ofstream::app);
            dataFile<<setiosflags(ios::left)<<endl;
            ui->textBrowser->setText("请点击下方的“显示结果”按钮以显示结果");
        }
    }
    else
    {
        ui->textBrowser->setText("请输入正确的人数");
    }
}

void Rollcall::on_displayBt_clicked()   //显示结果按钮
{
    QFile*file=new QFile(".\\output.txt");
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QString data=QString(file->readAll());
    ui->textBrowser->setText(data);
    file->close();
}

void Rollcall::on_refreshBt_clicked()   //刷新结果按钮
{
    QFile fileTemp(".\\output.txt");
    fileTemp.remove();
    ui->textBrowser->clear();
}

void Rollcall::on_customBt_clicked()    //自定义花名册按钮
{
    system("start .\\roster.txt");    //打开花名册
}
