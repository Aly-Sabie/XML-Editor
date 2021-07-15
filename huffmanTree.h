#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "huffmanHeap.h"

class HuffmanTree {
public:

    QString string;
    QVector<HuffmanNode *> vector;
    HuffmanHeap heap;
    HuffmanNode *root;
    QVector<QVector <QString>> codes_mapping;
    int map_count;

public:
    HuffmanTree(QString input);




};


#endif // HUFFMANTREE_H
