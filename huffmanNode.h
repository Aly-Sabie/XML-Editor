#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

#include <QChar>
#include <QString>

class HuffmanNode {
private:
    QChar character;
    unsigned int frequency;
    QString code;

    HuffmanNode *left;
    HuffmanNode *right;

public:
    HuffmanNode();
    HuffmanNode(QChar character, int frequency);
    HuffmanNode(QChar character, int frequency, QString code);


    void set_char(QChar c);
    void set_frequency(int f);
    void set_code(QString code);
    void set_left(HuffmanNode *left);
    void set_right(HuffmanNode *right);


    QString get_code();
    QChar get_character();
    int get_frequency();
    HuffmanNode *get_left();
    HuffmanNode *get_right();


    void inc_freq();
    bool is_leaf();
};



#endif // HUFFMANNODE_H
