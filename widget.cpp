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


//fn to convert UI string to Tree
void Widget::strToTree(){
    QString B;
    QStack<Node*> treeStack;
    Node * root_ptr;
    QString tag;
    QString attributes;
    B = ui->textEdit->toPlainText();
    int x = B.length();

    for(int i = 0; i < x; i++){
        if(B[i] == '<'){

            if(B[i+1] == '!' || B[i+1] == '?'){
                continue;
            }

            //tags
            if(B[i+1] != '/'){
                QString subStr = B.mid(i+1, -1);
                qDebug()<<"open tag";

                //tags with attributes
                    if(subStr.indexOf(" ") < subStr.indexOf(">") && subStr.indexOf(" ") < subStr.indexOf("/")){
                        tag = subStr.mid(0,subStr.indexOf(" "));
                        Node * x = new Node(tag);
                        QVector<QString> attr(2);

                        subStr = subStr.mid(subStr.indexOf(" "), -1);

                        while(subStr[0] != '>' && subStr[0] != '/'){
                            attr[0] = subStr.mid(1, subStr.indexOf("=") - 1);
                            subStr = subStr.mid(subStr.indexOf("=") + 2, -1);
                            attr[1] = subStr.mid(0, subStr.indexOf('"'));
                            x->attributesVec.append(attr);
                            subStr = subStr.mid(subStr.indexOf('"') + 1, -1);
                        }

                        //pop if closed with the same opening tag
                        if(subStr[0] == '/'){
                            qDebug()<<"PUSHED" << x->get_tag();
                            if(!treeStack.isEmpty()){
                                treeStack.top()->childrenVec.append(x);
                                x->set_depth(treeStack.size());
                            }
                            else{
                                root_ptr = x;
                            }
                            treeStack.push(x);
                            qDebug() << "closed" << treeStack.top()->get_tag();
                            treeStack.pop();
                            continue;

                        }

                        //after open tag
                        subStr = subStr.mid(subStr.indexOf(">") + 1, -1);
                        if(subStr[0]!= '<' && subStr[0]!= '\n'){
                            QString data = subStr.mid(0, subStr.indexOf("<"));
                            x->set_data(data);
                        }

                        //treeStack.top().childrenVec.append(&x);
                        qDebug()<<"PUSHED" << x->get_tag();
                        if(!treeStack.isEmpty()){
                            treeStack.top()->childrenVec.append(x);
                            x->set_depth(treeStack.size());
                        }
                        else{
                            root_ptr = x;
                        }

                        treeStack.push(x);
                    }


                //tags without attributes
                    else if (subStr.indexOf(" ") > subStr.indexOf(">")){
                        tag = subStr.mid(0,subStr.indexOf(">"));
                        Node *x = new Node(tag);
                        subStr = subStr.mid(subStr.indexOf(">") + 1, -1);
                        if(subStr[0]!= '<'&& subStr[0]!= '\n'){
                            QString data = subStr.mid(0, subStr.indexOf("<"));
                            x->set_data(data);
                        }
                        qDebug()<<"PUSHED with no attr" << x->get_tag();
                        if(!treeStack.isEmpty()){
                            treeStack.top()->childrenVec.append(x);
                            x->set_depth(treeStack.size());
                        }
                        else{
                            root_ptr = x;
                        }

                        treeStack.push(x);
                    }
            }
            else if(B[i+1] == '/'){

                qDebug() << "closed" << treeStack.top()->get_tag();
                treeStack.pop();
            }


        }



    }

    t.set_root(root_ptr);



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

//the rest of buttons

void Widget::on_prettify_btn_clicked()
{
    strToTree();
    ui->textEdit_2->setPlainText(t.xml_spaces(1));

}

void Widget::on_removeSpaces_btn_clicked()
{
    strToTree();
    ui->textEdit_2->setPlainText(t.xml_spaces(0));
}

void Widget::on_xmlToJSON_btn_clicked()

{
    strToTree();
    ui->textEdit_2->setPlainText(t.XMLtoJSON());
}

void Widget::on_compression_btn_clicked()
{
    HuffmanTree huffman(ui->textEdit->toPlainText());
    ui->textEdit_2->setPlainText(huffman.get_binary());
}




