/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    SymbolTable* s = new SymbolTable();
    symtable = s;
}

ExprTreeNode* getparent(vector<vector <ExprTreeNode*>> P,ExprTreeNode* child){
    for (int i=0;i<P.size();i++){
        if (P[i][0] == child){
            return P[i][1];
        }
    }
    return NULL;
}

ExprTreeNode* buildtree(vector <string> v){
    ExprTreeNode* root = new ExprTreeNode();
    vector <vector<ExprTreeNode*>> P;
    ExprTreeNode* cur = root;
    for (int i=0;i<v.size();i++){
        string s = v[i];
        if (s=="("){
            ExprTreeNode* l = new ExprTreeNode();
            cur->left = l;
            P.push_back({l,cur});
            
            cur = cur->left;
        }
        else if (s == "+" || s == "-" || s == "*" || s == "/"){
            if (s=="+"){
                cur->type = "ADD";
            }
            else if (s=="-"){
                cur->type = "SUB";
            }
            else if (s=="*"){
                cur->type = "MUL";
            }
            else if (s=="/"){
                cur->type = "DIV";
            }

            ExprTreeNode* r = new ExprTreeNode();
            cur->right = r;
            P.push_back({r,cur});
            cur = cur->right;
        }

        else if (s == ")"){
            ExprTreeNode* p = getparent(P,cur);
            cur = p;
        }

        else{
            bool isval = true;
            for (int i=0;i<s.length();i++){
                if (!isdigit(s[i])){
                    isval = false;
                    break;
                }
            }
            if (s[0] == '-'){
                isval = true;
            }

            if (isval){
                cur->type = "VAL";
                cur->num = stoi(s);
                ExprTreeNode* p = getparent(P,cur);
                cur = p;
            }
            else{
                cur->type = "VAR";
                cur->id = s;
                
                ExprTreeNode* p = getparent(P,cur);
                cur = p;
            }
        }

    }
    
    for (vector <ExprTreeNode*> e:P){
    }

    return root;
}




void Parser::parse(vector<string> code){
    vector <string> v = code;
    
    string l = code[0];
    string f = code[1];
    if (l=="del"){
        
        ExprTreeNode* lv = new ExprTreeNode();
        lv->type = "DEL";
        ExprTreeNode* o = new ExprTreeNode();
        o->type = "DEL";
        o->left = lv;
        string right = code[2];
        ExprTreeNode* r = new ExprTreeNode();
        r->type = "VAR";
        r->id = right;
        o->right = r;
        expr_trees.push_back(o);
        last_deleted = symtable->search(right);
        symtable->remove(right);
        
    }

    else if (l == "ret"){
        v.erase(v.begin());
        v.erase(v.begin());
        ExprTreeNode* lv = new ExprTreeNode();
        lv->type = "RET";
        ExprTreeNode* o = new ExprTreeNode();
        o->type = "RET";
        o->left = lv;
        o->right = buildtree(v);
        expr_trees.push_back(o);
        
    }
    
    else{
        v.erase(v.begin());
        v.erase(v.begin());
        ExprTreeNode* lv = new ExprTreeNode();
        lv->id = l;
        lv->type = "VAR";
        ExprTreeNode* o = new ExprTreeNode();
        o->type = "VAR";
        o->left = lv;
        o->right = buildtree(v);
        expr_trees.push_back(o);
        symtable->insert(l);
    }
    

}

Parser::~Parser(){
    for (int i =0; i<expr_trees.size();i++){
        delete expr_trees[i];
    }
}



// int main(){

//     Parser *p=new Parser();
//     vector<string> input;

//     while(true){
//         bool inpu=true;
//         bool end=false;
//         while(inpu){
//             string x;
//             cin>>x;
//             if(x=="!"){
//                 break;
//             }
//             else if(x=="?"){
//                 end=true;
//                 break;
//             }
//             else{
//                 input.push_back(x);
//             }

//         }
//         if(end){
//             //p.parse(input);
//             break;
//         }
//         p->parse(input);
//         input.clear();
        
//     }

    

//     for(int i=0;i<p->expr_trees.size();i++){
//         cout<<"now showing " <<p->expr_trees[i]->left->id<<endl;
//         pot(p->expr_trees[i]);
//         cout<<endl;

//     }
    

//     delete p;
    
//     return 0;

// }


