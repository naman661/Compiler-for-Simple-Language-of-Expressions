/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){

}

SymNode::SymNode(string k){
    key = k;
}

void updateheight(SymNode* root){
    if (root == NULL){
        root->height = -1;
    }
    else{
        updateheight(root->right);
        updateheight(root->left);
        root->height = max(root->right->height,root->left->height) + 1;
    }
}


SymNode* SymNode::LeftLeftRotation(){
    return NULL; 
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
     left = NULL;
     right = NULL;
}