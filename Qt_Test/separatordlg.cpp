#include "separatordlg.h"
#include "ui_separatordlg.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

SeparatorDlg::SeparatorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeparatorDlg)
{
    ui->setupUi(this);
    separator="";
    rowCount=0;
    fileName=getFileName();

    connect(ui->Tab,&QCheckBox::stateChanged,this,&SeparatorDlg::upadteTable);
    connect(ui->Space,&QCheckBox::stateChanged,this,&SeparatorDlg::upadteTable);
    connect(ui->Comma,&QCheckBox::stateChanged,this,&SeparatorDlg::upadteTable);
    connect(ui->Semi,&QCheckBox::stateChanged,this,&SeparatorDlg::upadteTable);
    connect(ui->lineEdit,&QLineEdit::textEdited,this,&SeparatorDlg::upadteTable);
}

SeparatorDlg::~SeparatorDlg()
{    
    delete ui;
}

void SeparatorDlg::on_buttonBox_accepted()
{
    QMessageBox::information(NULL,"Dlg->abc:",separator);
    accept();
}


void SeparatorDlg::upadteTable(){

    getSeparator();
    if(fileName.isEmpty())
        return;

    readWholeFile();


}

void SeparatorDlg::getSeparator(){

    QString str("");
    if(ui->Tab->isChecked())
        str+="\t";
    if(ui->Semi->isChecked())
        str+=";";
    if(ui->Comma->isChecked())
        str+=",";
    if(ui->Space->isChecked())
        str+=" ";
    if(ui->Other->isChecked()){
        str+=ui->lineEdit->text();
    }

    separator="[";
    separator+=str;
    separator+="]+";

}

void SeparatorDlg::readWholeFile(){

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(nullptr, "Warning", "Fail to read the file");
        return;
    }
    QTextStream in(&file);
    QStringList textList;   //记录文件中每一行的数据

    while (!in.atEnd())
        textList.append(in.readLine());
    rowCount=textList.size();
    file.close();

    if(textList.isEmpty()){
        QMessageBox::warning(NULL,QString::fromLocal8Bit("Warning"),QString::fromLocal8Bit("Text has nothing!"),QMessageBox::Ok);
        return;
    }


    initTable();

    QStringList listColHeader = textList.at(0).split(QRegExp(separator),QString::SkipEmptyParts);
    m_model->setColumnCount(listColHeader.size());
    for (int i=0;i<listColHeader.size();i++)
        m_model->setHorizontalHeaderItem(i, new QStandardItem(listColHeader.at(i)));

    for(int row = 1; row < rowCount; row++)
    {
        QStringList tmpList = textList.at(row).split(QRegExp(separator),QString::SkipEmptyParts);
        for(int col = 0; col < tmpList.size(); col++)
        {
            m_model->setItem(row-1,col,new QStandardItem(tmpList.at(col)));
            m_model->item(row-1,col)->setTextAlignment(Qt::AlignCenter);
            m_model->item(row-1,col)->setForeground(QBrush(QColor(255, 0, 0)));
        }
    }


}

void SeparatorDlg::initTable(){

    m_model = new QStandardItemModel();
    ui->tableView->setModel(m_model);

    ui->tableView->setShowGrid(true);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void SeparatorDlg::splitData(){

}

void SeparatorDlg::showTableData(){

}

QString SeparatorDlg::getFileName(){
    QString filename("");
    filename = QFileDialog::getOpenFileName(this,
           tr("Select file"),
           "",
           tr("Files (*.dat *.txt *.csv)")); //select file path


    return filename;
}

void SeparatorDlg::on_buttonBox_rejected()
{
    reject();
}
