/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
using namespace std; 

UnlimitedInt* GCD(UnlimitedInt* i1, UnlimitedInt* i2){
    string s1 = i1->to_string(); string s2 = i2->to_string();
    UnlimitedInt* a = new UnlimitedInt(s1); UnlimitedInt* b = new UnlimitedInt(s2); UnlimitedInt* rem = UnlimitedInt::mod(a,b); 
    while(b->to_string()!="0"){
        delete a;
        a = new UnlimitedInt(b->to_string()); 
        delete b;
        b = new UnlimitedInt(rem->to_string());
        delete rem;
        rem = UnlimitedInt::mod(a,b);
    }
    UnlimitedInt* ans = new UnlimitedInt(a->to_string());
    delete a; delete b; delete rem;
    return ans;
}

UnlimitedRational::UnlimitedRational(){
    this->p = new UnlimitedInt(1); this->q = new UnlimitedInt(1);
}
    
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    if(den->get_sign()==0){
        UnlimitedInt* temp1 = new UnlimitedInt(0); this->p = temp1; 
        UnlimitedInt* temp2 = new UnlimitedInt(0); this->q = temp2;
        return;
    }
    UnlimitedInt* g = GCD(num,den);
    if(g->to_string()=="1"){
        string s1 = num->to_string(); string s2 = den->to_string();
        UnlimitedInt* temp1 = new UnlimitedInt(s1); this->p = temp1; 
        UnlimitedInt* temp2 = new UnlimitedInt(s2); this->q = temp2;
    }
    else{
        this->p = UnlimitedInt::div(num,g); this->q = UnlimitedInt::div(den,g);
    }
    delete g;
}

UnlimitedRational::~UnlimitedRational(){
    delete p; delete q; 
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
} // Return the numerator as a string

string UnlimitedRational::get_q_str(){
    return q->to_string();
}; // Return the denominator as a string
    
string UnlimitedRational::get_frac_str(){
    string s="";
    string s1 = p->to_string(); string s2 = q->to_string();
    s = (s1 + "/" + s2);
    return s;
}; // Return the rational as "p/q"

    // Rational arithmetic operations
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q()->get_sign()==0 || i2->get_q()->get_sign()==0){
        UnlimitedInt* temp1 = new UnlimitedInt(0); 
        UnlimitedInt* temp2 = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(temp1,temp2);
        delete temp1; delete temp2; 
        return ans;
    }
    UnlimitedInt* num1 = UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* num2 = UnlimitedInt::mul(i1->get_q(),i2->get_p());
    UnlimitedInt* num = UnlimitedInt::add(num1,num2);
    UnlimitedInt* den = UnlimitedInt::mul(i1->get_q(),i2->get_q());

    delete num1, delete num2;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    delete num; delete den;
    return ans;

}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q()->get_sign()==0 || i2->get_q()->get_sign()==0){
        UnlimitedInt* temp1 = new UnlimitedInt(0); 
        UnlimitedInt* temp2 = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(temp1,temp2);
        delete temp1; delete temp2;
        return ans;
    }
    UnlimitedInt* num1 = UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* num2 = UnlimitedInt::mul(i1->get_q(),i2->get_p());
    UnlimitedInt* num = UnlimitedInt::sub(num1,num2);
    UnlimitedInt* den = UnlimitedInt::mul(i1->get_q(),i2->get_q());

    delete num1, delete num2;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    delete num; delete den;
    return ans;
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q()->get_sign()==0 || i2->get_q()->get_sign()==0){
        UnlimitedInt* temp1 = new UnlimitedInt(0); 
        UnlimitedInt* temp2 = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(temp1,temp2);
        delete temp1; delete temp2;
        return ans;
    }
    UnlimitedInt* num = UnlimitedInt::mul(i1->get_p(),i2->get_p());
    UnlimitedInt* den = UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedRational* ans = new UnlimitedRational(num,den);
    delete num; delete den;
    return ans;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q()->get_sign()==0 || i2->get_q()->get_sign()==0 || i2->get_p()->get_sign()==0){
        UnlimitedInt* temp1 = new UnlimitedInt(0); 
        UnlimitedInt* temp2 = new UnlimitedInt(0);
        UnlimitedRational* ans = new UnlimitedRational(temp1,temp2);
        delete temp1; delete temp2;
        return ans;
    }
    UnlimitedInt* num = UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* den = UnlimitedInt::mul(i1->get_q(),i2->get_p());
    UnlimitedRational* ans = new UnlimitedRational(num,den);
    delete num; delete den;
    return ans;
}