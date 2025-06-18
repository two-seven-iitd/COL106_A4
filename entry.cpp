/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry() {
    key = "";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}
SymEntry::SymEntry(string k, UnlimitedRational* v) {
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;

}
SymEntry::~SymEntry() {
    delete val;
    delete left;
    delete right;
    // if (val != nullptr) {
    //     delete val;
    //     val = nullptr;
    // }

    // if (left != nullptr) {
    //     delete left;
    //     left = nullptr;
    // }

    // if (right != nullptr) {
    //     delete right;
    //     right = nullptr;
    // }
}
