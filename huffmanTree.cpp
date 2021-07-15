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

QString HuffmanTree::get_binary() {
    QChar container;
    QString output = "";
    for(int i = 0; i < string.length(); i++) {
        container = string[i];
        for(int j = 0; j < codes_mapping.length();j++) {
            if(container == codes_mapping[j][0]) {
                output = output + codes_mapping[j][1];
            }

        }

    }

    return output;
}


void HuffmanTree::vector_creation(QString input) {
    bool flag;
    for(int i = 0; i < input.length(); i++) {

        flag = 0;
        for(int j = 0; j < vector.size(); j++) {
            if(input[i] == vector[j]->get_character()) {
                vector[j]->inc_freq();
                flag = 1;
            }
        }

        if(flag == 0) {
            HuffmanNode *node = new HuffmanNode(input[i], 1);
            vector.push_back(node);
        }


    }
}
// debugged correctly
void HuffmanTree::huffman_heap_building() {

    for(int i = 0; i < vector.size(); i++) {
        heap.insert(vector[i]);
    }

}


void HuffmanTree::huffman_tree_building() {

    HuffmanNode *n1;
    HuffmanNode *n2;

    int sum;

    while(heap.get_size() > 1) {

        n1 = heap.pop();
        n2 = heap.pop();
        sum = n1->get_frequency() + n2->get_frequency();

        HuffmanNode *n = new HuffmanNode;
        (*n).set_left(n1);
        (*n).set_right(n2);
        (*n).set_frequency(sum);

        heap.insert(n);

        n = nullptr;
        n1 = nullptr;
        n2 = nullptr;



     }

    root = heap.get_min();

    /*
    qDebug() << root->get_character();
    qDebug() << root->get_frequency();
    qDebug() << "";
    qDebug() << root->get_left()->get_character();
    qDebug() << root->get_left()->get_frequency();
    qDebug() << "";
    qDebug() << root->get_left()->get_left()->get_character();
    qDebug() << root->get_left()->get_left()->get_frequency();
    qDebug() << "";
    qDebug() << root->get_left()->get_right()->get_character();
    qDebug() << root->get_left()->get_right()->get_frequency();
    qDebug() << "";
    qDebug() << root->get_right()->get_character();
    qDebug() << root->get_right()->get_frequency();
    qDebug() << "";
    qDebug() << root->get_right()->get_left()->get_character();
    qDebug() << root->get_right()->get_left()->get_frequency();
    qDebug() << "";
    qDebug() << root->get_right()->get_right()->get_character();
    qDebug() << root->get_right()->get_right()->get_frequency();
    qDebug() << "";
    */

}

void HuffmanTree::map_generation(HuffmanNode *r, QString code) {
    //qDebug() <<r->get_character() << " ";

    if(r != nullptr) {
        r->set_code(code);
        map_generation(r->get_left(), code + "0");
        map_generation(r->get_right(), code + "1");

        if(r->get_left() == nullptr && r->get_right() == nullptr) {
            codes_mapping[map_count][0] = r->get_character();
            //qDebug() << r->get_character();
            codes_mapping[map_count][1] = code;
            map_count++;
            //qDebug() << map_count;
        }
    }




}


QString HuffmanTree::test() {
    QString output = "";
    for(int i = 0; i < map_count; i++) {
        output = output + codes_mapping[i][0] + "-" + codes_mapping[i][1] + "  ";
    }

    return output;
}
