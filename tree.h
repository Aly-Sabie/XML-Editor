#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <QStack>


class Tree {
public:
    Node *root;
    QString header;

public:

    Tree();

    void set_root(Node *r);


    Node *get_root();


    void recursive_prettification(QString *output, QStack<Node> *stack, QString tabs);

    void recursive_space_removal(QString *output, QStack<Node> *stack);

    QString xml_spaces(bool condition);



    //Nego
     QString XMLtoJSON();
     QString xmltojson(Node * pp,QString s);
};


#endif // TREE_H
