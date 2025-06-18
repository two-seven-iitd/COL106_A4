/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    // Delete all expression trees
    for (ExprTreeNode* root : expr_trees) {
        delete root;  
    }
    
    delete symtable;  
}

bool isVariable(const string& token) {
    if (token.empty()) return false;
    char c = token[0];
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isOperator(const string& token) {
    if (token.empty()) return false;
    return token=="+" || token=="-" || token=="/" || token=="*" || token=="%";
}

void Evaluator::parse(vector<string> code) {
    vector<ExprTreeNode*> nodeStack;
    vector<string> tokenStack;

    for(int i=0; i<code.size(); i++) {
        if(i==0) {  //var
            ExprTreeNode* node = new ExprTreeNode;
            node->type = "VAR";
            node->id = code[0];
            nodeStack.push_back(node);
        }
        else if(i == 1) {//assignment
            ExprTreeNode* node = new ExprTreeNode;
            node->type = "ASSIGN";
            node->id = "";
            nodeStack.push_back(node);
        }
        else if(code[i] == "(" ) {
            tokenStack.push_back("(");

        }
        else if(code[i] == ")") {
            tokenStack.pop_back();
            ExprTreeNode* right = nodeStack.back(); nodeStack.pop_back();
            ExprTreeNode* op = nodeStack.back(); nodeStack.pop_back();
            ExprTreeNode* left = nodeStack.back(); nodeStack.pop_back();

            op->left = left;
            op->right = right;

            nodeStack.push_back(op);
        }
        else if(isOperator(code[i])) {
            if(code[i] == "+") {
                ExprTreeNode* node = new ExprTreeNode();
                node->type = "ADD";
                node->id = "";
                nodeStack.push_back(node);
            }
            else if(code[i] == "-") {
                ExprTreeNode* node = new ExprTreeNode();
                node->type = "SUB";
                node->id = "";
                nodeStack.push_back(node);
            }
            else if(code[i] == "*") {
                ExprTreeNode* node = new ExprTreeNode();
                node->type = "MUL";
                node->id = "";
                nodeStack.push_back(node);
            }
            else if(code[i] == "/") {
                ExprTreeNode* node = new ExprTreeNode();
                node->type = "DIV";
                node->id = "";
                nodeStack.push_back(node);
            }
            // else if(code[i] == "%") {
            //     ExprTreeNode* node = new ExprTreeNode();
            //     node->type = "MOD";
            //     node->id = "";
            //     nodeStack.push_back(node);
            // }
        }
        else if(isVariable(code[i])) {
            ExprTreeNode* node = new ExprTreeNode();
            node->type = "VAR";
            node->id = code[i];
            nodeStack.push_back(node);
        }
        else {
            UnlimitedInt* val = new UnlimitedInt(code[i]);
            ExprTreeNode* node = new ExprTreeNode("VAL",val);
            nodeStack.push_back(node);
        }
    }
    // build final, = at root, var at left and other at right
    ExprTreeNode* assign = nodeStack[1];
    assign->left = nodeStack[0];
    assign->right = nodeStack.back();
    
    expr_trees.push_back(assign);
}
UnlimitedRational* evalHelper(ExprTreeNode* node, SymbolTable* symbolTable) {
    if (!node) return nullptr;
    if (node->type == "VAL") {
        node->evaluated_value = node->val;
    } else if (node->type == "VAR") {
        node->evaluated_value = symbolTable->search(node->id);
    } else {
        UnlimitedRational* leftResult = evalHelper(node->left, symbolTable);
        UnlimitedRational* rightResult = evalHelper(node->right, symbolTable);
        if (leftResult && rightResult) {
            if (node->type == "ADD") {
                node->evaluated_value = UnlimitedRational::add(leftResult, rightResult);
            } 
            else if (node->type == "SUB") {
                node->evaluated_value = UnlimitedRational::sub(leftResult, rightResult);
            } 
            else if (node->type == "MUL") {
                node->evaluated_value = UnlimitedRational::mul(leftResult, rightResult);
            } 
            else if (node->type == "DIV") {
                node->evaluated_value = UnlimitedRational::div(leftResult, rightResult);
            }
            // else if (node->type == "MOD") {
            //     node->evaluated_value = UnlimitedRational::mod(leftResult, rightResult);
            // }
        }
    }
    return node->evaluated_value;
}
void Evaluator::eval() {
    if (expr_trees.empty()) return;
    ExprTreeNode* root = expr_trees.back();
    if (!root) return;
    UnlimitedRational* result = evalHelper(root->right, symtable);
    symtable->insert(root->left->id, result);
}