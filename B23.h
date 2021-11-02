#pragma once
#include"AC.h"

using namespace std;

template<class T1, class T2>
class B23 : public AC<T1, T2>
{
public:
	//init
	class NodeA : public AC<T1, T2>::Node
	{
	public:
		T1 keyR;
		T2 valueR;
		AC<T1, T2>::Node* middle = nullptr;
		NodeA() :AC<T1, T2>::Node() {}
	};

	B23(const Ñompare<T1>* _comparator) : AC<T1, T2>(_comparator) {	}
	B23(const AC<T1, T2>& _tree) : AC<T1, T2>(_tree) {}
	B23<T1, T2>& operator= (B23<T1, T2>& tree)
	{
		if (this->root != nullptr) {
			rec_del(this->root);
			this->root = nullptr;
		}
		this->comparator = tree.get_compare();
		rec_copy(tree.get_root());
		return *this;
	}

protected:
	//pass
	void infix(void (*function) (const T1&, const T2&, int), typename AC<T1, T2>::Node* p_node, int depth)
	{
		if (p_node == nullptr) {
			return;
		}
		infix(function, p_node->left, depth + 1);
		function(p_node->key, p_node->value, depth);
		if (get_middle(p_node) != p_node)
		{
			infix(function, get_middle(p_node), depth + 1);
			function(getKR(p_node), getVR(p_node), depth);
		}
		infix(function, p_node->right, depth + 1);
	}
	void postfix(void (*function) (const T1&, const T2&, int), typename AC<T1, T2>::Node* p_node, int depth)
	{
		if (p_node == nullptr) {
			return;
		}
		postfix(function, p_node->left, depth + 1);
		postfix(function, p_node->right, depth + 1);
		if (get_middle(p_node) != p_node)
		{
			postfix(function, get_middle(p_node), depth + 1);
			function(getKR(p_node), getVR(p_node), depth + 1);
		}
		function(p_node->key, p_node->value, depth);
	}
	void prefix(void (*function) (const T1&, const T2&, int), typename AC<T1, T2>::Node* p_node, int depth)
	{
		if (p_node == nullptr) {
			return;
		}
		function(p_node->key, p_node->value, depth);
		if (get_middle(p_node) != p_node)
		{
			function(getKR(p_node), getVR(p_node), depth + 1);
			prefix(function, get_middle(p_node), depth + 1);
		}
		prefix(function, p_node->left, depth + 1);
		prefix(function, p_node->right, depth + 1);
	}

	// node_methods
	AC<T1, T2>::Node*& get_middle(typename AC<T1, T2>::Node* node)
	{
		typename AC<T1, T2>::Node** tmp = &static_cast<NodeA*>(node)->middle;
		return *tmp;
	}
	AC<T1, T2>::Node*& get_middle_const(const typename AC<T1, T2>::Node* node)
	{
		typename AC<T1, T2>::Node* tmpc = const_cast<typename AC<T1, T2>::Node*>(node);
		return static_cast<NodeA*>(tmpc)->middle;
	}

	T1& getKR(typename AC<T1, T2>::Node* node)
	{
		return static_cast<NodeA*>(node)->keyR;
	}
	T2& getVR(typename AC<T1, T2>::Node* node)
	{
		return static_cast<NodeA*>(node)->valueR;
	}

	T1& getKRC(const typename AC<T1, T2>::Node* node)
	{
		typename AC<T1, T2>::Node* tmpc = const_cast<typename AC<T1, T2>::Node*>(node);
		return static_cast<NodeA*>(tmpc)->keyR;
	}
	T2& getVRC(const typename AC<T1, T2>::Node* node)
	{
		typename AC<T1, T2>::Node* tmpc = const_cast<typename AC<T1, T2>::Node*>(node);
		return static_cast<NodeA*>(tmpc)->valueR;
	}


