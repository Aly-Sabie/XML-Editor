#include "huffmanNode.h"

HuffmanNode::HuffmanNode() {
    this->left = nullptr;
    this->right = nullptr;
}

HuffmanNode::HuffmanNode(QChar character, int frequency) {
    this->character = character;
    this->frequency = frequency;
    this->left = nullptr;
    this->right = nullptr;
}
HuffmanNode::HuffmanNode(QChar character, int frequency, QString code) {
    this->character = character;
    this->frequency = frequency;
    this->code = code;
    this->left = nullptr;
    this->right = nullptr;
}

void HuffmanNode::set_char(QChar c) {
    this->character = c;
}

void HuffmanNode::set_frequency(int f) {
    this->frequency = f;
}

void HuffmanNode::set_code(QString code) {
    this->code = code;
}

void HuffmanNode::set_left(HuffmanNode *left) {
    this->left = left;
}

void HuffmanNode::set_right(HuffmanNode *right) {
    this->right = right;
}

QString HuffmanNode::get_code() {
    return this->code;
}

QChar HuffmanNode::get_character() {
    return this->character;
}

int HuffmanNode::get_frequency() {
    return this->frequency;
}

HuffmanNode *HuffmanNode::get_left() {
    return this->left;
}

HuffmanNode *HuffmanNode::get_right() {
    return this->right;
}


void HuffmanNode::inc_freq() {
    (this->frequency)++;
}


bool HuffmanNode::is_leaf() {
    return ((left == nullptr) && (right == nullptr));
}
