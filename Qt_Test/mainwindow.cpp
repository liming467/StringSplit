#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include "separatordlg.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    SeparatorDlg dlg;
    if(dlg.exec() == QDialog::Rejected)
        return;

    QString separator=dlg.separator;
    QString filename=dlg.fileName;
    int length=dlg.rowCount;
    if(filename.isEmpty())
        return;


    QFile readFile(filename);
    if(!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(nullptr, "Warning", "Fail to read the file");
        return;
    }

    QTextStream readStream(&readFile);
    QString line;
    line=readStream.readLine();//skip the first row

    float *time=new float[length];
    float *point1=new float[length];
    float *point2= new float[length];
    float *point3= new float[length];
    QString str="";

    int i=0;
    while(i<length)
    {
        if(i>20)//for test;you can delete
            break;

        line=readStream.readLine();
        if(line.isEmpty())
            break;

        QStringList list=line.split(QRegExp(separator),QString::SkipEmptyParts);
        time[i]=list.at(0).toFloat();
        point1[i]=list.at(1).toFloat();
        point2[i]=list.at(2).toFloat();
        point3[i]=list.at(3).toFloat();

        /**********for test;you can delete*******/
        str+=QString::number(time[i]);
        str+="\t";
        str+=QString::number(point1[i]);
        str+="\t";
        str+=QString::number(point2[i]);
        str+="\t";
        str+=QString::number(point3[i]);
        str+="\n";

        i++;
    }
    QMessageBox::warning(NULL,QString::fromLocal8Bit("Warning"),str);//for test;you can delete
}
