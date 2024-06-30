/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line



EPPCompiler::EPPCompiler(){
    memory_size = 0;
    Parser targ();
    
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
    Parser targ();
    vector <int> v;
    for (int i=memory_size-1;i>=0;i--){
        v.push_back(i);
    }
    mem_loc = v;
}

void EPPCompiler::compile(vector<vector<string>> code){
    for (vector <string> v : code){
        
        string t = v[0];
        if (t == "del"){
            targ.parse(v);
            mem_loc.push_back(targ.last_deleted);
            
        }

        else if (t == "ret"){
            targ.parse(v);
        }
        else{
            string key = t;
            
            if (targ.symtable->search(key) != -2){
                targ.parse(v);
            }
            else{ 
                targ.parse(v);
                int index = mem_loc[mem_loc.size()-1];
                mem_loc.pop_back();
                targ.symtable->assign_address(key,index);
            }
        }

        vector <string> command = generate_targ_commands();
        write_to_file(command);


    }
}


void cc(ExprTreeNode* root,vector <string> & command,SymbolTable* S){
    if (root->type == "ADD"){
        cc(root->right,command,S);
        cc(root->left,command,S);
        command.push_back("ADD"); 
    }

    else if (root->type == "SUB"){
        cc(root->right,command,S);
        cc(root->left,command,S);
        command.push_back("SUB");
    }

    else if (root->type == "MUL"){
        cc(root->right,command,S);
        cc(root->left,command,S);
        command.push_back("MUL");
    }

    else if (root->type == "DIV"){
        cc(root->right,command,S);
        cc(root->left,command,S);
        command.push_back("DIV");
    }

    else if (root->type == "VAL"){
        string s = "PUSH " + to_string(root->num);
        command.push_back(s);
    }

    else if (root->type == "VAR"){
        
        string key = root->id;
        int index = S->search(key);
        string s = "PUSH mem[" + to_string(index) + "]";
        command.push_back(s);
    }

}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* N = targ.expr_trees[targ.expr_trees.size()-1];
    vector <string> command;
    if (N->type == "DEL"){
        int index = targ.last_deleted;
        string s = "DEL = mem[" + to_string(index) + "]";
        command.push_back(s);
    }

    else if (N->type == "RET"){
        cc(N->right,command,targ.symtable);
        command.push_back("RET = POP");
    }

    else{
        cc(N->right,command,targ.symtable);
        string key = N->left->id;
        int index = targ.symtable->search(key);
        string s = "mem[" + to_string(index) + "] = POP";
        command.push_back(s);
    }

    return command;
    
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream o_file;
    o_file.open(output_file,ios::app);
    if (o_file.is_open()){
        for (string s : commands){
            o_file<<s<<endl;
        }
        o_file.close();
    }
}

EPPCompiler::~EPPCompiler(){

}