	// insert into node
	void increase_node(typename AC<T1, T2>::Node* leftnode, typename AC<T1, T2>::Node* rightnode)
	{
		if (this->comparator->compare(leftnode->key, rightnode->key) == 1) // case x from left
		{
			getKR(leftnode) = leftnode->key;
			getVR(leftnode) = leftnode->value;
			leftnode->key   = rightnode->key;
			leftnode->value = rightnode->value;

			leftnode->left = rightnode->left;
			get_middle(leftnode) = rightnode->right;
		}
		else                                                // case x from right
		{
			getKR(leftnode) = rightnode->key;
			getVR(leftnode) = rightnode->value;

			leftnode->right = rightnode->right;
			get_middle(leftnode) = rightnode->left;
		}
	}
	AC<T1, T2>::Node*& insert_into_double_node(AC<T1, T2>::Node*& p, AC<T1, T2>::Node* x)
	{
		typename AC<T1, T2>::Node* temp;
		hook_new_node(temp);
		if (this->comparator->compare(p->key, x->key) == 1) // case x from left, push node l to up
		{
			temp->key = p->key;
			temp->value = p->value;
			temp->left = x;
			temp->right = p;

			p->left = get_middle(p);
			get_middle(p) = p;
			x = temp->left;
			get_middle(x) = x;
			get_middle(temp) = temp;
			return temp;
		}

		if (this->comparator->compare(getKR(p), x->key) == -1) // case x from right, push node r to up
		{
			temp->key = getKR(p);
			temp->value = getVR(p);
			temp->left = p;
			temp->right = x;


			p->right = get_middle(p);
			get_middle(p) = p;
			x = temp->right;
			get_middle(x) = x;

			get_middle(temp) = temp;
			return temp;
		}

		x->left = p;           // case x from middle, push node x to up
		x->right = temp;
		get_middle(x) = x;
		temp->key = getKR(p);
		temp->value = getVR(p);
		get_middle(temp) = temp;
		temp->left = x->right;
		temp->right = p->right;
		p->right = x->left;
		get_middle(p) = p;
		return x;
	}

	void hook_new_node(typename AC<T1, T2>::Node*& _node) {
		_node = new NodeA;
	}
	void hook_push(stack<typename AC<T1, T2>::Node**>& nodes,
		typename AC<T1, T2>::Node** node) {
		nodes.push(node);
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
				if (!(get_middle(*current) == *current))
					comparator_result = this->comparator->compare(getKR(*current), key);
				
				if (comparator_result == 0)
				{
					return;
				}
				if (comparator_result == -1)
					current = &(*current)->right;
				else
					current = &(get_middle(*current));
			}
			hook_push(nodes, current);
		}
		return;
	}

	//methods
	void hook_balance_insert(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		typename AC<T1, T2>::Node** p;
		typename AC<T1, T2>::Node** temp;
		typename AC<T1, T2>::Node** x = nodes.top();
		nodes.pop();

		while (!nodes.empty())
		{
			p = nodes.top();
			nodes.pop();

			if (get_middle(*p) == *p)
			{
				get_middle(*p) = nullptr;
				increase_node(*p, *x);
				delete* x;
				*x = nullptr;
				return;
			}
			else
			{
				temp = &insert_into_double_node(*p, *x);
				x = temp;
			}
		}

		get_middle(*x) = *x;
		this->root = *x;
		return;
	}
	void hook_balance_rem(stack<typename AC<T1, T2>::Node**>& nodes)
	{
		typename AC<T1, T2>::Node** g;
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
		}
		return;
	}

	//methods
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
		return this->root;
	}
	virtual typename AC<T1, T2>::Node* find(const T1& key, typename AC<T1, T2>::Node*& _root)
	{
		stack<typename AC<T1, T2>::Node**> st;
		typename AC<T1, T2>::Node** current = &_root;
		hook_find_and_completed_stack(st, current, key);
		if (*current == nullptr)
			throw TreeException("KEY ERROR: key for find not found");
		return *current;
	}
	virtual typename AC<T1, T2>::Node* remove(const T1& key, typename AC<T1, T2>::Node*& _root)
	{
		stack<typename AC<T1, T2>::Node**> st;
		typename AC<T1, T2>::Node** current = &_root;
		hook_find_and_completed_stack(st, current, key);

		if (*current == nullptr)
			throw TreeException("KEY ERROR: key for remove not found");

		//hook_remove(st, current);
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
		if (get_middle(node) != node and get_middle(node) != nullptr)
		{
			rec_del(get_middle(node));
		}
		if (node->right != nullptr) {
			rec_del(node->right);
		}
		delete node;
	}
	void rec_copy(const typename AC<T1, T2>::Node* node) //typename B23<T1, T2>::NodeA* node
	{
		if (node == nullptr) {
			return;
		}
		AC<T1, T2>::insert(node->key, node->value);
		if (!(get_middle_const(node) == node))
		{
			AC<T1, T2>::insert(getKRC(node), getVRC(node));
		}
		rec_copy(static_cast<NodeA*>(node->left));
		if (!(get_middle_const(node) == node))
		{
			rec_copy(static_cast<NodeA* > (get_middle_const(node)));
		}
		rec_copy(static_cast<NodeA*>(node->right));
	}
};
