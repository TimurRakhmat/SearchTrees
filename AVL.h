#pragma once
#include"BS.h"

using namespace std;

template<class T1, class T2>
class AVL : public BS<T1, T2>
{
protected:
	//init
	class NodeA : public BS<T1, T2>::Node
	{
	public:
		int h = 0;
		NodeA() :BS<T1, T2>::Node() {}
	};
public:
	AVL(const Ñompare<T1>* _comparator) : BS<T1, T2>(_comparator) {	}
	AVL(const AC<T1, T2>& _tree) : BS<T1, T2>(_tree) {}

	void rec_copy_self_decorator(AC<T1, T2>& _tree) const
	{
		AC<T1, T2>* tmp = &_tree;
		this->rec_copy_self(this->root, tmp);
	}

protected:
	void hook_new_node(typename BS<T1, T2>::Node*& _node) {
		_node =  new NodeA;
	}
	void hook_push(stack<typename BS<T1, T2>::Node**>& nodes,
		typename BS<T1, T2>::Node** node) {
		nodes.push(node);
	}
	int height(typename BS<T1, T2>::Node* _node)
	{
		int hei = (_node ? static_cast<NodeA*>(_node)->h : -1);
		return hei;
	}
	void set_height(typename BS<T1, T2>::Node* _node)
	{
		if (_node)
			static_cast<NodeA*>(_node)->h = max(height(_node->left), height(_node->right)) + 1;
	}
	int get_delta(typename BS<T1, T2>::Node* _node)
	{
		if(_node)
			return height(_node->right) - height(_node->left);
		return 0;
	}

	//methods
	void hook_balance_insert(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		while (!nodes.empty()) {
			typename BS<T1, T2>::Node** node = nodes.top();
			set_height(*node);
			int delta = get_delta(*node);
			if (delta == 2)
			{
				if (get_delta((*node)->right) < 0)
				{
					this->rotateright((*node)->right);
					set_height((*node)->right->right);
					set_height((*node)->right);
				}
				this->rotateleft(*node);
				set_height((*node)->left);
				set_height(*node);
			}
			if (delta == -2)
			{
				if (get_delta((*node)->left) > 0)
				{
					this->rotateleft((*node)->left);
					set_height((*node)->left->left);
					set_height((*node)->left);
				}
				this->rotateright(*node);
				set_height((*node)->right);
				set_height(*node);
			}
			nodes.pop();
		}
		return;
	}
	void hook_balance_rem(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		nodes.pop();
		while (!nodes.empty()) {
			typename BS<T1, T2>::Node** node = nodes.top();
			set_height(*node);
			int delta = get_delta(*node);
			// add delta
			if (delta > 1)
			{
				if (get_delta((*node)->right) < 0) {
					this->rotateright((*node)->right);
					set_height((*node)->right->right);
					set_height((*node)->right);
				}
				this->rotateleft(*node);
				set_height((*node)->left);
				set_height(*node);
			}
			if (delta < -1)
			{
				if (get_delta((*node)->right) > 0) {
					this->rotateleft((*node)->left);
					set_height((*node)->left->left);
					set_height((*node)->left);
				}
				this->rotateright(*node);
				set_height((*node)->right);
				set_height(*node);
			}
			nodes.pop();
		}
	}
};
