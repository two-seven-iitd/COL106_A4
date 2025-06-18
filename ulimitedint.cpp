/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <algorithm>
#include <stdexcept>

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

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
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

void UnlimitedInt::set_sign(int s) {
    if (s == 1 || s == -1 || s == 0)
        sign = s;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign() == 0) {
        return new UnlimitedInt(i2->get_array(),i2->get_capacity(),i2->get_sign(),i2->get_size());
    }
    if (i2->get_sign() == 0) {
        return new UnlimitedInt(i1->get_array(),i1->get_capacity(),i1->get_sign(),i1->get_size());
    }

    if (i1->get_sign() != i2->get_sign()) { //converted to subtraction
        UnlimitedInt* temp = new UnlimitedInt(i2->get_array(),i2->get_capacity(),-i2->get_sign(),i2->get_size());
        UnlimitedInt* result = UnlimitedInt::sub(i1,temp);
        delete temp;
        return result;
    }
    int size_i1 = i1->get_size();
    int size_i2 = i2->get_size();
    int max_size = std::max(size_i1, size_i2);
    int* result = new int[max_size + 1];
    for (int i = 0; i < max_size + 1; i++) {
        result[i] = 0;
    }

    int carry = 0;

    int* array_i1 = i1->get_array();
    int* array_i2 = i2->get_array();
    for (int i = 0; i < max_size; i++) {
        int digit1 = (i < size_i1) ? array_i1[i] : 0;
        int digit2 = (i < size_i2) ? array_i2[i] : 0;
        int sum = digit1 + digit2 + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        result[max_size] = carry;
        max_size++;
    }
    // result sign is anyof i1 or i2
    return new UnlimitedInt(result,max_size, i1->get_sign(), max_size);
}
// function for checking if abs(i1) > abs(i2)
int compare_abs(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* array_i1 = i1->get_array();
    int* array_i2 = i2->get_array();
    int size_i1 = i1->get_size();
    int size_i2 = i2->get_size();

    if (size_i1 != size_i2) return (size_i1 > size_i2) ? 1 : -1;
    for (int i = size_i1 - 1; i >= 0; i--) {
        if (array_i1[i] != array_i2[i])
            return (array_i1[i] > array_i2[i]) ? 1 : -1;
    }
    return 0;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* array_i1 = i1->get_array();
    int* array_i2 = i2->get_array();
    int size_i1 = i1->get_size();
    int size_i2 = i2->get_size();

    if (i2->get_sign() == 0) {
        return new UnlimitedInt(array_i1,i1->get_capacity(),i1->get_sign(),size_i1);
    }
    if (i1->get_sign() == 0) {
        int* result = new int[size_i2];
        for (int i = 0; i < size_i2; i++) result[i] = array_i2[i];
        return new UnlimitedInt(result,size_i2,-i2->get_sign(),size_i2);
    }

    if (i1->get_sign() != i2->get_sign()) {
        UnlimitedInt* temp = new UnlimitedInt(array_i2,i2->get_capacity(),-i2->get_sign(),size_i2);
        UnlimitedInt* result = UnlimitedInt::add(i1, temp);
        delete temp;
        return result;
    }

    int cmp = compare_abs(i1, i2);

    UnlimitedInt *larger, *smaller;
    int* array_larger = array_i1;
    int* array_smaller = array_i2;
    int size_larger = size_i1;
    int size_smaller = size_i2;
    int result_sign;

    if (cmp >= 0) {         // abs(i1) > abs(i2)
        larger = i1; smaller = i2;
        result_sign = i1->get_sign();
        
    } 
    else {                // abs(i2) > abs(i1)
        larger = i2; smaller = i1;
        result_sign = -i1->get_sign();
        array_larger = array_i2;
        array_smaller = array_i1;
        size_larger = size_i2;
        size_smaller = size_i1;
    }

    int* result = new int[size_larger];
    for (int i = 0; i < size_larger; i++) {
        result[i] = 0;
    }

    int borrow = 0;
    for (int i = 0; i < size_larger; i++) {
        int digit1 = array_larger[i];
        int digit2 = (i < size_smaller) ? array_smaller[i] : 0;
        int sub = digit1 - digit2 - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } 
        else {
            borrow = 0;
        }
        result[i] = sub;
    }
    // removing trailin zeroes
    int new_size = size_larger;
    while (new_size > 1 && result[new_size - 1] == 0) {
        new_size--;
    } 
    // checking if value becomes zero, to be consistent with signs
    int final_sign = (new_size == 1 && result[0] == 0) ? 0 : result_sign;

    return new UnlimitedInt(result, size_larger, final_sign, new_size);
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign() == 0 || i2->get_sign() == 0) {
        return new UnlimitedInt(0);
    }
    
    int* array_i1 = i1->get_array();
    int* array_i2 = i2->get_array();
    int size_i1 = i1->get_size();
    int size_i2 = i2->get_size();

    int result_size = size_i1 + size_i2;
    int result_sign = i1->get_sign()*i2->get_sign();
    int* result = new int[result_size];

    for(int i=0; i<result_size; i++) {
        result[i] = 0;
    }

    for(int i=0; i<size_i1; i++) {
        for(int j=0; j<size_i2; j++) {
            result[i+j]+= array_i1[i]*array_i2[j];
        }
    }
    int carry = 0;
    for(int i=0; i<result_size; i++) {
        result[i]+=carry;
        carry = result[i]/10;
        result[i]%=10;
    } 
    int final_size = result_size;
    while(final_size >1 && result[final_size-1]==0) {
        final_size--;
    }
    if (final_size == 1 && result[0] == 0) {
        result_sign = 0;
    }
    return new UnlimitedInt(result,result_size,result_sign, final_size);
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i2->get_sign() == 0) {
        throw std::invalid_argument("Division by zero");
    }
    
    int cmp = compare_abs(i1, i2);
    
    if (cmp < 0) {
        return new UnlimitedInt(0);
    }
    if (cmp == 0) {
        return new UnlimitedInt(i1->get_sign() * i2->get_sign());
    }
    
    int size_i1 = i1->get_size();
    int* array_i1 = i1->get_array();
    
    int* quotient = new int[size_i1](); // Initialize with zeros
    UnlimitedInt* remainder = new UnlimitedInt(0);
    
    // Process digits from most significant to least significant
    for (int i = size_i1 - 1; i >= 0; i--) {
        // Shift remainder left by one position and add new digit
        int rem_size = remainder->get_size();
        int* rem_array = remainder->get_array();
        
        // Create new remainder: remainder * 10 + array_i1[i]
        int* new_digits = new int[rem_size + 1];
        
        // Shift existing digits left (multiply by 10)
        int carry = 0;
        for (int j = 0; j < rem_size; j++) {
            int temp = rem_array[j] * 10 + carry;
            new_digits[j] = temp % 10;
            carry = temp / 10;
        }
        
        // Add carry digits if any
        int new_size = rem_size;
        while (carry > 0) {
            new_digits[new_size] = carry % 10;
            carry /= 10;
            new_size++;
        }
        
        // Add the new digit
        new_digits[0] += array_i1[i];
        carry = new_digits[0] / 10;
        new_digits[0] %= 10;
        
        // Propagate carry
        for (int j = 1; j < new_size && carry > 0; j++) {
            new_digits[j] += carry;
            carry = new_digits[j] / 10;
            new_digits[j] %= 10;
        }
        
        while (carry > 0 && new_size < rem_size + 1) {
            new_digits[new_size] = carry % 10;
            carry /= 10;
            new_size++;
        }
        
        delete remainder;
        remainder = new UnlimitedInt(new_digits, new_size, 1, new_size);
        delete[] new_digits;
        
        // Find the largest digit d such that (i2 * d) <= remainder
        int digit = 0;
        for (int d = 9; d >= 1; d--) {
            UnlimitedInt* trial_d = new UnlimitedInt(d);
            UnlimitedInt* product = UnlimitedInt::mul(i2, trial_d);
            delete trial_d;
            
            if (compare_abs(product, remainder) <= 0) {
                digit = d;
                
                // Update remainder = remainder - product
                UnlimitedInt* new_rem = UnlimitedInt::sub(remainder, product);
                delete remainder;
                remainder = new_rem;
                delete product;
                break;
            }
            delete product;
        }
        
        // Store the digit in the correct position
        quotient[i] = digit;
    }
    
    delete remainder;
    
    // Remove leading zeros from quotient
    int final_size = size_i1;
    while (final_size > 1 && quotient[final_size - 1] == 0) {
        final_size--;
    }
    
    // Determine sign
    int final_sign = (final_size == 1 && quotient[0] == 0) ? 0 : (i1->get_sign() * i2->get_sign());
    
    // Create result - make a copy of quotient array
    int* result_array = new int[final_size];
    for (int i = 0; i < final_size; i++) {
        result_array[i] = quotient[i];
    }
    delete[] quotient;
    
    return new UnlimitedInt(result_array, final_size, final_sign, final_size);
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i2->get_sign() == 0) {
        throw std::invalid_argument("Modulo by zero");
    }

    UnlimitedInt* quotient = div(i1, i2);           // q = i1 / i2
    UnlimitedInt* product = mul(quotient, i2);      // q * i2
    UnlimitedInt* modResult = sub(i1, product);     // i1 - (q * i2)

    delete quotient;
    delete product;

    return modResult;
}

string UnlimitedInt::to_string() {
    string str;
    if (sign == -1) {
        str = "-";
    }
    int i = size - 1;
    while (i >= 0 && unlimited_int[i] == 0) {
        --i;
    }
    if (i == -1) {
        return "0";
    }
    while (i >= 0) {
        str += ('0' + unlimited_int[i]);
        i--;
    }
    return str;
}