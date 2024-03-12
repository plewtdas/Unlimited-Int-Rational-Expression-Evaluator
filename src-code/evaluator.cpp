/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
// using namespace std;
// #include <iostream>
Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    delete symtable;
    int n=expr_trees.size();
    while (n){
        ExprTreeNode * node=expr_trees[n-1];
        while (node!=nullptr){
            if (node->left!=nullptr){
                delete node->left;
                node->left=nullptr;
            }
            if (node->right!=nullptr){
                delete node->right;
                node->right=nullptr;
            }
            delete node;
            node=nullptr;
        }
        n-=1;
    }
}

string signcheck(char c)
{

    if (int(c) == 37)
    {
        return "MOD";
    }
    else if (int(c) == 40)
    {
        return "OPENINGBRACKET";
    }
    else if (int(c) == 41)
    {
        return "CLOSINGBRACKET";
    }
    else if (int(c) == 42)
    {
        return "MUL";
    }
    else if (int(c) == 43)
    {
        return "ADD";
    }
    else if (int(c) == 45)
    {
        return "SUB";
    }
    else if (int(c) == 47)
    {

        return "DIV";
    }
    else
    {
        return "VAR";
    }
}

ExprTreeNode *recurparse(vector<string> code, int startindex, int endindex)
{
    if (startindex < endindex)
    {
        if (47 < int(code[startindex + 1][0]) and int(code[startindex + 1][0]) < 58) // means its a number ahead;
        {
            // cout<<"f"<<code[startindex+1];
            UnlimitedInt *num = new UnlimitedInt(code[startindex + 1]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            ExprTreeNode *signnode = new ExprTreeNode;
            numnode->id = code[startindex + 1];
            signnode->type = signcheck(code[startindex + 2][0]);
            signnode->left = numnode;
            signnode->id = code[startindex + 2];
            // cout<<signnode->id<<endl;
            // cout<<"start "<<startindex<<"end "<<endindex<<endl;
            signnode->right = recurparse(code, startindex + 3, endindex - 1);
            // cout<<"enter"<<endl;
            return signnode;
        }
        else 
        // if (code[startindex+1]=="(")
        { // means its a bracket ahead;
            int countbracket = 0;
            int indexcheck = 0;
            for (int j = startindex + 1; j < endindex; j++)
            {
                if (int(code[j][0]) == 40)
                {
                    countbracket += 1;
                }
                else if (int(code[j][0]) == 41)
                {
                    countbracket -= 1;
                }
                if (countbracket == 0)
                {
                    indexcheck = j;
                    break;
                }
            }
            ExprTreeNode *signnode = new ExprTreeNode;
            signnode->type = signcheck(code[indexcheck + 1][0]);
            signnode->left = recurparse(code, startindex + 1, indexcheck);
            signnode->right = recurparse(code, indexcheck + 2, endindex - 1);
            signnode->id = code[indexcheck + 1];
            return signnode;
        }
        // else{
        //     //a variable at startindex+1;
        //     ExprTreeNode *signnode = new ExprTreeNode;
        //     signnode->type = signcheck(code[startindex + 2][0]);
        //     signnode->id = code[startindex + 2];

        //     ExprTreeNode *variable = new ExprTreeNode();
        //     variable->type = "VAR";
        //     variable->id = code[startindex+1];

        //     signnode->left=variable;
        //     signnode->right=recurparse(code,startindex+3,endindex-1);

        // }
    }
    else if (startindex > endindex)
    {
        return nullptr;
    }
    else
    {

        // cout<<"jho";
        // cout<<5;
        // cout<<startindex+1;
        // int a=int(code[startindex + 1][0]);
        // cout<<a;
        if (47 < int(code[startindex ][0]) and int(code[startindex][0]) < 58) // means its a number ahead;
        {
            // cout<<"ko";
            UnlimitedInt *num = new UnlimitedInt(code[startindex]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            numnode->id = code[startindex];
            return numnode;
        }
        else
        {
            // cout<<"here"<<endl;
            ExprTreeNode *variable = new ExprTreeNode();
            variable->type = "VAR";
            variable->id = code[startindex];
            // cout<<variable->id;
            return variable;
        }
    }
}

void Evaluator::parse(vector<string> code)
{
    ExprTreeNode *main = new ExprTreeNode();
    main->type = "equalto";
    main->id = code[1];

    ExprTreeNode *leftmain = new ExprTreeNode();
    main->left = leftmain;
    leftmain->type = "VAR";
    leftmain->id = code[0];
    
    int startindex = 2;
    int size = code.size();
    int endindex = size - 1;

    if (code[2] != "(")
    {
        // cout<<"hi";

        if (47 < int(code[2][0]) and int(code[2][0]) < 58) // means its a number ahead;
        {
            // cout<<"ko";
            UnlimitedInt *num = new UnlimitedInt(code[2]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            numnode->id = code[2];
            main->right = numnode;
            // return numnode;
        }
        else
        {
            // cout<<"here";
            ExprTreeNode *variable = new ExprTreeNode();
            variable->type = "VAR";
            variable->id = code[2];
            main->right = variable;
            // return variable;
        }
        expr_trees.push_back(main);
    }
    else
    {
        main->right = recurparse(code, startindex, endindex);
        expr_trees.push_back(main);
    }
}

UnlimitedRational *calculator(SymbolTable *symtable, ExprTreeNode *root)
{
    if (root->right != nullptr or root->left != nullptr)
    {
        // cout<<"enter";
        string rootid = root->id;
        char s = rootid[0];
        // cout<<s;
        UnlimitedRational *num1 = calculator(symtable, root->left);
        UnlimitedRational *num2 = calculator(symtable, root->right);
        // cout<<endl;
        // cout<<num1->get_frac_str()<<" "<<num2->get_frac_str()<<endl;
        
        UnlimitedRational *value;
        if (int(s) == 37)
        {
            // mod asuming a,b are int type divided by 1;
            UnlimitedInt *p1 = num1->get_p();
            UnlimitedInt *p2 = num2->get_p();
            UnlimitedInt *modd = UnlimitedInt::mod(p1, p2);
            delete p1;
            delete p2;
            UnlimitedInt *one = new UnlimitedInt(1);
            UnlimitedRational *ans = new UnlimitedRational(modd, one);
            value= ans;
        }
        else if (int(s) == 42)
        {
            value= UnlimitedRational::mul(num1, num2);
        }
        else if (int(s) == 43)
        {

            value= UnlimitedRational::add(num1, num2);
        }
        else if (int(s) == 45)
        {
            value= UnlimitedRational::sub(num1, num2);
        }
        else
        {
            value= UnlimitedRational::div(num1, num2);
        }
        root->evaluated_value = value;
        return value;
    }
    else
    {
        if (root->type != "VAR")
        {
            // UnlimitedRational * vall=new UnlimitedRational();
            UnlimitedInt * p1=new UnlimitedInt (root->evaluated_value->get_p_str());
            UnlimitedInt * p2=new UnlimitedInt (root->evaluated_value->get_q_str());
            UnlimitedRational *retval= new UnlimitedRational(p1,p2);
            return retval;
        }
        else
        {
            // UnlimitedRational * vall=new UnlimitedRational();
            UnlimitedInt * p1=new UnlimitedInt (symtable->search(root->id)->get_p_str());
            UnlimitedInt * p2=new UnlimitedInt (symtable->search(root->id)->get_q_str());
            UnlimitedRational *retval= new UnlimitedRational(p1,p2);
            return retval;
        }
    }
}

void Evaluator::eval()
{
    int lastelement = expr_trees.size() - 1;
    ExprTreeNode *lastnode = expr_trees[lastelement];
    ExprTreeNode *rightnode = lastnode->right;
    // cout<<rightnode->id;
    UnlimitedRational *rational = calculator(symtable, rightnode);//calculating value of right subtree
    // cout<<rational->get_frac_str();
    lastnode->evaluated_value = rational;
    string idd = lastnode->left->id; //will be a variable
    symtable->insert(idd, rational);
}

// void print(ExprTreeNode* node){
//     if (node!=nullptr){
//         print(node->left);
//         cout<<node->id<<" ";
//         print(node->right);
//     }
// }

// int main(){
//     vector<string> arr={"e", ":=", "(", "(","a", "*", "c", ")", "+","(","(", "b","*","d", ")", "*","4",")",")"};
//     Evaluator* ev=new Evaluator();
//     ev->parse(arr);
//     ev->eval();
//     ExprTreeNode* node=ev->expr_trees[0];
//     print(node);
//     // cout<<" fh" <<node->right->right->right->type;
// //     print(node);
//     cout<<"over";
// }