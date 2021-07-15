#include "widget.h"
#include "ui_widget.h"
#include "QFile"
#include "QFileDialog"
#include "QTextStream"
#include "QDebug"
#include "QTextEdit"
#include "QString"
#include "QStack"
#include "QVector"
#include "huffmanTree.h"
#include <QByteArray>


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

//browse button
void Widget::on_browseButton_clicked()
{
    QString fileContent;
    QString filename = QFileDialog::getOpenFileName(this,"Open File");
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    QTextStream in(&file);
    fileContent = in.readAll();
    file.close();
    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
}

//save button
void Widget::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save As");
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
             return;

    QTextStream out(&file);
    out << ui ->textEdit_2 -> toPlainText() << "\n";
    file.close();


}


