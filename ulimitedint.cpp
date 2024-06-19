/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;
#include <iostream>
#include <vector>

UnlimitedInt* by2(UnlimitedInt* c){
    string s = c->to_string();
    UnlimitedInt a(s);
    int* initial = a.get_array();
    int sz = a.get_size();
    int arr[sz];
    for(int i=0; i<sz; i++){
        arr[i]=initial[i];
    }
    if(arr[0]<=1){sz--;}
    int temp[sz];
    if(arr[0]<=1){sz++;}
    for(int i=(sz-1); i>0; i--){
        if(arr[i-1]%2==0){arr[i]=arr[i]/2;}
        else{
            arr[i-1]--; arr[i]=(10+arr[i])/2;
        }
    }
    arr[0]/=2;
    if(arr[0]==0){ 
        sz--;
        for(int i=0; i<(a.get_size()-1); i++){
            temp[i]=arr[i+1];
        }
    }
    else{
        for(int i=0; i<(a.get_size()); i++){
            temp[i]=arr[i];
        }
    }
    UnlimitedInt* ans = new UnlimitedInt(temp, 0, 1, sz);
    return ans;
}

UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 0;
    unlimited_int = new int[1];
    unlimited_int[0] = 0;
}

int isBigger(UnlimitedInt &i1, UnlimitedInt &i2){
    int bigger = 0; 
    if(i1.get_size()>i2.get_size()){bigger = 1;}
    else if(i1.get_size()<i2.get_size()){bigger = 2;}
    else{
        int* arr1 = i1.get_array();
        int* arr2 = i2.get_array();
        for(int i=0; i<(i1.get_size()); i++){
            if(arr1[i]>arr2[i]){
                bigger = 1;
                break;
            }
            else if(arr1[i]<arr2[i]){
                bigger = 2;
                break;
            }
        }
    }
    return bigger;
}

UnlimitedInt::UnlimitedInt(string s){
    size = s.size();
    sign = 1; 
    capacity = s.size();

    if(s[0]=='-'){sign = -1; capacity--; size--;}
    else if(s[0]=='0'){sign = 0;};

    unlimited_int = new int[capacity];
    if(sign == 1){
        for(int i=0; i<(s.size()); i++){
            unlimited_int[i] = s[i] - 48;
        }
    }
    else if(sign == -1){
        for(int i=1; i<(s.size()); i++){
            unlimited_int[i-1] = s[i] - 48;
        }
    }
    else{
        unlimited_int[0]=0;
    }
}

UnlimitedInt::UnlimitedInt(int i){
    size = 0; capacity=0; sign = 1; int tempStorage[10]={0};
    if(i == 0){
        size++; sign = 0;
    }
    else if(i>0){
        int pos = 9; 
        while(i!=0){
            tempStorage[pos]=i%10;
            i=(i/10);
            pos--;
            size++;
        }
    }
    else if(i<0){
        int pos = 9; 
        sign = -1;
        i*=(-1);
        while(i!=0){
            tempStorage[pos]=i%10;
            i=(i/10);
            pos--;
            size++;
        }
    }
    capacity = size;
    unlimited_int = new int[size];
    for(int i=0; i<size; i++){
        unlimited_int[i]=tempStorage[10-size+i];
    }
} // Create from int

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    this->unlimited_int = new int[sz];
    for(int i=0; i<sz; i++){
        this->unlimited_int[i]=ulimited_int[i];
    }
    this->size = sz; 
    this->capacity = cap; 
    this->sign = sgn;
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

    // Return the size of the unlimited int
int UnlimitedInt::get_size(){
    return size;
}

    // Return the unlimited_int array
int* UnlimitedInt::get_array(){
    return unlimited_int;
}

    // Get sign
