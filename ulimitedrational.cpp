/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include <stdexcept>
#include <iostream>
// Helper function to compute GCD of two UnlimitedInt* values
bool iszero(UnlimitedInt* z) {
        if (z->get_array()[z->get_size()-1]!= 0) {
            return false;
        }
    
    return true;
}

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b) {
    UnlimitedInt* x = new UnlimitedInt(a->get_array(), a->get_capacity(), 1, a->get_size());
    UnlimitedInt* y = new UnlimitedInt(b->get_array(), b->get_capacity(), 1, b->get_size());
    UnlimitedInt* difference = x->sub(x, y);
    if (difference->get_sign() != x->get_sign()) {
        UnlimitedInt* temp = y;
        y = x;
        x = temp;
    }
    delete difference;
    
    UnlimitedInt* remainder = UnlimitedInt::mod(x, y);
    while (!iszero(remainder)) {
        delete x;
        x = y;
        y = remainder;
        remainder = UnlimitedInt::mod(x, y);
    }
    delete x;
    delete remainder;
    return y;
}


UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if (den->get_sign() == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }

    UnlimitedInt* g = gcd(new UnlimitedInt(*num), new UnlimitedInt(*den));
    p = UnlimitedInt::div(num, g);
    q = UnlimitedInt::div(den, g);
    delete g;

    if (q->get_sign() == -1) {
        p->set_sign(p->get_sign() * -1);  // Flip numerator sign
        q->set_sign(1);                   // Make denominator positive
    }
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->to_string();
}

string UnlimitedRational::get_q_str() {
    return q->to_string();
}

string UnlimitedRational::get_frac_str() {
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* num1 = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* num2 = UnlimitedInt::mul(i2->p, i1->q);
    UnlimitedInt* numerator = UnlimitedInt::add(num1, num2);
    delete num1; delete num2;

    UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* res = new UnlimitedRational(numerator, denominator);
    delete numerator;
    delete denominator;
    return res;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* num1 = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* num2 = UnlimitedInt::mul(i2->p, i1->q);
    UnlimitedInt* numerator = UnlimitedInt::sub(num1, num2);
    delete num1; delete num2;

    UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* res = new UnlimitedRational(numerator, denominator);
    delete numerator;
    delete denominator;
    return res;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* numerator = UnlimitedInt::mul(i1->p, i2->p);
    UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* res = new UnlimitedRational(numerator, denominator);
    delete numerator;
    delete denominator;
    return res;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
    if (i2->p->get_sign() == 0) {
        throw std::invalid_argument("Division by zero numerator");
    }
    UnlimitedInt* numerator = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedRational* res = new UnlimitedRational(numerator, denominator);
    delete numerator;
    delete denominator;
    return res;
}

// UnlimitedRational::UnlimitedRational() {
//     p = new UnlimitedInt(0);
//     q = new UnlimitedInt(1);
// }

// UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
//     p = new UnlimitedInt(*num);
//     q = new UnlimitedInt(*den);
// }

// UnlimitedRational::~UnlimitedRational() {
//     delete p;
//     delete q;
// }

// UnlimitedInt* UnlimitedRational::get_p() {
//     return p;
// }

// UnlimitedInt* UnlimitedRational::get_q() {
//     return q;
// }

// string UnlimitedRational::get_p_str() {
//     return p->to_string();
// }

// string UnlimitedRational::get_q_str() {
//     return q->to_string();
// }

// string UnlimitedRational::get_frac_str() {
//     return p->to_string() + "/" + q->to_string();
// }

// UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
//     UnlimitedInt* a = UnlimitedInt::mul(i1->p, i2->q);
//     UnlimitedInt* b = UnlimitedInt::mul(i2->p, i1->q);
//     UnlimitedInt* numerator = UnlimitedInt::add(a, b);
//     UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);

//     delete a;
//     delete b;
//     return new UnlimitedRational(numerator, denominator);
// }

// UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
//     UnlimitedInt* a = UnlimitedInt::mul(i1->p, i2->q);
//     UnlimitedInt* b = UnlimitedInt::mul(i2->p, i1->q);
//     UnlimitedInt* numerator = UnlimitedInt::sub(a, b);
//     UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);

//     delete a;
//     delete b;
//     return new UnlimitedRational(numerator, denominator);
// }

// UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
//     UnlimitedInt* numerator = UnlimitedInt::mul(i1->p, i2->p);
//     UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->q);
//     return new UnlimitedRational(numerator, denominator);
// }

// UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
//     UnlimitedInt* numerator = UnlimitedInt::mul(i1->p, i2->q);
//     UnlimitedInt* denominator = UnlimitedInt::mul(i1->q, i2->p);
//     return new UnlimitedRational(numerator, denominator);
// }