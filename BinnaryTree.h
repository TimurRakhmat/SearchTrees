#pragma once
#include "TreeException.h"
#include "Compare.h"
using namespace std;

template <class T1, class T2>
class BinaryTree
{
public:
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
        ~Node() {
        }
    };

private:
    Node* root;
    const Ñompare <T1>* comparator;

private:
    void insert(const T1& key, const T2& value)
    {
        Node* parent = nullptr;
        Node* current = root;
        bool right;
        int comparator_result = 0;

        while (current != nullptr)
        {
            comparator_result = comparator->compare(current->key, key);
            if (comparator_result == 0)
            {
                throw TreeException("INSERT ERROR: element already exists");
            }
            if (comparator_result == 1)
            {
                parent = current;
                current = current->left;
                right = false;
                continue;
            }
            if (comparator_result == -1)
            {
                parent = current;
                current = current->right;
                right = true;
                continue;
            }
        }

        if (parent == nullptr) {
            root = new Node;
            root->key = key;
            root->value = value;
        }
        else {
            if (right)
            {
                parent->right = new Node;
                parent->right->key = key;
                parent->right->value = value;
            }
            else
            {
                parent->left = new Node;
                parent->left->key = key;
                parent->left->value = value;
            }
        }
        return;
    }

    Node* find(const T1& key) const
    {
        Node* current = root;
        while (current != nullptr)
        {
            int comparator_result = comparator->compare(current->key, key);
            if (comparator_result == 0)
            {
                return current;
            }
            if (comparator_result == 1)
            {
                current = current->left;
                continue;
            }
            if (comparator_result == -1)
            {
                current = current->right;
                continue;
            }
        }
        throw TreeException("KEY ERROR: key for find not found");
    }

    void remove(const T1& key)
    {
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr)
        {
            int comparator_result = comparator->compare(current->key, key);
            if (comparator_result == 0)
            {
                break;
            }
            if (comparator_result == 1)
            {
                parent = current;
                current = current->left;
                continue;
            }
            if (comparator_result == -1)
            {
                parent = current;
                current = current->right;
                continue;
            }
        }
        if (current == nullptr) {
            throw TreeException("KEY ERROR: key for remove not found");
        }


        if (current->left == nullptr and current->right == nullptr)
        {
            if (parent == nullptr) {
                root = nullptr;
            }
            else {
                if (parent->left == current) {
                    parent->left = nullptr;
                }
                if (parent->right == current) {
                    parent->right = nullptr;
                }
            }
            delete current;
        }
        else if (current->left == nullptr or current->right == nullptr)
        {
            if (parent == nullptr) {
                if (current->left == nullptr) {
                    root = root->right;
                }
                else {
                    root = root->left;
                }
            }
            else {
                if (current->left == nullptr)
                {
                    if (parent->left == current) {
                        parent->left = current->right;
                    }
                    else {
                        parent->right = current->right;
                    }
                }
                else {
                    if (parent->left == current) {
                        parent->left = current->left;
                    }
                    else {
                        parent->right = current->left;
                    }
                }
            }
            delete current;
        }
        else {
            Node* next = current->right;
            Node* next_parent = current;
            while (next->left != nullptr) {
                next_parent = next;
                next = next->left;
            }
            if (next_parent != current) {
                next_parent->left = nullptr;
            }

            current->key = next->key;
            current->value = next->value;
            remove(next->key);

            delete current;
        }
    }

    void remove1(const T1& key)
    {
        if (target->left && target->right) {
            Node* localMax = findMaxNode(target->left);
            target->data = localMax->data;
            removeNodeByPtr(localMax);
            return;
        }
        else if (target->left) {
            if (target == target->parent->left) {
                target->parent->left = target->left;
            }
            else {
                target->parent->right = target->left;
            }
        }
        else if (target->right) {
            if (target == target->parent->right) {
                target->parent->right = target->right;
            }
            else {
                target->parent->left = target->right;
            }
        }
        else {
            if (target == target->parent->left) {
                target->parent->left = nullptr;
            }
            else {
                target->parent->right = nullptr;
            }
        }
        delete target;
    }

    void replace(const T1& key, const T2& value)
    {
        Node* current = find(key);
        current->value = value;
    }

    void recursiv_delete(Node* TreePtr)
    {
        if (TreePtr == nullptr) {
            return;
        }
        if (TreePtr->left != nullptr) {
            recursiv_delete(TreePtr->left);
        }
        if (TreePtr->right != nullptr) {
            recursiv_delete(TreePtr->right);
        }
        delete TreePtr;
    }

    void prefix_pass(void (*function) (const T1&, const T2&, int), Node *p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        function(p_node->key, p_node->value, depth);
        prefix_pass(function, p_node->left, depth + 1);
        prefix_pass(function, p_node->right, depth + 1);
    }

    void infix_pass(void (*function) (const T1&, const T2&, int), Node* p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        infix_pass(function, p_node->left, depth + 1);
        function(p_node->key, p_node->value, depth);
        infix_pass(function, p_node->right, depth + 1);
    }

    void postfix_pass(void (*function) (const T1&, const T2&, int), Node* p_node, int depth)
    {
        if (p_node == nullptr) {
            return;
        }
        postfix_pass(function, p_node->left, depth + 1);
        postfix_pass(function, p_node->right, depth + 1);
        function(p_node->key, p_node->value, depth);
    }

    void recursiv_copy(const Node* p_node)
    {
        if (p_node == nullptr) {
            return;
        }
        insert(p_node->key, p_node->value);
        recursiv_copy(p_node->left);
        recursiv_copy(p_node->right);
    }

public:
    BinaryTree(const Ñompare <T1>* _comparator)
    {
        comparator = _comparator;
        root = nullptr;
    }

    ~BinaryTree()
    {
        recursiv_delete(root);
    }

    BinaryTree(const BinaryTree<T1, T2>& _tree)
    {
        root = nullptr;
        comparator = _tree.comparator;
        recursiv_copy(_tree.root);
    }

    void operator+=(const Node& node)
    {
        insert(node.key, node.value);
    }

    void operator*=(const Node& node)
    {
        replace(node.key, node.value);
    }

    void operator-=(const T1& key)
    {
        remove(key);
    }

    T2 operator[](const T1& key) const
    {
        return (find(key))->value;
    }

    BinaryTree<T1, T2>& operator=(const BinaryTree<T1, T2>& _tree)
    {
        if (root != nullptr) {
            recursiv_delete(root);
            root = nullptr;
        }
        comparator = _tree.comparator;
        recursiv_copy(_tree.root);
        return *this;
    }

    void prefix(void (*function) (const T1&, const T2&, int))
    {
        prefix_pass(function, &root, 0);
    }

    void postfix(void (*function) (const T1&, const T2&, int))
    {
        postfix_pass(function, &root, 0);
    }

    void infix(void (*function) (const T1&, const T2&, int))
    {
        infix_pass(function, &root, 0);
    }
};
