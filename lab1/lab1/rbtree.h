#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

enum Color
{
    black,
    red
};

class rbtree
{
    class Node
    {
    public:
        Node(bool is_red, int Key, char Value)
        {
            if (is_red)
                color = red;
            else
                color = black;
            key = Key;
            value = Value;
            parent = nullptr;
            right = nullptr;
            left = nullptr;
        }
        Color color;
        int key;
        char value;
        Node* parent;
        Node* right;
        Node* left;
    };

    Node* root;

    class dftIterator       //deep-first-search iterator
    {
        class Stack
        {
            struct Elem
            {
                Node* inf;
                Elem* next;
            };

            Elem* head;

        public:

            Stack() { head = nullptr; }

            void push(Node* In)
            {
                Elem* Insert = new Elem;
                Insert->inf = In;
                Insert->next = head;
                head = Insert;
            }

            Node* pop()
            {
                if (!head)
                    return nullptr;
                Node* ans = head->inf;
                Elem* Del = head;
                head = head->next;
                delete Del;
                return ans;
            }

            ~Stack()
            {
                while (head)
                    pop();
            }
        };

        Node* cur;
        Stack* s;

    public:

        dftIterator(Node* Root)
        {
            cur = Root;
            s = new Stack;
        }

        Node* next()
        {
            if (!cur)
                return nullptr;
            if (cur->right)
                s->push(cur->right);
            Node* ans = cur;
            if (cur->left)
                cur = cur->left;
            else
                cur = s->pop();
            return ans;
        }

        ~dftIterator() { delete s; }
    };

    void rotate_l(Node* pivot)
    {
        Node* P = pivot->parent;
        Node* GP = P->parent;
        Node* leftC = pivot->left;
        pivot->parent = GP;
        if (GP)
        {
            if (GP->left == P)
                GP->left = pivot;
            else
                GP->right = pivot;
        }
        else
            root = pivot;
        P->parent = pivot;
        pivot->left = P;
        if (leftC)
            leftC->parent = P;
        P->right = leftC;
    }

    void rotate_r(Node* pivot)
    {
        Node* P = pivot->parent;
        Node* GP = P->parent;
        Node* rightC = pivot->right;
        pivot->parent = GP;
        if (GP)
        {
            if (GP->left == P)
                GP->left = pivot;
            else
                GP->right = pivot;
        }
        else
            root = pivot;
        P->parent = pivot;
        pivot->right = P;
        if (rightC)
            rightC->parent = P;
        P->left = rightC;
    }


    void fix_insertion(Node* newNode)   //tree rebalancing after insertion
    {
        Node* P = newNode->parent;
        if (!P)
        {
            newNode->color = black;
            root = newNode;
            return;
        }
        if (P->color == black)
            return;

        Node* GP = P->parent;
        Node* U;
        if (GP->right == P)
            U = GP->left;
        else
            U = GP->right;

        Color U_col;
        if (!U)
            U_col = black;
        else
            U_col = U->color;


        if (U_col == red)
        {
            GP->color = red;
            P->color = black;
            U->color = black;
            fix_insertion(GP);
        }
        else
        {
            if (P->right == newNode)
            {
                if (GP->left == P)
                {
                    rotate_l(newNode);
                    rotate_r(newNode);
                    newNode->color = black;
                    GP->color = red;
                }
                else
                {
                    rotate_l(P);
                    P->color = black;
                    GP->color = red;
                }
            }
            else
            {
                if (GP->right == P)
                {
                    rotate_r(newNode);
                    rotate_l(newNode);
                    newNode->color = black;
                    GP->color = red;
                }
                else
                {
                    rotate_r(P);
                    P->color = black;
                    GP->color = red;
                }
            }
        }
    }

    //tree rebalancing in case of deleting black node
    void fix_deleting(Node* pivot, bool mode) //bool mode shows if pivot may be the root
    {
        Node* P = pivot->parent; //parent of pivot

        if (mode && !P) //deleting case 3.1 (pivot is new root)
        {
            root = pivot;
            return;
        }

        Node* S; //sibling of pivot
        if (P->left == pivot)
            S = P->right;
        else
            S = P->left;
        Node* Sl = S->left; //left child of S
        Node* Sr = S->right; //right child of S

        //getting colors of Sl and Sr
        Color Sl_col, Sr_col;
        if (!Sl)
            Sl_col = black;
        else
            (Sl_col = Sl->color);
        if (!Sr)
            Sr_col = black;
        else
            (Sr_col = Sr->color);


        if (S->color == red) //deleting case 3.2 (P is black and S is red)
        {
            if (P->left == pivot)
                rotate_l(S);
            else
                rotate_r(S);
            S->color = black;
            P->color = red;
            fix_deleting(pivot, 0); //leads to cases 3.4-6
        }
        else if (P->color == black && Sr_col == black && Sl_col == black) //delting case 3.3 (P, S, Sl and Sr are black)
        {
            S->color = red;
            fix_deleting(P, 1); //leads to cases 3.1-6
        }
        else if (P->color == red && Sr_col == black && Sl_col == black) //deleting case 3.4 (P is red; S, Sr and Sl are black)
        {
            P->color = black;
            S->color = red;
        }
        else if (P->left == pivot && Sr_col == black) //deleting case 3.5.1 (S and Sr are black, Sl is red, pivot is left)
        {
            rotate_r(Sl);
            Sl->color = black;
            S->color = red;
            fix_deleting(pivot, 0); //leads to case 3.6.2
        }
        else if (P->left == pivot && Sr_col == red) //deleting case 3.6.1 (S is black, Sr is red, pivot is left)
        {
            rotate_l(S);
            S->color = P->color;
            P->color = black;
            Sr->color = black;
        }
        else if (P->right == pivot && Sl_col == black) //deleting case 3.5.2 (S and Sl are black, Sr is red, pivot is right)
        {
            rotate_l(Sr);
            Sr->color = black;
            S->color = red;
            fix_deleting(pivot, 0); //leads to case 3.6.2
        }
        else if (P->right == pivot && Sl_col == red) //deleting case 3.6.2 (S is black, Sl is red, pivot is right)
        {
            rotate_r(S);
            S->color = P->color;
            P->color = black;
            Sl->color = black;
        }
    }

