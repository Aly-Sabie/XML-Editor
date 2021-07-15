#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QVector>

//Node Class
class Node {
public:
    QString tag;
    QString data;
    int depth;
    int num_of_children;
    int num_of_attributes;
    QVector <Node *> childrenVec;
    QVector < QVector<QString> > attributesVec;


public:
    // data
    Node();
    Node(QString tag);

    Node(QString tag, QString data);
    void set_tag(QString tag);
    QString get_tag();
    void set_data(QString data);
    QString get_data();

    // depth
    Node(QString tag, QString data, int depth);
    void set_depth(int depth);
    int get_depth();

    // number of children    Note: it's always initialized in the constructor to be 0
    int get_num_of_children();
    void increament_num_of_children();

    // children
    void set_child(QString tag);
    Node* get_child(int index);




    int get_num_of_attributes();
    void increament_num_of_attributes();


    void set_attribute(QString type,QString value);
    QString get_attribute_type(int index);
    QString get_attribute_value(int index);
friend class Tree;

};


#endif // NODE_H
