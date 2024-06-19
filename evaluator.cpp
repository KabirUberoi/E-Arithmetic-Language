/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

void delelteHelper(ExprTreeNode* root){
    if(root==nullptr){return;}
    delelteHelper(root->left);
    delelteHelper(root->right);
    delete root;
}

UnlimitedRational* EvalHelper(ExprTreeNode* root, SymbolTable* symtable){
    if(root->type == "ADD"){
        UnlimitedRational* left = EvalHelper(root->left,symtable); UnlimitedRational* right = EvalHelper(root->right,symtable); 
        root->evaluated_value = UnlimitedRational::add(left,right);
        delete left; delete right;
    }
    else if(root->type == "SUB"){
        UnlimitedRational* left = EvalHelper(root->left,symtable); UnlimitedRational* right = EvalHelper(root->right,symtable); 
        root->evaluated_value = UnlimitedRational::sub(left,right);
        delete left; delete right;
    }
    else if(root->type == "DIV"){
        UnlimitedRational* left = EvalHelper(root->left,symtable); UnlimitedRational* right = EvalHelper(root->right,symtable); 
        root->evaluated_value = UnlimitedRational::div(left,right);
        delete left; delete right;
    }
    else if(root->type == "MUL"){
        UnlimitedRational* left = EvalHelper(root->left,symtable); UnlimitedRational* right = EvalHelper(root->right,symtable); 
        root->evaluated_value = UnlimitedRational::mul(left,right);
        delete left; delete right;
    }
    else if(root->type == "VAR"){
        string s1 = symtable->search(root->id)->get_p()->to_string() ;string s2 =symtable->search(root->id)->get_q()->to_string();
        UnlimitedInt num(s1); UnlimitedInt den(s2);
        UnlimitedRational* ans = new UnlimitedRational(&num, &den);
        root->evaluated_value = ans;
    }
    else if(root->type == "VAL"){
        UnlimitedInt* p = root->val->get_p(); UnlimitedInt* q = root->val->get_q(); 
        root->evaluated_value = new UnlimitedRational(p,q);
    }
    UnlimitedInt* p = root->evaluated_value->get_p(); UnlimitedInt* q = root->evaluated_value->get_q(); 
    UnlimitedRational* ans = new UnlimitedRational(p,q);
    return ans;
}

Evaluator::Evaluator(){
	this->symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    for(int i=0; i<this->expr_trees.size(); i++){
        delelteHelper(this->expr_trees[i]);
    }
	delete symtable;
}

// Read an input vector of tokens (strings)
// Parse it and convert it to a parse tree
// Push the root of the tree in the expr_trees
void Evaluator::parse(vector<string> code){
    vector<ExprTreeNode*> Q; 
    ExprTreeNode* Var = new ExprTreeNode();
    Var->type = "VAR";
    Var->id = code[0];

    ExprTreeNode* eq = new ExprTreeNode();
    eq->type = ":=";

    for(int i=2; i<code.size(); i++){
        if(code[i]=="("){
            continue;
        }
        else if(code[i]=="+"){
            ExprTreeNode* temp = new ExprTreeNode();
            temp->type = "ADD";
            Q.push_back(temp);
        }
        else if(code[i]=="-"){
            ExprTreeNode* temp = new ExprTreeNode();
            temp->type = "SUB";
            Q.push_back(temp);
        }
        else if(code[i]=="*"){
            ExprTreeNode* temp = new ExprTreeNode();
            temp->type = "MUL";
            Q.push_back(temp);
        }
        else if(code[i]=="/"){
            ExprTreeNode* temp = new ExprTreeNode();
            temp->type = "DIV";
            Q.push_back(temp);
        }
        else if(code[i]==")"){
            ExprTreeNode* r = Q[Q.size()-1]; Q.pop_back();
            ExprTreeNode* m = Q[Q.size()-1]; Q.pop_back();
            ExprTreeNode* l = Q[Q.size()-1]; Q.pop_back();
            m->right = r; m->left = l; 
            Q.push_back(m);
        }
        else if(code[i][0]<=57 && code[i][0]>=48){
            UnlimitedInt v(code[i]);
            string s = "VAL";
            ExprTreeNode* temp=new ExprTreeNode(s,&v);
            Q.push_back(temp);
        }
        else{
            ExprTreeNode* temp = new ExprTreeNode();
            temp->type = "VAR";
            temp->id = code[i];
            Q.push_back(temp);
        }
    }
    eq->right = Q[0];
    eq->left = Var;
    expr_trees.push_back(eq);
}

// Evaluate the last element of the expr_trees
// This function is guaranteed to be called immediately 
// after a call to parse, and will be only called ONCE
// for a tree
// Also populate the symbol tables
void Evaluator::eval(){
    ExprTreeNode* root = this->expr_trees.back();
    UnlimitedRational* ans = EvalHelper(root->right, this->symtable);
    symtable->insert(root->left->id, ans);
    delete ans;
}