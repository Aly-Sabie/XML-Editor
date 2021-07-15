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
    QString get_binary();
    QString test();
    
private:
    void vector_creation(QString input);
    void huffman_heap_building();
    void huffman_tree_building();
    void map_generation(HuffmanNode *r, QString code);




};


#endif // HUFFMANTREE_H
