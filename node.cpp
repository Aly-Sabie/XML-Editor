#include "node.h"

Node::Node() {
    this->data="";
    this->num_of_children = 0;
    this->num_of_attributes=0;
    childrenVec.fill(nullptr/*,5*/);
    attributesVec.fill(QVector<QString>(2)/*, 5*/);
    //attributesVec.reserve(5);
}
Node::Node(QString tag) {
    this->data="";
    this->tag = tag;
    this->num_of_children = 0;
    this->num_of_attributes=0;
    childrenVec.fill(nullptr/*,5*/);
    attributesVec.fill(QVector<QString>(2)/*, 2*/);
    //attributesVec.reserve(5);
}

Node::Node(QString tag, QString data) {
    this->data=data;
    this->tag = tag;
    this->num_of_children = 0;
    this->num_of_attributes=0;
    childrenVec.fill(nullptr/*,5*/);
    attributesVec.fill(QVector<QString>(2)/*, 5*/);
    //attributesVec.reserve(5);
}
void Node::set_tag(QString tag) {
    this->tag = tag;
}
QString Node::get_tag() {
    return this->tag;
}
void Node::set_data(QString data) {
    this->data = data;
}
QString Node::get_data() {
    return this->data;
}

// depth
Node::Node(QString tag, QString data, int depth) {
    this->data=data;
    this->tag = tag;
    this->num_of_children = 0;
    this->num_of_attributes=0;
    childrenVec.fill(nullptr,5);
    attributesVec.fill(QVector<QString>(2)/*, 5*/);
    //attributesVec.reserve(5);
    this->depth = depth;
}
void Node::set_depth(int depth) {
    this->depth = depth;
}
int Node::get_depth() {
    return this->depth;
}

// number of children    Note: it's always initialized in the constructor to be 0
int Node::get_num_of_children() {
    return this->num_of_children;
}
void Node::increament_num_of_children() {
    this->num_of_children++ ;
}

// children
void Node::set_child(QString tag) {
    childrenVec[num_of_children]->set_tag(tag);
    this->num_of_children++;

}
Node* Node::get_child(int index) { // this returns a pointer to the selected child node , not the data inside it
    return childrenVec[index];
}




int Node::get_num_of_attributes() {
    return this->num_of_attributes;
}
void Node::increament_num_of_attributes() {
    this->num_of_attributes++ ;
}


void Node::set_attribute(QString type,QString value) {
    attributesVec[num_of_attributes][0]=type;
    attributesVec[num_of_attributes][1]=value;
    this->num_of_attributes++;

}
QString Node::get_attribute_type(int index) {
    return attributesVec[index][0];
}
QString Node::get_attribute_value(int index) {
    return attributesVec[index][1];
}
