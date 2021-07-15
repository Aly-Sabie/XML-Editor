#ifndef HUFFMANHEAP_H
#define HUFFMANHEAP_H

#include "huffmanNode.h"
#include <QVector>

class HuffmanHeap {
private:
    QVector<HuffmanNode *> arr;
    int size;
    int capacity;

public:
    HuffmanHeap();
    HuffmanHeap(int c);


    HuffmanNode *get_min();
    int get_size();


    HuffmanNode *pop();
    void insert(HuffmanNode *node);
    QString test();
};


#endif // HUFFMANHEAP_H
