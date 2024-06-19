/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
#include <iostream>

ExprTreeNode::ExprTreeNode(){
    this->type=" ";
    this->left=nullptr;
    this->right=nullptr;
    UnlimitedInt a(0); UnlimitedInt b(1);
    this->val = new UnlimitedRational(&a, &b);
    this->evaluated_value = new UnlimitedRational(&a, &b);
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    UnlimitedInt a(0); UnlimitedInt b(1);
    this->evaluated_value = new UnlimitedRational(&a, &b);

    this->left=nullptr;
    this->right=nullptr;
    this->type = t; 
    UnlimitedInt one(1);
    UnlimitedRational* val = new UnlimitedRational(v,&one);
    this->val = val;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    UnlimitedInt a(0); UnlimitedInt b(1);
    this->evaluated_value = new UnlimitedRational(&a, &b);
    
    this->left=nullptr;
    this->right=nullptr;
    this->type = t; 
    string num = v->get_p_str();
    string den = v->get_q_str();
    UnlimitedInt NUM(num); UnlimitedInt DEN(den);
    UnlimitedRational* Val = new UnlimitedRational(&NUM,&DEN);
    this->val = Val;
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
}