int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

    // Implement these integer operations as they are defined for integers in mathematics
    // (Since there are no size restrictions)
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* ini1, UnlimitedInt* ini2){
    string s1 = ini1->to_string(); string s2 = ini2->to_string();
    UnlimitedInt i1(s1); UnlimitedInt i2(s2);
    if(i1.get_sign()==0){
        UnlimitedInt* answer = new UnlimitedInt(s2);
        return answer;
    }
    if(i2.get_sign()==0){
        UnlimitedInt* answer = new UnlimitedInt(s1);
        return answer;
    }
    int sz; int small; int itsSign=1;
    int* arr; string ans;
    if(i1.get_size()>i2.get_size()){
        sz = i1.get_size(); small = i2.get_size();
    }
    else{
        sz = i2.get_size(); small = i1.get_size();
    }
    if(i1.get_sign()!=i2.get_sign()){
        if(isBigger(i1,i2)==0){
            UnlimitedInt* answer = new UnlimitedInt(0);
            return answer;
        }
    }
    int temparr[sz];
    if(i1.get_sign() == i2.get_sign()){
        itsSign = i1.get_sign();
        if(i1.get_size()>i2.get_size()){
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i1.get_array()[sz-small+i] + i2.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i1.get_array()[i];
            }
        }
        else{
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i2.get_array()[sz-small+i] + i1.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i2.get_array()[i];
            }
        }
        for(int i=(sz-1); i>0; i--){
            if(temparr[i]>9){temparr[i-1]++; temparr[i]=temparr[i]-10;}
        }
        if(temparr[0]>9){
            sz++;
            temparr[0]=temparr[0]-10;
            arr= new int[sz];
            for(int i = (sz-1); i>0; i--){
                arr[i]=temparr[i-1];
            }
            arr[0]= 1;
        }
        else{
            arr= new int[sz];
            for(int i=0; i<sz; i++){
                arr[i]=temparr[i];
            }
        }
    }
    else{
        int bigger = 0; 
        if(i1.get_size()>i2.get_size()){bigger = 1;if(i1.get_sign()==-1){itsSign=-1;}}
        else if(i1.get_size()<i2.get_size()){bigger = 2;if(i2.get_sign()==-1){itsSign=-1;}}
        else{
            int* arr1 = i1.get_array();
            int* arr2 = i2.get_array();
            for(int i=0; i<(i1.get_size()); i++){
                if(arr1[i]>arr2[i]){
                    bigger = 1;
                    if(i1.get_sign()==-1){itsSign=-1;}
                    break;
                }
                else if(arr1[i]<arr2[i]){
                    bigger = 2;
                    if(i2.get_sign()==-1){itsSign=-1;}
                    break;
                }
            }
        }
        if(bigger == 1){
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i1.get_array()[sz-small+i] - i2.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i1.get_array()[i];
            }
        }
        else{
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i2.get_array()[sz-small+i] - i1.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i2.get_array()[i];
            }
        }
        for(int i=(sz-1); i>=0; i--){
            if(temparr[i]<0){temparr[i-1]--; temparr[i]=temparr[i]+10;}
        }
        int count=0;
        for(int i = 0 ; i<sz; i++){
            if(temparr[i]==0){count++;}
            else{
                break;
            }
        }
        sz = sz - count;
        if(sz == 0){arr = new int[1]; sz++; arr[0]=0;}
        else{
            arr = new int[sz];
            for(int i =0; i<(sz); i++){
                arr[i]=temparr[i+count];
            }
        }
    }
    if(itsSign==-1){ans+='-';}
    for(int i =0; i<sz; i++){
        ans += std::to_string(arr[i]);
    }
    delete[] arr;
    UnlimitedInt* answer = new UnlimitedInt(ans);
    return answer;
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* ini1, UnlimitedInt* ini2){
    string s1 = ini1->to_string(); string s2 = ini2->to_string();
    UnlimitedInt i1(s1); UnlimitedInt i2(s2);
    int sz; int small; int itsSign=1;
    int* arr; string ans;
    if(i1.get_size()>i2.get_size()){
        sz = i1.get_size(); small = i2.get_size();
    }
    else{
        sz = i2.get_size(); small = i1.get_size();
    }
    if(i1.get_sign()==i2.get_sign()){
        if(isBigger(i1,i2)==0){
            UnlimitedInt* answer = new UnlimitedInt(0);
            return answer;
        }
    }
    int temparr[sz];
    if(i1.get_sign() != i2.get_sign()){
        itsSign = i1.get_sign();
        if(i1.get_size()>i2.get_size()){
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i1.get_array()[sz-small+i] + i2.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i1.get_array()[i];
            }
        }
        else{
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i2.get_array()[sz-small+i] + i1.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i2.get_array()[i];
            }
        }
        for(int i=(sz-1); i>0; i--){
            if(temparr[i]>9){temparr[i-1]++; temparr[i]=temparr[i]-10;}
        }
        if(temparr[0]>9){
            sz++;
            temparr[0]=temparr[0]-10;
            arr= new int[sz];
            for(int i = (sz-1); i>0; i--){
                arr[i]=temparr[i-1];
            }
            arr[0]= 1;
        }
        else{
            arr= new int[sz];
            for(int i=0; i<sz; i++){
                arr[i]=temparr[i];
            }
        }
    }
    else{
        int bigger = 0; 
        if(i1.get_size()>i2.get_size()){bigger = 1;if(i1.get_sign()==-1){itsSign=-1;}}
        else if(i1.get_size()<i2.get_size()){bigger = 2;if(i2.get_sign()==1){itsSign=-1;}}
        else{
            int* arr1 = i1.get_array();
            int* arr2 = i2.get_array();
            for(int i=0; i<(i1.get_size()); i++){
                if(arr1[i]>arr2[i]){
                    bigger = 1;
                    if(i1.get_sign()==-1){itsSign=-1;}
                    break;
                }
                else if(arr1[i]<arr2[i]){
                    bigger = 2;
                    if(i2.get_sign()==1){itsSign=-1;}
                    break;
                }
            }
        }
        if(bigger == 1){
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i1.get_array()[sz-small+i] - i2.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i1.get_array()[i];
            }
        }
        else{
            for(int i=(small-1); i>=0; i--){
                temparr[sz-small + i]= i2.get_array()[sz-small+i] - i1.get_array()[i];
            }
            for(int i=0; i<(sz-small); i++){
                temparr[i]=i2.get_array()[i];
            }
        }
        for(int i=(sz-1); i>=0; i--){
            if(temparr[i]<0){temparr[i-1]--; temparr[i]=temparr[i]+10;}
        }
        int count=0;
        for(int i = 0 ; i<sz; i++){
            if(temparr[i]==0){count++;}
            else{
                break;
            }
        }
        sz = sz - count;
        if(sz == 0){arr = new int[1]; sz++; arr[0]=0;}
        else{
            arr = new int[sz];
            for(int i =0; i<(sz); i++){
                arr[i]=temparr[i+count];
            }
        }
    }
    if(itsSign==-1){ans+='-';}
    for(int i =0; i<sz; i++){
        ans += std::to_string(arr[i]);
    }
    delete[] arr;
    UnlimitedInt* answer = new UnlimitedInt(ans);
    return answer;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* ini1, UnlimitedInt* ini2) {
    std::string s1 = ini1->to_string();
    std::string s2 = ini2->to_string();
    UnlimitedInt i1(s1);
    UnlimitedInt i2(s2);
    int* arr1 = i1.get_array();
    int* arr2 = i2.get_array();
    int size1 = i1.get_size();
    int size2 = i2.get_size();
    int sign1 = i1.get_sign();
    int sign2 = i2.get_sign();

    if (sign1 == 0 || sign2 == 0) {
        return new UnlimitedInt(0);
    }

    int* result = new int[size1 + size2];
    std::memset(result, 0, (size1 + size2) * sizeof(int));  
    int itsSign = (sign1 == sign2) ? 1 : -1;

    for (int i = size1 - 1; i >= 0; i--) {
        for (int j = size2 - 1; j >= 0; j--) {
            result[i + j + 1] += arr1[i] * arr2[j];
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    std::string ans;
    if (itsSign == -1) {
        ans += '-';
    }

    bool leadingZero = true;
    for (int i = 0; i < size1 + size2; i++) {
        if (result[i] != 0) {
            leadingZero = false;
        }
        if (!leadingZero) {
            ans += std::to_string(result[i]);
        }
    }

    delete[] result;  
    if (ans.empty() || ans == "-") {
        ans = "0";
    }
    return new UnlimitedInt(ans);
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* ini1, UnlimitedInt* ini2){
    string s1 = ini1->to_string(); string s2 = ini2->to_string();
    UnlimitedInt i1(s1); UnlimitedInt i2(s2);
    int* arr1 = i1.get_array(); int* arr2 = i2.get_array();
    int size1 = i1.get_size() ; int size2 = i2.get_size();
    int sign1 = i1.get_sign() ; int sign2 = i2.get_sign();

    int itsSign=1;
    if(sign1 != sign2){itsSign=-1;}

    if(i2.to_string()=="1"){
        UnlimitedInt* obj = new UnlimitedInt(s1);
        return obj;
    }
    if(sign1 == 0 && sign2!= 0){
        UnlimitedInt* obj = new UnlimitedInt(0);
        return obj;
    }
    int bigger = isBigger(i1,i2);
    if(bigger == 2){
        UnlimitedInt* obj = new UnlimitedInt(0);
        return obj;
    }
    else{
        int l = (size1-size2); int r = (size1-size2)+1; 
        int temparr1[r]; 
        for(int i=0; i<r; i++){
            temparr1[i]=9;
        }
        UnlimitedInt* right=new UnlimitedInt(temparr1, 0, 1, r);
        UnlimitedInt* left;
        if(l>0){
            int temparr2[l];
            for(int i=0; i<l; i++){
                temparr2[i]=0;
            }
            temparr2[0]=1;
            left =new UnlimitedInt(temparr2, 0, 1, l);
        }
        else{
            left =new UnlimitedInt(0);
        }
        UnlimitedInt* mid;
        int big;
        while(isBigger(*right,*left)==1){
            UnlimitedInt* sum = UnlimitedInt::add(left,right);
            mid = by2(sum);
            delete sum;
            UnlimitedInt* compare = mul(mid,&i2);
            if(isBigger(*compare,i1)==1){
                UnlimitedInt One(1); 
                delete right;
                right = sub(mid,&One); 
            }
            else if(isBigger(*compare,i1)==2){
                UnlimitedInt One(1); 
                delete left;
                left = add(mid,&One);
            }
            else{
                delete left; delete right;
                string s = mid->to_string();
                left = new UnlimitedInt(s);
                right= new UnlimitedInt(s);
            }
            delete compare;
            delete mid;
        }
        UnlimitedInt* ans; 
        UnlimitedInt* compare = mul(left,&i2);
        big = isBigger(*compare,i1);
        if(big ==0 || big == 2){ans = new UnlimitedInt(left->get_array(), 0, itsSign, left->get_size());}
        else{
            UnlimitedInt One(1); UnlimitedInt* thing = sub(left,&One);
            ans = new UnlimitedInt(thing->get_array(), 0, itsSign, thing->get_size());
            delete thing;
        }
        delete compare; 
        delete left; delete right;
        return ans;
    }
}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* Div = div(i1,i2);
    UnlimitedInt* Mul = mul(i2,Div);
    UnlimitedInt* ans = sub(i1,Mul);
    delete Div; delete Mul;
    return ans;
}

    // Conversion Functions 
string UnlimitedInt::to_string(){
    string ans = "";
    if(sign == -1){
        ans += "-";
    }
    for(int i =0; i<size; i++){
        ans += std::to_string(unlimited_int[i]);
    }
    return ans;
}