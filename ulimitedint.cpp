/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt() {
    size = 0;
    sign = 0;
    capacity = 0;
    unlimited_int = nullptr;
}

UnlimitedInt::UnlimitedInt(string s) {
    if(s.empty() || s == "0" || s == "+0" || s == "-0") {
        size = 1;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] =0;
        sign = 0;
        return;
    }
    int stIndex = 0;
    if(s[0]=='-') {
        stIndex = 1;
        sign = -1;
    }
    else if(s[0] == '+') {
        stIndex = 1;
        sign = 1;
    }
    else {
        sign = 1;       //without sign, treated as positive
    }
    size = s.size() - stIndex;
    capacity = size;
    unlimited_int = new int[size]; //memory allocation

    
    for (int i = 0; i < size; i++) {
        unlimited_int[i] = s[s.size() - 1 - i] - '0';
    }

    while (size > 1 && unlimited_int[size - 1] == 0) {
        size--;
    }

    //capacity = size;
    
}

UnlimitedInt::UnlimitedInt(int i) {
    if(i==0) {
        size = 1;
        capacity = 1;
        sign = 0;
        unlimited_int = new int[size];
        unlimited_int[0] = 0;
        return;
    }
    
    sign = (i<0)? -1 : 1;
    int temp = (i<0)?-i:i;

    int ele = temp;
    size = 0;
    while(ele>0) {
        size++;
        ele/=10;
    }

    capacity = size;
    unlimited_int = new int[capacity]; //memory allocation

    for(int i=0; i<size; i++) {
        unlimited_int[i] = temp%10;
        temp/=10;
    }
    
}

UnlimitedInt::UnlimitedInt(int* unlimited_int, int cap, int sgn, int sz) {
    this->capacity = cap;
    this->sign = sgn;
    this->size = sz;
    this->unlimited_int = new int[cap];

    for(int i=0; i<sz; i++) {
        this->unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}