    //deleting node
    void deleting(Node* delNode)
    {
        if (delNode->color == red) //case 1
        {
            if (delNode->parent->right == delNode)
                delNode->parent->right = nullptr;
            else
                delNode->parent->left = nullptr;
            delete delNode;
        }
        else if (delNode->left || delNode->right) //case 2
        {
            Node* child;
            if (delNode->left)
                child = delNode->left;
            else
                child = delNode->right;
            child->parent = delNode->parent;
            child->color = black;

            if (!child->parent)
                root = child;
            else
            {
                if (delNode->parent->right == delNode)
                    delNode->parent->right = child;
                else
                    delNode->parent->left = child;
            }
            delete delNode;
        }
        else if (delNode == root) //case 3.1
        {
            root = nullptr;
            delete delNode;
        }
        else
        {
            fix_deleting(delNode, 0); //other cases
            if (delNode->parent->left == delNode)
                delNode->parent->left = nullptr;
            else
                delNode->parent->right = nullptr;
            delete delNode;
        }
    }

    //returns node with min key from subtree
    Node* getMin(Node* cur)
    {
        while (cur->left)
            cur = cur->left;
        return cur;
    }

    //returns node by its' key
    Node* getNode(int k, Node* cur)
    {
        if (!cur)
            return nullptr;
        if (cur->key == k)
            return cur;
        if (cur->key < k)
            return getNode(k, cur->right);
        if (cur->key > k)
            return getNode(k, cur->left);
    }

    //searching for place and inserts node
    Node* insert_rec(int IncludeKey, char IncludeValue, Node* Parent)
    {
        if (IncludeKey == Parent->key)
            throw invalid_argument("");
        if (IncludeKey > Parent->key)
        {
            if (!Parent->right)
            {
                Parent->right = new Node(1, IncludeKey, IncludeValue);
                Parent->right->parent = Parent;
                return Parent->right;
            }
            else
                return insert_rec(IncludeKey, IncludeValue, Parent->right);
        }
        else
        {
            if (!Parent->left)
            {
                Parent->left = new Node(1, IncludeKey, IncludeValue);
                Parent->left->parent = Parent;
                return Parent->left;
            }
            else
                return insert_rec(IncludeKey, IncludeValue, Parent->left);
        }
    }

public:

    rbtree() { root = nullptr; }

    //inserts node
    void insert(int Key, char Value)
    {
        if (!root)
            root = new Node(0, Key, Value);
        else
        {
            Node* newNode;
            try { newNode = insert_rec(Key, Value, root); }
            catch (exception& exception) { throw invalid_argument("Element with such key has been already included\n"); }
            fix_insertion(newNode);
        }
    }

    //removes node by its' key
    void remove(int Key)
    {
        if (!root)
            throw runtime_error("Tree is empty\n");
        Node* delNode = getNode(Key, root);
        if (!delNode)
            throw runtime_error("Node isn't exist\n");

        if (delNode->left && delNode->right)
        {
            Node* temp = delNode;
            delNode = getMin(delNode->right);
            temp->key = delNode->key;
            temp->value = delNode->value;
        }
        deleting(delNode);
    }

    //returns node's value by its' key
    char find(int Key)
    {
        if (!root)
            throw runtime_error("Tree is empty\n");
        Node* ans = getNode(Key, root);
        if (!ans)
            throw runtime_error("Node isn't exist\n");
        return ans->value;
    }

    void clear()
    {
        while (root)
            remove(root->key);
    }

    string get_keys()
    {
        if (!root)
            throw runtime_error("Tree is empty\n");
        string ans;
        dftIterator* Iterator = new dftIterator(root);
        Node* Cur = Iterator->next();
        while (Cur)
        {
            ans += to_string(Cur->key);
            ans += ' ';
            Cur = Iterator->next();
        }
        delete Iterator;
        return ans;
    }

    string get_values()
    {
        if (!root)
            throw runtime_error("Tree is empty\n");
        string ans;
        dftIterator* Iterator = new dftIterator(root);
        Node* Cur = Iterator->next();
        while (Cur)
        {
            ans += Cur->value;
            ans += ' ';
            Cur = Iterator->next();
        }
        delete Iterator;
        return ans;
    }

    void print()
    {
        if (!root)
            throw runtime_error("Tree is empty\n");
        dftIterator* Iterator = new dftIterator(root);
        Node* Cur = Iterator->next();
        while (Cur)
        {
            cout << Cur->key << ' ' << Cur->value << endl;
            Cur = Iterator->next();
        }
        delete Iterator;
    }

    ~rbtree()
    {
        clear();
    }
};

#endif
