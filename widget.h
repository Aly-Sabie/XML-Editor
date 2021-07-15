#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include "tree.h"
//#include "widget.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);
    ~Widget();
    Tree t;

private slots:
    void on_browseButton_clicked();

    void on_saveButton_clicked();

    void on_pushButton_4_clicked();

    void on_gotoAnother_clicked();

    void strToTree();
    void showErrors();
    void fixErrors();
    void on_Fix_button_clicked();

    void on_prettify_btn_clicked();

    void on_removeSpaces_btn_clicked();

    void on_xmlToJSON_btn_clicked();

    void on_compression_btn_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
