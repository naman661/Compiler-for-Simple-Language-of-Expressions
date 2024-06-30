/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//Write your code below this line

SymbolTable::SymbolTable(){

}

bool smaller(string s1, string s2){
    int i1 = s1.length();
    int i2 = s2.length();
    int k = min(i1,i2);
    bool t = true;
    for (int j=0;j<k;j++){
        if (int(s1[j]) < int(s2[j])){
            t = true;
            return true;
            break;
        }
        else if (int(s2[j])<int(s1[j])) {
            t = false;
            return false;
            break;
        }
    }
    if (i1>k){
        t = false;
        return false;
    }
    else{
        return true;
    }
}

string smaller1(string s1, string s2){
    int i1 = s1.length();
    int i2 = s2.length();
    int k = min(i1,i2);
    for (int j=0;j<k;j++){
        if (int(s1[j]) < int(s2[j])){
            return s1;
        }
        else if (int(s2[j])<int(s1[j])) {
            return s2;
        }
    }
    if (i1>k){
        return s2;
    }
    else{
        return s1;
    }
}

SymNode* find(SymNode* root, string k){
    if (root == NULL){
        return NULL;
    }
    else if (root->key == k){
        return root;
    }
    else if (smaller1(root->key,k) == k){
        return find(root->left,k);
    }
    else{
        return find(root->right,k);
    }
}

void LL(SymNode* A){
    SymNode* B = A->left;
    SymNode* C = B->left;
    if (A->par != NULL){
        bool Aisright = true;
        if (A->par->left == A){
            Aisright = false;
        }
        SymNode* P = A->par;
        SymNode* r1 = A->right;
        SymNode* r2 = B->right;
        SymNode* r3 = C->right;
        SymNode* r4 = C->left;
        B->right = A;
        A->par = B;
        A->left = r2;
        r2->par = A;
        B->par = P;
        if (Aisright){
            P->right = B;
        }
        else{
            P->left = B;
        }
    }
    else{
        
        SymNode* r1 = A->right;
        SymNode* r2 = B->right;
        SymNode* r3 = C->right;
        SymNode* r4 = C->left;
        B->right = A;
        A->par = B;
        A->left = r2;
        r2->par = A;
        B->par = NULL;
        
    }
}

void RR(SymNode* A){
    SymNode* B = A->right;
    SymNode* C = B->right;
    if (A->par != NULL){
        bool Aisright = true;
        if (A->par->left == A){
            Aisright = false;
        }
        SymNode* P = A->par;
        SymNode* l1 = A->left;
        SymNode* l2 = B->left;
        SymNode* l3 = C->left;
        SymNode* l4 = C->right;
        B->left = A;
        A->par = B;
        A->right = l2;
        l2->par = A;
        B->par = P;
        if (Aisright){
            P->right = B;
        }
        else{
            P->left = B;
        }
    }
    else{
        
        SymNode* l1 = A->left;
        SymNode* l2 = B->left;
        SymNode* l3 = C->left;
        SymNode* l4 = C->right;
        B->left = A;
        A->par = B;
        A->right = l2;
        l2->par = A;
        B->par = NULL;
        
    }
}





int height(SymNode *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
} 

int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  

SymNode* newNode(string key)  
{  
    SymNode* node = new SymNode();  
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially  
                    // added at leaf  
    return(node);  
}

bool equal1(string s1, string s2){
    int i1 = s1.length();
    int i2 = s2.length();
    int k = min(i1,i2);
    bool t = true;
    if (i1!=i2){
        return false;
    }
    for (int j=0;j<k;j++){
        if (int(s1[j]) < int(s2[j])){
            return false;
            break;
        }
        else if (int(s2[j])<int(s1[j])) {
            t = false;
            return false;
            break;
        }
    }
    return true;
}

SymNode *rightRotate(SymNode *y)  
{  
    SymNode *x = y->left;  
    SymNode *T2 = x->right;  
  
    x->right = y;  
    y->left = T2;  
  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
  
    return x;  
}

SymNode *leftRotate(SymNode *x)  
{  
    SymNode *y = x->right;  
    SymNode *T2 = y->left;  
  
    y->left = x;  
    x->right = T2;  
  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    return y;  
}

int getBalance(SymNode *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}


SymNode* inserting(SymNode* node, string key)  
{  
    if (node == NULL)  
        return(newNode(key));  
  
    if (smaller(key,node->key))  
        node->left = inserting(node->left, key);  
    else if (!smaller(key,node->key))  
        node->right = inserting(node->right, key);  
    else   
        return node;  
  
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    int balance = getBalance(node);  
  
  
    if (balance > 1 && (smaller(key,node->left->key)))  
        return rightRotate(node);  
  
    if (balance < -1 &&  (smaller(node->right->key,key)))  
        return leftRotate(node);  
  
    if (balance > 1 && (smaller(node->left->key,key)))  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    if (balance < -1 && ((smaller(key,node->right->key))))  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    return node;  
}



void SymbolTable::insert(string k){
    if (find(root,k)!=NULL){
        return ;
    }
    SymNode* N = inserting(root,k);
    root = N;
    size++;
}



SymNode * minValueNode(SymNode* node)  
{  
    SymNode* current = node;  
  
    /* loop down to find the leftmost leaf */  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

SymNode* deleteNode(SymNode* root, string key)  
{  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies  
    // in left subtree  
    if (  (smaller(key,root->key)) && !(equal1(key,root->key)) )  
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if(  (smaller(root->key,key)) && !(equal1(root->key,key)))  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else  
    {  
        // node with only one child or no child  
        if( (root->left == NULL) ||  
            (root->right == NULL) )  
        {  
            SymNode *temp = root->left ?  
                        root->left :  
                        root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                        // the non-empty child  
            free(temp);  
        }  
        else  
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            SymNode* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;  
            root->address = temp->address;
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                    temp->key);  
        }  
    }  
  
    // If the tree had only one node  
    // then return  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),  
                        height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}


void SymbolTable::remove(string k){
    if (find(root,k) == NULL){
        return ;
    }
    else{
        SymNode* N = deleteNode(root,k);
        
        root = N;
        size--;

    }
}



int SymbolTable::search(string k){
    SymNode* s = find(root,k);
    if (s != NULL){

        return s->address;
    }
    else{
        return -2;
    }
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* N = find(root,k);
    N->address = idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
     delete root;
}


