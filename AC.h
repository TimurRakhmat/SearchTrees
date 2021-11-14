#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Compare.h"
#include <stack>
using namespace std;

template <class T1, class T2>
class AC
{
protected:
    class Node
    {
    public:
        T1 key;
        T2 value;
        Node* left;
        Node* right;

        Node(Node* _left = nullptr, Node* _right = nullptr)
        {
            left = _left;
            right = _right;
        }
        virtual ~Node() {
        }
    };
public:
    class TreeException : public exception
    {
    private:
        string error_text;
    public:
        T1 key;

    public:
        TreeException(const string& _error_text, const T1& _key) {
            error_text = _error_text;
            key = _key;
        }
        const char* what() const noexcept {
            return error_text.c_str();
        }
    };

protected:
    Node* root = nullptr;
    const Ñompare <T1>* comparator;

    //pass
    virtual void infix(void (*function) (const T1&, const T2&, int), Node* p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        infix(function, p_node->left, depth + 1);
        function(p_node->key, p_node->value, depth);
        infix(function, p_node->right, depth + 1);
    }
    virtual void postfix(void (*function) (const T1&, const T2&, int), Node* p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        postfix(function, p_node->left, depth + 1);
        postfix(function, p_node->right, depth + 1);
        function(p_node->key, p_node->value, depth);
    }
    virtual void prefix(void (*function) (const T1&, const T2&, int), Node* p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        function(p_node->key, p_node->value, depth);
        prefix(function, p_node->left, depth + 1);
        prefix(function, p_node->right, depth + 1);
    }

    //method
    virtual Node* insert(const T1& key, const T2& value, Node*& _root) = 0;
    virtual Node* find(const T1& key, Node*& _root) = 0;
    virtual Node* remove(const T1& key, Node*& _root) = 0;

    virtual void rec_del(typename AC<T1, T2>::Node* node) = 0;

public:
    //init mega
    virtual void rec_copy_self_decorator(AC<T1, T2>& _tree) const = 0;

public:
    //method_decorater
    T2& find(const T1& key)
    {
        return find(key, root)->value;
    }
    void insert(const T1& key, const T2& value)
    {
        insert(key, value, root);
    }
    void remove(const T1& key)
    {
        remove(key, root);
    }

    //method fot init
    const Node* get_root() const
    {
        return root;
    }
    const Ñompare<T1>* get_compare() const
    {
        return comparator;
    }

    //pass_decorater
    void prefix_pass(void (*function) (const T1&, const T2&, int))
    {
        prefix(function, root, 0);
    }
    void postfix_pass(void (*function) (const T1&, const T2&, int))
    {
        postfix(function, root, 0);
    }
    void infix_pass(void (*function) (const T1&, const T2&, int))
    {
        infix(function, root, 0);
    }

public:
    //init
    AC(const Ñompare <T1>* _comparator)
    {
        comparator = _comparator;
        root = nullptr;
    }
    AC(const AC<T1, T2>& _tree) {};

    AC<T1, T2>& operator= (const AC<T1, T2>& _tree)
    {
        if (this->root != nullptr) {
            rec_del(this->root);
            this->root = nullptr;
        }
        _tree.rec_copy_self_decorator(*this);
        return *this;
    }

    virtual ~AC() {}
};
