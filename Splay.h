#pragma once
#include<iostream>
#include"BS.h"

using namespace std;

template<class T1, class T2>
class Splay : public BS<T1, T2>
{
public:
	Splay(const Ñompare<T1>* _comparator) : BS<T1, T2>(_comparator) {	}
	Splay(const AC<T1, T2>& _tree) : BS<T1, T2>(_tree) {}

	void rec_copy_self_decorator(AC<T1, T2>& _tree) const
	{
		AC<T1, T2>* tmp = &_tree;
		this->rec_copy_self(this->root, tmp);
	}

protected:
	void hook_push(stack<typename BS<T1, T2>::Node**>& nodes,
		typename BS<T1, T2>::Node** node) {
		nodes.push(node);
	}

	void splay(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		typename AC<T1, T2>::Node** g;
		typename AC<T1, T2>::Node** p;
		typename AC<T1, T2>::Node** x;
		if (nodes.size() > 0)
		{
			x = nodes.top();
			nodes.pop();
			while (nodes.size() > 1)
			{
				p = nodes.top();
				nodes.pop();
				g = nodes.top();
				nodes.pop();
				if ((*g)->left == *p and (*p)->left == *x) // zig-zig
				{
					this->rotateright(*g);
					this->rotateright(*g);
				}
				else if ((*g)->right == *p and (*p)->right == *x)
				{
					this->rotateleft(*g);
					this->rotateleft(*g);
				}
				else if ((*g)->right == *p and (*p)->left == *x) // zig-zag
				{
					this->rotateright((*g)->right);
					this->rotateleft(*g);
				}
				else if ((*g)->left == *p and (*p)->right == *x)
				{
					this->rotateleft((*g)->left);
					this->rotateright(*g);
				}
				x = g;
			}

			if (nodes.size() == 1) // zig
			{
				p = nodes.top();
				nodes.pop();
				if ((*p)->left == *x)
				{
					this->rotateright(*p);
				}
				else {
					this->rotateleft(*p);
				};
				x = p;
			};
		}
		
		return;
	}

	AC<T1, T2>::Node* merge(AC<T1, T2>::Node*& ln, AC<T1, T2>::Node*& rn)
	{
		stack<typename AC<T1, T2>::Node**> st;
		typename AC<T1, T2>::Node** tmp = &ln;
		while (*tmp != nullptr)
		{
			hook_push(st, tmp);
			tmp = &(*tmp)->right;
		}
		splay(st);
		if (ln != nullptr)
		{
			ln->right = rn;
			return ln;
		}
		else
			return rn;
	}

	void hook_remove(stack<typename AC<T1, T2>::Node**>& st, typename AC<T1, T2>::Node**& current)
	{
		splay(st);
		typename AC<T1, T2>::Node* tmp = this->root;
		this->root = merge(this->root->left, this->root->right);
		delete tmp;
	}

	void hook_find_splay(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		splay(nodes);
	}
};
