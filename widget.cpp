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

//adding get error in tts position by commenting that with recommendation to add the error
void Widget::showErrors(){
    QString B;
    QStack<QString> tagStack;
    QString tag;
    B = ui->textEdit->toPlainText();
    QString C;
    int x = B.length();
    for(int i = 0; i < x; i++){
        if(B[i] != '<'){
            C.append(B[i]);
        }
        if(B[i] == '/' && B[i+1] == '>'){
            qDebug()<< "No Error " <<tagStack.pop();
            continue;
        }
        if(B[i] == '<'){
            if(B[i+1] == '!' || B[i+1] == '?'){
                C.append("<");
                continue;
            }
            else if(B[i+1] == '/'){
                QString subStr2 = B.mid(i+2, -1);
                if(!tagStack.isEmpty() && subStr2.mid(0, subStr2.indexOf(">")) != tagStack.top()){
                    C.append("<!--*******Error: Close Tag: ");
                    C.append(tagStack.top() + "******************-->");
                    C.append("\n");
                    //C.append("<");
                    qDebug() << "Error: Close Tag: " <<tagStack.pop();
                }
                if(subStr2.mid(0, subStr2.indexOf(">")) == tagStack.top()){
                    C.append("<");
                    qDebug() << "NO ERROR: " <<tagStack.pop();
                    continue;
                }
            }
            else{
                C.append("<");
                QString subStr = B.mid(i+1, -1);
                if(subStr.indexOf(" ") < subStr.indexOf(">") && subStr.indexOf(" ") < subStr.indexOf("/")){
                    tag = subStr.mid(0,subStr.indexOf(" "));
                    tagStack.push(tag);
                }
                else if (subStr.indexOf(" ") > subStr.indexOf(">")){
                    tag = subStr.mid(0,subStr.indexOf(">"));
                    tagStack.push(tag);
                }
            }
        }
    }
    while(!tagStack.isEmpty()){
        C.append("<!--*******Error: Close Tag: ");
        C.append(tagStack.top() + "****************-->");
        C.append("\n");
        //C.append("<");

        qDebug() << "Error: Close Tag" <<tagStack.pop();
    }
    ui->textEdit_2->clear();
    ui->textEdit_2->setPlainText(C);

}


//fixing the error 
void Widget::fixErrors(){
    QString B;
    QStack<QString> tagStack;
    QString tag;
    B = ui->textEdit->toPlainText();
    QString C;
    int x = B.length();
    for(int i = 0; i < x; i++){
        if(B[i] != '<'){
            C.append(B[i]);
        }
        if(B[i] == '/' && B[i+1] == '>'){
            qDebug()<< "No Error " <<tagStack.pop();
            continue;
        }
        if(B[i] == '<'){
            if(B[i+1] == '!' || B[i+1] == '?'){
                C.append("<");
                continue;
            }
            else if(B[i+1] == '/'){
                QString subStr2 = B.mid(i+2, -1);
                //qDebug() << "CHECK THIS "<<subStr2.mid(0, subStr2.indexOf(">"));
                if(!tagStack.isEmpty() && subStr2.mid(0, subStr2.indexOf(">")) != tagStack.top()){
                    //error
                    C.append("<!--******* ADDING Close Tag: ");
                    C.append(tagStack.top() + "******************-->");
                    C.append("\n");
                    C.append("</" + tagStack.top() + ">");
                    C.append("\n");
                    //C.append("<");
                    qDebug() << "Error: Close Tag: " <<tagStack.pop();
                }
                if(subStr2.mid(0, subStr2.indexOf(">")) == tagStack.top()){
                    C.append("<");
                    qDebug() << "NO ERROR: " <<tagStack.pop();
                    continue;

                }
            }
            else{
                C.append("<");
                QString subStr = B.mid(i+1, -1);
                if(subStr.indexOf(" ") < subStr.indexOf(">") && subStr.indexOf(" ") < subStr.indexOf("/")){
                    tag = subStr.mid(0,subStr.indexOf(" "));
                    tagStack.push(tag);
                }
                else if (subStr.indexOf(" ") > subStr.indexOf(">")){
                    tag = subStr.mid(0,subStr.indexOf(">"));
                    tagStack.push(tag);
                }
            }
        }
    }
    while(!tagStack.isEmpty()){
        C.append("<!--*******ADDING Tag: ");
        C.append(tagStack.top() + "****************-->");
        C.append("\n");
        C.append("</" + tagStack.top() + ">");
        C.append("\n");
        //C.append("<");

        qDebug() << "Error: Close Tag" <<tagStack.pop();
    }
    ui->textEdit_2->clear();
    ui->textEdit_2->setPlainText(C);
}

//adding the buttons to call the function
void Widget::on_gotoAnother_clicked()
{
    showErrors();
    qDebug()<< "***********************************";
}

void Widget::on_Fix_button_clicked()
{
    fixErrors();
    qDebug()<< "***********************************";
}


