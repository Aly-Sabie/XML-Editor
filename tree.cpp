#include "tree.h"


Tree::Tree() {
    header = "";
}

void Tree::set_root(Node *r) {
    this->root = r;

}


Node *Tree::get_root() { // returns a pointer to the root node
    return root;
}


void Tree::recursive_prettification(QString *output, QStack<Node> *stack, QString tabs) {
    Node r;
    r = stack->pop();

    if(r.childrenVec.length() != 0) {
        // children pushing on the stack
        for(int i = (r.childrenVec.length() - 1); i >= 0; i--) {
            stack->push(*(r.get_child(i)));
        }

        // <tag
        *output = *output + tabs + '<' + r.get_tag();

        for(int i = 0; i < r.attributesVec.length(); i++) {
            *output = *output + " " + r.get_attribute_type(i) + "=" + r.get_attribute_value(i);
        }

        *output = *output + ">\n";

        if(r.get_data() != "") {
            *output = *output + tabs + "    " + r.get_data() + "\n";
        }

        for (int i = 0; i < r.childrenVec.length(); i++) {
            recursive_prettification(output, stack, tabs + "    ");
        }

        *output = *output + tabs + "</" + r.get_tag() + ">\n";


    }
    else {

        *output = *output + tabs + '<' + r.get_tag();
        //..=.. is exists
        for(int i = 0; i < r.attributesVec.length(); i++) {
            *output = *output + " " + r.get_attribute_type(i) + "=" + r.get_attribute_value(i);
        }
        //>\n
        *output = *output + "> ";

        *output = *output + r.get_data();
        *output = *output + " </" + r.get_tag() + ">\n";




        return;
    }

}

void Tree::recursive_space_removal(QString *output, QStack<Node> *stack) {
        Node r;
        r = stack->pop();

        if(r.childrenVec.length() != 0) {
            // children pushing on the stack
            for(int i = (r.childrenVec.length() - 1); i >= 0; i--) {
                stack->push(*(r.get_child(i)));
            }

            // <tag
            *output = *output + '<' + r.get_tag();
            for(int i = 0; i < r.attributesVec.length(); i++) {
                *output = *output + ' ' + r.get_attribute_type(i) + "=" + '"' + r.get_attribute_value(i) + '"';
            }
            *output = *output + '>';

            if(r.get_data() != "") {
                *output = *output  + r.get_data();
            }

            for (int i = 0; i < r.childrenVec.length(); i++) {
                recursive_space_removal(output, stack);
            }

            *output = *output + "</" + r.get_tag() + '>';


        }
        else {

            *output = *output + '<' + r.get_tag();
            //..=.. is exists
            for(int i = 0; i < r.attributesVec.length(); i++) {
                *output = *output + ' ' + r.get_attribute_type(i) + "=" + '"' + r.get_attribute_value(i) + '"';
            }
            //>\n
            *output = *output + ">";

            *output = *output + r.get_data();
            *output = *output + "</" + r.get_tag() + '>';

            return;
        }

    }

QString Tree::xml_spaces(bool condition) {

    QString output = "";
    QStack<Node> stack;
    Node r = *(this->root);
    stack.push(r);

    // recursive calls

    if(condition != 0) {
        //output = output + "\n";
        recursive_prettification(&output, &stack, "");
    }
    else {
        recursive_space_removal(&output, &stack);
    }


    return output;

}


QString Tree::XMLtoJSON(){
         QString s="";
         return xmltojson(get_root(),s);
     }
QString Tree::xmltojson(Node * pp,QString s){


    if(pp->childrenVec.length()==0){


        if(pp->attributesVec.length()==0 && pp->get_data()==""){

            for(int j=0;j<pp->get_depth();j++)
                s+="    ";

            s=s+'"'+pp->get_tag()+'"'+":null\n";
        }


        if(pp->attributesVec.length()==0 && pp->get_data()!=""){

            for(int j=0;j<pp->get_depth();j++)
                s+="    ";

            s=s+'"'+pp->get_tag()+'"'+":"+'"'+pp->get_data()+'"'+"\n";
        }


        if(pp->attributesVec.length()!=0 && pp->get_data()==""){

            for(int j=0;j<pp->get_depth();j++)
                s+="    ";

            s=s+'"'+pp->get_tag()+'"'+":{";

            for(int i=0;i<pp->attributesVec.length();i++){

                s=s+'"'+'@'+pp->get_attribute_type(i)+'"'+":"+'"'+pp->get_attribute_value(i)+'"';

                if(i!=pp->attributesVec.length()-1){
                    s+=",";
                }

                s+="}/n";
            }

        }

        if(pp->attributesVec.length()!=0&&pp->get_data()!=""){


            for(int j=0;j<pp->get_depth();j++)
                s+="    ";

            s=s+'"'+pp->get_tag()+'"'+":{";

            for(int i=0;i<pp->attributesVec.length();i++){



                s=s+'"'+'@'+pp->get_attribute_type(i)+'"'+":"+'"'+pp->get_attribute_value(i)+'"';
                if(i!=pp->attributesVec.length()-1){
                    s+=",";
                }



                s=s+'"'+"#text"+'"'+":"+'"'+pp->get_data()+'"';
            }
            s+='\n';
        }


}

         else{

                    if(pp->attributesVec.length()==0&&pp->get_data()==""){

                        for(int j=0;j<pp->get_depth();j++)
                            s+="    ";

                        s=s+'"'+pp->get_tag()+'"'+":{\n";


                    }


                    if(pp->attributesVec.length()==0&&pp->get_data()!=""){

                        for(int j=0;j<pp->get_depth();j++)
                            s+="    ";

                        s=s+'"'+pp->get_tag()+'"'+":{\n";

                        for(int j=0;j<=pp->get_depth();j++)
                            s+="    ";

                        s=s+'"'+"#text"+'"'+":"+'"'+pp->get_data()+'"'+",\n";
                    }



                    if(pp->attributesVec.length()!=0&&pp->get_data()==""){

                        for(int j=0;j<pp->get_depth();j++)
                            s+="    ";

                        s=s+'"'+pp->get_tag()+'"'+":{\n";

                        for(int i=0;i<pp->attributesVec.length();i++){


                            for(int j=0;j<=pp->get_depth();j++)
                                s+="    ";


                            s=s+'"'+'@'+pp->get_attribute_type(i)+'"'+":"+'"'+pp->get_attribute_value(i)+'"';
                            s+=",\n";
                        }
                    }



                    if(pp->attributesVec.length()!=0&&pp->get_data()!=""){

                        for(int j=0;j<pp->get_depth();j++)
                            s+="    ";

                        s=s+'"'+pp->get_tag()+'"'+":{\n";



                        for(int i=0;i<pp->attributesVec.length();i++){

                            for(int j=0;j<=pp->get_depth();j++)
                                s+="    ";

                            s=s+'"'+'@'+pp->get_attribute_type(i)+'"'+":"+'"'+pp->get_attribute_value(i)+'"';
                            s+=",\n";
                        }

                        for(int j=0;j<=pp->get_depth();j++)
                            s+="    ";

                            s = s + '"' + "#text" + '"' + ":" + '"' +pp->get_data() + '"' + ",\n";
                        }


                        for(int i=0;i<pp->childrenVec.length();i++){
                             s+=xmltojson((pp->get_child(i)),"");
                             if(i==pp->childrenVec.length()-1){
                                 for(int j=0;j<pp->get_depth();j++)
                                     s+="    ";
                                s+="}\n";
                             }

                        }



            }

         return s;
     }
