#include "huffmanTree.h"

HuffmanTree::HuffmanTree(QString input) {

    this->string = input;

    codes_mapping.fill(QVector<QString>(2), 256);
    map_count = 0;


    vector_creation(input);

    huffman_heap_building();

    huffman_tree_building();

    map_generation(root, "");

}
