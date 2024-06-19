/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;

SymEntry* removeHelper(SymEntry* root, string k){
    if(root == nullptr){return root;}
    if(root->key != k){
        if(root->key > k){
            root->left = removeHelper(root->left,k);
        }
        else{
            root->right = removeHelper(root->right,k);
        }
    }
    if(root->left == nullptr && root->right == nullptr){delete root; return nullptr;}
    else if(root->left == nullptr || root->right == nullptr){
        if(root->left == nullptr){
            SymEntry* t = root->right; 
            delete root; 
            return t;
        }
        else{
            SymEntry* t = root->left; 
            delete root; 
            return t;
        }
    }
    else{
        SymEntry* t = root->left;
        while(t->right!=nullptr){t=t->right;}

        string tempK = t->key; string p = t->val->get_p()->to_string(); string q = t->val->get_q()->to_string();
        UnlimitedInt P(p); UnlimitedInt Q(q);
        UnlimitedRational* tempVal = new UnlimitedRational(&P,&Q);
        root->key = tempK; 
        delete root->val; root->val = tempVal;

        root->left = removeHelper(root->left,tempK);
        return root;
    }
}

void destructor(SymEntry* root){
    if(root == nullptr){return;}
    destructor(root->left);
    destructor(root->right);
    delete root;
}

SymbolTable::SymbolTable(){
    root=nullptr;
    this->size=0;
}

SymbolTable::~SymbolTable(){
    destructor(this->root);
}

    // Insert a key value pair in the symbol table
void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* ans = new SymEntry(k,v);
    if(this->size==0){this->root = ans; size++; return;}
    SymEntry* temp = root; 
    while((temp->key>k && temp->left!=nullptr) || (temp->key<k && temp->right!=nullptr)){
        if(temp->key>k){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    if(temp->key>k){
        temp->left = ans;
    }
    else{
        temp->right = ans;
    }
    size++; 
}

    // Remove a key (and value) in the symbol table
void SymbolTable::remove(string k){
    this->root = removeHelper(this->root,k);
}
 
    // Find the val corresponding to the key in the symbol table
UnlimitedRational* SymbolTable::search(string k){
    SymEntry* temp = root;
    if(temp == nullptr){return nullptr;}
    while(temp!=nullptr){
        if(temp->key == k){
            UnlimitedInt* p = temp->val->get_p(); UnlimitedInt* q = temp->val->get_q();
            UnlimitedRational* ans = new UnlimitedRational(p,q);
            return ans;
        }
        else if(temp->key>k){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return nullptr;
}

    // Get size
int SymbolTable::get_size(){
    return size;
}

    // Get root 
SymEntry* SymbolTable::get_root(){
    return root;
}