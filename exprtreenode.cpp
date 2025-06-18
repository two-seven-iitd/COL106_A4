/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
    type = "";
    val = new UnlimitedRational();
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr;    

}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    type = t;
    val = new UnlimitedRational(v, new UnlimitedInt(1));
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr; 

}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    type = t;
    val = v;
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode() {
    // delete val;
    // delete evaluated_value;
    // delete left;
    // delete right;
    if (val != nullptr) {
        delete val;
        val = nullptr;
    }

    if (evaluated_value != nullptr) {
        delete evaluated_value;
        evaluated_value = nullptr;
    }

    if (left != nullptr) {
        delete left;
        left = nullptr;
    }

    if (right != nullptr) {
        delete right;
        right = nullptr;
    }
}
