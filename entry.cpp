/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
using namespace std;

SymEntry::SymEntry(){
    this->key = "";
    this->val =nullptr;
    this->left=nullptr;
    this->right=nullptr;
}
    
SymEntry::SymEntry(string k, UnlimitedRational* v){
    this->key = k;
    string num = v->get_p_str();
    string den = v->get_q_str();
    UnlimitedInt NUM(num); UnlimitedInt DEN(den);
    UnlimitedRational* Val = new UnlimitedRational(&NUM,&DEN);
    this->val = Val;
    this->left=nullptr;
    this->right=nullptr;
}

SymEntry::~SymEntry(){
    delete val;
}