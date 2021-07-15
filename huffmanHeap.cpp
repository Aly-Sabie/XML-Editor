#include "huffmanHeap.h"


HuffmanHeap::HuffmanHeap() {
    this->size = 0;
    this->capacity = 256;
    this->arr.fill(nullptr, 256);
}
HuffmanHeap::HuffmanHeap(int c) {
    this->size = 0;
    this->capacity = c;
    this->arr.fill(nullptr, 256);
}

HuffmanNode *HuffmanHeap::get_min() {
    return arr[0];
}



int HuffmanHeap::get_size() {
    return size;
}

HuffmanNode *HuffmanHeap::pop() {
    HuffmanNode *node = arr[0];
    arr[0] = arr[size-1];
    size--;

    int i = 0;
    HuffmanNode *container;

    while( (2*i)+1 <= (size-1)) {

        if(arr[ (2*i)+1 ]->get_frequency() <= arr[ (2*i)+2 ]->get_frequency()) {
            if(arr[ (2*i)+1 ]->get_frequency() < arr[i]->get_frequency()) {
                container = arr[i];
                arr[i] = arr[ (2*i)+1 ];
                arr[ (2*i)+1 ] = container;
                i = (2*i)+1;
            }
            else {
                break;
            }
        }
        else {
            if(arr[ (2*i)+2 ]->get_frequency() < arr[i]->get_frequency()) {
                container = arr[i];
                arr[i] = arr[ (2*i)+2 ];
                arr[ (2*i)+2 ] = container;
                i = (2*i)+2;
            }
            else {
                break;
            }

        }
    }


    return node;
}

void HuffmanHeap::insert(HuffmanNode *node) {
    arr[size] = node;
    int i = size;
    size++;
    HuffmanNode *container;

    while(i > 0) {
        if (arr[ (i-1)/2 ]->get_frequency() > arr[i]->get_frequency()) {
            container = arr[i];
            arr[i] = arr[ (i-1)/2 ];
            arr[ (i-1)/2 ] = container;
            i = (i-1) / 2;
        }
        else {
            break;
        }
    }
}

QString HuffmanHeap::test() {
    QString output = "";
    for(int i = 0; i < size; i++) {
        output = output + arr[i]->get_character() + " " + QString::number(arr[i]->get_frequency()) + "   ";
    }
    return output;
}
