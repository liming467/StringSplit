#ifndef SEPARATORDLG_H
#define SEPARATORDLG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class SeparatorDlg;
}

class SeparatorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SeparatorDlg(QWidget *parent = nullptr);
    ~SeparatorDlg();

    QString getFileName();


    QString separator;
    QString fileName;
    int rowCount;//record the row number of your selected file

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void upadteTable();

signals:
    void boxChanged();


private:
    Ui::SeparatorDlg *ui;

    void readWholeFile();
    void getSeparator();
    void splitData();
    void showTableData();
    void initTable();

    QStandardItemModel *m_model;



};

#endif // SEPARATORDLG_H
