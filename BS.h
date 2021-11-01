#pragma once
#include "AC.h"
using namespace std;


template <class T1, class T2>
class BS : public AC<T1, T2>
{
protected:
    virtual void hook_new_node(typename AC<T1, T2>::Node*& _node)
    {
        _node = new typename AC<T1, T2>::Node;
    }
    virtual void hook_balance_insert(stack<typename AC<T1, T2>::Node**>& nodes) {}
    virtual void hook_balance_rem(stack<typename AC<T1, T2>::Node**>& nodes) {}
    virtual void hook_find_splay(stack<typename AC<T1, T2>::Node**>& nodes) {}
    virtual bool hook_check(typename AC<T1, T2>::Node*& node) { return true; };
    virtual void hook_change_rb(typename AC<T1, T2>::Node**& node) { };
    virtual void hook_remove(stack<typename AC<T1, T2>::Node**>& st, typename AC<T1, T2>::Node**& current)
    {
        if ((*current)->left and (*current)->right) {
            typename AC<T1, T2>::Node** minNode = &(*current)->right;
            hook_push(st, minNode);
            while ((*minNode)->left) {
                minNode = &(*minNode)->left;
                hook_push(st, minNode);
            }
            swap((*current)->key, (*minNode)->key);
            swap((*current)->value, (*minNode)->value);
            current = minNode;
        }

        bool hook_bool = hook_check(*current);

        if ((*current)->left == nullptr and (*current)->right == nullptr) {
            delete* current;
            *current = nullptr;
            if (this->root == nullptr)
                hook_bool = false;
        }
        else {
            if ((*current)->left == nullptr) {
                typename AC<T1, T2>::Node* tmp = *current;
                *current = (*current)->right;
                delete tmp;
            }
            else {
                typename AC<T1, T2>::Node* tmp = *current;
                *current = (*current)->left;
                delete tmp;
            }
            if (!hook_check(*current))
            {
                hook_change_rb(current);
                hook_bool = false;
            }
        }

        if (hook_bool)
            hook_balance_rem(st);
    }
    void hook_find_and_completed_stack(stack<typename AC<T1, T2>::Node**>& nodes, typename AC<T1, T2>::Node**& current, T1 key)
    {
        int comparator_result;
        hook_push(nodes, current);
        while (*current != nullptr)
        {
            comparator_result = this->comparator->compare((*current)->key, key);
            if (comparator_result == 0)
            {
                return;
            }
            if (comparator_result == 1)
            {
                current = &(*current)->left;
            }
            else
            {
                current = &(*current)->right;
            }
            hook_push(nodes, current);
        }
        return;
    }
    virtual void hook_push(stack<typename AC<T1, T2>::Node**>& nodes, typename AC<T1, T2>::Node** node) {} // push to stack
    
    //rotate
    void rotateright(AC<T1, T2>::Node*& p)
    {
        typename AC<T1, T2>::Node* q = p->left;
        p->left = q->right;
        q->right = p;
        p = q;
    }
    void rotateleft(AC<T1, T2>::Node*& q)
    {
        typename AC<T1, T2>::Node* p = q->right;
        q->right = p->left;
        p->left = q;
        q = p;
    }

    //method
    virtual typename AC<T1, T2>::Node* insert(const T1& key, const T2& value, typename AC<T1, T2>::Node*& _root)
    {
        stack<typename AC<T1, T2>::Node**> st;
        typename AC<T1, T2>::Node** current = &_root;
        hook_find_and_completed_stack(st, current, key);
        
        if (*current != nullptr)
            throw TreeException("INSERT ERROR: element already exists");

        this->hook_new_node(*current);
        (*current)->key = key;
        (*current)->value = value;

        hook_balance_insert(st);
        hook_find_splay(st);
        return this->root;
    }
    virtual typename AC<T1, T2>::Node* find(const T1& key, typename AC<T1, T2>::Node*& _root)
    {
        stack<typename AC<T1, T2>::Node**> st;
        typename AC<T1, T2>::Node** current = &_root;
        hook_find_and_completed_stack(st, current, key);
        if (*current == nullptr)
            throw TreeException("KEY ERROR: key for find not found");
        hook_find_splay(st);
        return *current;
    }
    virtual typename AC<T1, T2>::Node* remove(const T1& key, typename AC<T1, T2>::Node*& _root)
    {
        stack<typename AC<T1, T2>::Node**> st;
        typename AC<T1, T2>::Node** current = &_root;
        hook_find_and_completed_stack(st, current, key);

        if (*current == nullptr)
            throw TreeException("KEY ERROR: key for remove not found");

        hook_remove(st, current);
        return *current;
    }

    //init
    void rec_del(typename AC<T1, T2>::Node* node)
    {
        if (node == nullptr) {
            return;
        }
        if (node->left != nullptr) {
            rec_del(node->left);
        }
        if (node->right != nullptr) {
            rec_del(node->right);
        }
        delete node;
    }
    void rec_copy(const typename AC<T1, T2>::Node* node)
    {
        if (node == nullptr) {
            return;
        }
        AC<T1, T2>::insert(node->key, node->value);
        rec_copy(node->left);
        rec_copy(node->right);
    }

public:
    //init
    BS(const Ñompare <T1>* _comparator) : AC<T1, T2>(_comparator) {}
    virtual ~BS()
    {
        rec_del(this->root);
    }
    BS(const AC<T1, T2>& _tree)
    {
        this->root = nullptr;
        this->comparator = _tree.get_compare();
        rec_copy(_tree.get_root());
    }
    BS<T1, T2>& operator= (const AC<T1, T2>& tree)
    {
        if (this->root != nullptr) {
            rec_del(this->root);
            this->root = nullptr;
        }
        this->comparator = tree.get_compare();
        rec_copy(tree.get_root());
        return *this;
    }
};
