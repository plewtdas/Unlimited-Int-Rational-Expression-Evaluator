/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #include "entry.cpp"
#include "symtable.h"
// using namespace std;
// #include <iostream>
// #include "ulimitedint.cpp"
// #include "ulimitedrational.cpp"

// #include "ulimitedrational.cpp"

SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}

void deete(SymEntry* node){
    if (node!=nullptr){
        if (node->left!=nullptr){
            delete(node->left);
        }
        if (node->right!=nullptr){
            delete (node->right);
        }
        delete node;
        node=nullptr;
    }
}

SymbolTable::~SymbolTable() {
    deete(root);
    size=0;

}

SymEntry *helperinsert(string k, UnlimitedRational *v, SymEntry *node, SymEntry *root)
{
    if (node == nullptr)
    {
        // cout<<"enter"<<endl;
        SymEntry *s = new SymEntry;

        s->key = k;

        s->val = v;
        node = s;
        return node;
    }
    else
    {
        if (k > node->key)
        {
            // cout<<"enter 1"<<endl;
            if (node->right == nullptr)
            {
                SymEntry *s = new SymEntry;

                s->key = k;
                s->val = v;
                node->right = s;
            }
            else
            {
                helperinsert(k, v, node->right, root);
            }
        }
        else
        {
            // cout<<"enter 2"<<endl;
            if (node->left == nullptr)
            {
                SymEntry *s = new SymEntry;

                s->key = k;
                s->val = v;
                node->left = s;
            }
            else
            {
                helperinsert(k, v, node->left, root);
            }
        }
        return root;
    }
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    size++;
    SymEntry *Node = root;
    root = helperinsert(k, v, Node, root);
}

SymEntry *helperremove(SymEntry *root, string k)
{

    if (root->key < k)
    {
        if (root->right == nullptr)
        {
            // cout<<"hi";
            return root;
        }
        else
        {
            root->right = helperremove(root->right, k);
        }
        return root;
    }
    else if (root->key > k)
    {
        if (root->left == nullptr)
        {
            return root;
        }
        else
        {
            root->left = helperremove(root->left, k);
        }
        return root;
    }

    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            return root;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
            return root;
        }
        else if (root->left == nullptr)
        {
            root = root->right;
            return root;
        }

        else
        {
            SymEntry *Node = root;
            Node=Node->right;
            while (Node->left != nullptr)
            {
                Node = Node->left;
            }
            root->key = Node->key;
            root->val = Node->val;
            Node->key=k;
            root->right = helperremove(root->right, k);
            return root;
        }
    }
    return root;
}

void SymbolTable::remove(string k)
{
    size--;
    root = helperremove(root, k);
}

UnlimitedRational *SymbolTable::search(string k)
{
    UnlimitedInt *a=new UnlimitedInt(0);
    UnlimitedInt *b=new UnlimitedInt(0);
    UnlimitedRational *p=new UnlimitedRational(a,b);
    bool found = false;
    SymEntry *Node = root;
    while (!found)
    {
        // cout<<"hi";
        if (Node==nullptr){
            found=false;
            break;
        }
        if (Node->key == k)
        {
            found = true;
            p = Node->val;
            break;
        }
        else
        {
            if (Node->key > k)
            {
                Node = Node->left;
            }
            else
            {
                Node = Node->right;
            }
        }
    }
    // cout<<"gotout";
    // cout<<p->get_frac_str()<<endl;
    string s1=p->get_p_str();
    string s2=p->get_q_str();
    UnlimitedInt* p1=new UnlimitedInt(s1);
    UnlimitedInt* p2=new UnlimitedInt(s2);
    UnlimitedRational * p3=new UnlimitedRational(p1,p2);
    return p3;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}

// void print(SymEntry* node){
//     if (node!=nullptr){
//         print(node->left);
//         cout<<node->key<<" ";
//         print(node->right);
//     }
// }
// int main()
// {
//     SymbolTable *st = new SymbolTable;
//     UnlimitedInt t(9);
//     UnlimitedInt y(2);
//     UnlimitedInt f(2);
//     UnlimitedInt h(2);
//     UnlimitedRational d(&f, &y);
//     UnlimitedRational v(&t, &h);
//     st->insert("hello", &v);

//     st->insert("d", &v);
//     st->insert("hs", &v);
//     st->insert("hg", &v);
// //     // st->remove("d");
//     // UnlimitedRational *p= st->search("hsdhfbo");
//     // cout<<p->get_frac_str()<<endl;
// //     // cout<<1234567<<endl;
//     st->insert("z", &d);
// //     // cout<<1234567<<endl;
//     st->insert("a", &d);
// //     // cout<<1234567<<endl;
//     st->insert("e", &d);
//     st->insert("hell",&d);
//     // SymEntry *root=st->get_root();
//     // print(root);

// //     // st->remove("hs");
// //     // st->remove("hg");
// //     // cout << "hs removed";
//     // st->remove("e");
// //     st->remove("hs");
//     UnlimitedRational *p= st->search("hell");
// //     // cout<<"pagal";
//     cout<<p->get_frac_str()<<endl;

// //     cout << st->get_size() << endl;
// //     cout << "out";
// }