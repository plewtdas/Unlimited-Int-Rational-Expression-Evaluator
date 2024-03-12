/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    val=nullptr;
    id="vague";
    type="vague";
    evaluated_value=nullptr;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    id="vague";
    type=t;
    left=nullptr;
    right=nullptr;
    UnlimitedInt *one=new UnlimitedInt (1);
    val=new UnlimitedRational(v,one);//converted to rational
    evaluated_value=nullptr;
    if (t=="VAL"){
        evaluated_value=val;
    }
    
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    val=v;
    id="vague";
    type=t;
    left=nullptr;
    right=nullptr;
    evaluated_value=nullptr;
    if (t=="VAL"){
        evaluated_value=v;
    }
}

ExprTreeNode::~ExprTreeNode(){
    if (type!="VAL" and evaluated_value!=nullptr){
    delete evaluated_value;
    evaluated_value=nullptr;}
    if (right!=nullptr){
    delete right;
    right=nullptr;}
    if (left!=nullptr){
    delete left;
    left=nullptr;}
    if (val!=nullptr){
    delete val;
    val=nullptr;}
}



