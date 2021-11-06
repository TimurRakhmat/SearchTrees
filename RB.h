#pragma once
#include"BS.h"

using namespace std;

template<class T1, class T2>
class RB : public BS<T1, T2>
{
public:
	//beautifull_print
	void print_tree(typename BS<T1, T2>::Node* _node, int depth);
	void print_colorfull_tree();

	//init
	class NodeA : public BS<T1, T2>::Node
	{
	public:
		bool black = false;
		NodeA() :BS<T1, T2>::Node() {}
	};
	RB(const Ñompare<T1>* _comparator) : BS<T1, T2>(_comparator) {	}
	RB(const AC<T1, T2>& _tree) : BS<T1, T2>(_tree) {}

	void rec_copy_self_decorator(AC<T1, T2>& _tree) const
	{
		AC<T1, T2>* tmp = &_tree;
		this->rec_copy_self(this->root, tmp);
	}

protected:
	virtual bool hook_check(typename AC<T1, T2>::Node*& node) { 
			return static_cast<NodeA*>(node)->black; }
	void hook_new_node(typename BS<T1, T2>::Node*& _node) {
		_node = new NodeA;
	}
	void hook_push(stack<typename BS<T1, T2>::Node**>& nodes,
		typename BS<T1, T2>::Node** node) {
		nodes.push(node);
	}
	bool get_color(typename BS<T1, T2>::Node* _node)
	{
		return (_node ? static_cast<NodeA*>(_node)->black : true);
	}
	void set_color(typename BS<T1, T2>::Node* _node, bool color = true)
	{
		if (_node)
			static_cast<NodeA*>(_node)->black = color;
	}
	virtual void hook_change_rb(typename AC<T1, T2>::Node**& node)
	{
		set_color(*node);
	};

	//methods
	void hook_balance_insert(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		typename AC<T1, T2>::Node** g;
		typename AC<T1, T2>::Node** p;
		typename AC<T1, T2>::Node** u;
		typename AC<T1, T2>::Node** x = nodes.top();
		nodes.pop();

		if (nodes.empty())
		{
			set_color(*x);
			return;
		}

		p = nodes.top();
		nodes.pop();

		while (*p != this->root) // case 1
		{
			if (get_color(*p)) // case 2
				return;

			g = nodes.top();
			nodes.pop();
			if (*p == (*g)->left)
			{
				u = &(*g)->right;
				if (!get_color(*u)) // case 3
				{
					set_color(*p);
					set_color(*u);
					set_color(*g, false);
					x = g;
					if (!nodes.empty())
					{
						p = nodes.top();
						nodes.pop();
						continue;
					}
					break;
				}

				if ((*p)->right == *x) // case 4
				{
					x = p;
					this->rotateleft(*x);
				}

				set_color(*p); // case 5
				set_color(*g, false);
				this->rotateright(*g);
				break;
			}
			else
			{
				u = &(*g)->left;
				if (!get_color(*u)) // case 3
				{
					set_color(*p);
					set_color(*u);
					set_color(*g, false);
					x = g;
					if (!nodes.empty())
					{
						p = nodes.top();
						nodes.pop();
						continue;
					}
					break;
				}
				
				if ((*p)->left == *x) // case 4
				{
					x = p;
					this->rotateright(*x);
				}

				set_color(*p); // case 5
				set_color(*g, false);
				this->rotateleft(*g);
				break;
			}
		}

		set_color(this->root);
		return;
	}

	void hook_balance_rem(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		typename AC<T1, T2>::Node** p;
		typename AC<T1, T2>::Node** u;
		typename AC<T1, T2>::Node** x = nodes.top();
		nodes.pop();

		if (nodes.empty())
			return;

		p = nodes.top();
		nodes.pop();

		while (*x != this->root) // case 1
		{
			if (*x == (*p)->left)
			{
				u = &(*p)->right;
				if (!get_color(*u)) // case 2
				{
					set_color(*p, false);
					set_color(*u);
					this->rotateleft(*p);
					nodes.push(p);
					p = &(*p)->left;
					u = &(*p)->right;
				}
				if (get_color(*p) and get_color(*u) and get_color((*u)->left) and get_color((*u)->right)) // case 3
				{
					set_color(*u, false);
					x = p;
					if (nodes.empty())
						break;
					p = nodes.top();
					nodes.pop();
					continue;
				}

				if (!get_color(*p) and get_color(*u) and get_color((*u)->left) and get_color((*u)->right)) // case 4
				{
					set_color(*p);
					set_color(*u, false);
					return;
				}

				if (get_color(*u) and !get_color((*u)->left) and get_color((*u)->right)) // case 5
				{
					set_color(*u, false);
					set_color((*u)->left);
					this->rotateright(*u);
				}

				// case 6
				set_color(*u, get_color(*p));
				set_color(*p);

				set_color((*u)->right);
				this->rotateleft(*p);
				return;
			}
			else
			{
				u = &(*p)->left;
				if (!get_color(*u)) // case 2
				{
					set_color(*p, false);
					set_color(*u);
					this->rotateright(*p);
					nodes.push(p);
					p = &(*p)->right;
					u = &(*p)->left;
				}
				if (get_color(*p) and get_color(*u) and get_color((*u)->left) and get_color((*u)->right)) // case 3
				{
					set_color(*u, false);
					x = p;
					if (nodes.empty())
						break;
					p = nodes.top();
					nodes.pop();
					continue;
				}

				if (!get_color(*p) and get_color(*u) and get_color((*u)->left) and get_color((*u)->right)) // case 4
				{
					set_color(*p);
					set_color(*u, false);
					return;
				}

				if (get_color(*u) and !get_color((*u)->right) and get_color((*u)->left)) // case 5
				{
					set_color(*u, false);
					set_color((*u)->right);
					this->rotateleft(*u);
				}

				// case 6
				set_color(*u, get_color(*p));
				set_color(*p);

				set_color((*u)->left);
				this->rotateright(*p);
				return;
			}
		}
		return;
	}

	void print_node(typename BS<T1, T2>::Node* _node, int depth)
	{
		for (int i = 0; i < depth; i++)
			cout << "\t";
		if (static_cast<NodeA*>(_node)->black)
			cout << "B-";
		else
			cout << "R-";
		cout << _node->key << endl;
	}
};

template<class T1, class T2>
inline void RB<T1, T2>::print_colorfull_tree()
{
	print_tree(this->root, 0);
}

template<class T1, class T2>
inline void RB<T1, T2>::print_tree(typename BS<T1, T2>::Node* _node, int depth)
{
	if (_node == nullptr)
		return;
	print_tree(_node->left, depth + 1);
	print_node(_node, depth);
	print_tree(_node->right, depth + 1);
}
