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

	//delete from node
	void redistribute(AC<T1, T2>::Node*& p, AC<T1, T2>::Node*& x)
	{
		//case delete from single node
		if (get_middle(p) == p)
		{
			typename AC<T1, T2>::Node** d;
			if (p->right == x) // x from right
			{
				d = &p->left;
				x->key = p->key;
				x->value = p->value;
				p->key = getKR(*d);
				p->value = getVR(*d);
				x->left = (*d)->right;
				(*d)->right = get_middle(*d);
				get_middle(*d) = *d;
			}
			else // x from left
			{
				d = &p->right;
				x->key = p->key;
				x->value = p->value;

				p->key   = (*d)->key;
				p->value = (*d)->value;

				(*d)->key = getKR(*d);
				(*d)->value = getVR(*d);

				x->left = x->right;
				x->right = (*d)->left;
				(*d)->left = get_middle(*d);
				get_middle(*d) = *d;
			}
			return;
		}

		typename AC<T1, T2>::Node** d;
		typename AC<T1, T2>::Node** tmp;
		//case x from left
		if (p->left == x)
		{
			if (get_middle(get_middle(p)) != get_middle(p)) //case double middle node
			{
				d = &get_middle(p);
				x->key   = p->key;
				x->value = p->value;

				p->key   = (*d)->key;
				p->value = (*d)->value;
				(*d)->key   = getKR(*d);
				(*d)->value = getVR(*d);

				x->left = x->right;
				x->right = (*d)->left;
				(*d)->left = get_middle(*d);
				get_middle(*d) = *d;

				return;
			}

			// case  double right node
			d = &get_middle(p);
			tmp = &p->right;

			x->left = x->right;
			x->right = (*d)->left;
			x->key = p->key;
			x->value = p->value;

			p->key = (*d)->key;
			p->value = (*d)->value;

			(*d)->left = (*d)->right;
			(*d)->right = (*tmp)->left;
			(*d)->key   = getKR(p);
			(*d)->value = getVR(p);

			getKR(p) = (*tmp)->key;
			getVR(p) = (*tmp)->value;

			(*tmp)->key   = getKR(*tmp);
			(*tmp)->value = getVR(*tmp);
			(*tmp)->left = get_middle(*tmp);
			get_middle(*tmp) = *tmp;
			
			return;
		}

		//case x from right
		if (p->right == x)
		{
			if (get_middle(get_middle(p)) != get_middle(p)) //case double middle node
			{
				d = &get_middle(p);
				x->key   = getKR(p);
				x->value = getVR(p);

				getKR(p) = getKR(*d);
				getVR(p) = getVR(*d);

				x->left = (*d)->right;
				(*d)->right = get_middle(*d);
				get_middle(*d) = *d;

				return;
			}

			//case double left node
			d = &get_middle(p);
			tmp = &p->left;

			x->left = (*d)->right;
			x->key = getKR(p);
			x->value = getVR(p);

			getKR(p) = (*d)->key;
			getVR(p) = (*d)->value;

			(*d)->right = (*d)->left;
			(*d)->left = (*tmp)->right;
			(*d)->key = p->key;
			(*d)->value = p->value;

			p->key   = getKR(*tmp);
			p->value = getVR(*tmp);

			(*tmp)->right = get_middle(*tmp);
			get_middle(*tmp) = *tmp;

			return;
		}

		//case x from middle
		//case double right node
		if (get_middle(p->right) != p->right)
		{
			d = &p->right;
			x->key = getKR(p);
			x->value = getVR(p);
			x->left = x->right;
			x->right = (*d)->left;

			getKR(p) = (*d)->key;
			getVR(p) = (*d)->value;

			(*d)->key = getKR(*d);
			(*d)->value = getVR(*d);
			(*d)->left = get_middle(*d);
			get_middle(*d) = *d;
			return;
		}
		
		// case double left node
		d = &p->left;
		x->key = p->key;
		x->value = p->value;
		x->left = (*d)->right;

		p->key = getKR(*d);
		p->value = getVR(*d);

		(*d)->right = get_middle(*d);
		get_middle(*d) = *d;
		return;
	}
	void fix(AC<T1, T2>::Node*& p, AC<T1, T2>::Node* x)
	{
		typename AC<T1, T2>::Node** d;
		//case x from left
		if (p->left == x)
		{
			d = &get_middle(p);
			getKR(*d) = (*d)->key;
			getVR(*d) = (*d)->value;
			(*d)->key = p->key;
			(*d)->value = p->value;
			get_middle(*d) = (*d)->left;
			(*d)->left = x->right;

			p->key = getKR(p);
			p->value = getVR(p);
			p->left = get_middle(p);
			get_middle(p) = p;

			delete x;
			x = nullptr;
			return;
		}

		//case x from right
		if (p->right == x)
		{
			d = &get_middle(p);
			getKR(*d) = getKR(p);
			getVR(*d) = getVR(p);
			get_middle(*d) = (*d)->right;
			(*d)->right = x->right;

			p->right = get_middle(p);
			get_middle(p) = p;

			delete x;
			x = nullptr;
			return;
		}

		//case x from middle
		d = &p->right;
		getKR(*d) = (*d)->key;
		getVR(*d) = (*d)->value;
		(*d)->key = getKR(p);
		(*d)->value = getVR(p);
		get_middle(*d) = (*d)->left;
		(*d)->left = x->right;

		get_middle(p) = p;

		delete x;
		x = nullptr;
		return;
	}
	void merge(AC<T1, T2>::Node*& p, AC<T1, T2>::Node* x)
	{
		typename AC<T1, T2>::Node** d;
		//case x from left
		if (p->left == x)
		{
			d = &p->right;
			getKR(*d) = (*d)->key;
			getVR(*d) = (*d)->value;

			get_middle(*d) = (*d)->left;
			(*d)->left = x->right;

			(*d)->key = p->key;
			(*d)->value = p->value;

			delete x;
			x = nullptr;
			return;
		}
		
		//case x from right
		d = &p->left;
		getKR(*d) = p->key;
		getVR(*d) = p->value;

		get_middle(*d) = (*d)->right;
		(*d)->right = x->right;

		delete x;
		x = nullptr;

		p->right = p->left;
		p->left = nullptr;
		return;
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
	void hook_remove(stack<typename AC<T1, T2>::Node**>& st, typename AC<T1, T2>::Node**& current, const T1& key)
	{
		// find right node
		if ((*current)->left and (*current)->right) {
			typename AC<T1, T2>::Node** minNode;
			if (this->comparator->compare((*current)->key, key) == 0 and get_middle(*current) != *current)
					minNode = &get_middle(*current);
			else
				minNode = &(*current)->right;
			hook_push(st, minNode);
			while ((*minNode)->left) {
				minNode = &(*minNode)->left;
				hook_push(st, minNode);
			}
			if (get_middle(*current) == *current or (*current)->key == key)
			{
				swap((*current)->key, (*minNode)->key);
				swap((*current)->value, (*minNode)->value);
			}
			else
			{
				swap(getKR(*current), (*minNode)->key);
				swap(getVR(*current), (*minNode)->value);
			}
			current = minNode;
		}

		// case double node
		if (get_middle(*current) != *current)
		{
			if ((*current)->key == key)
			{
				(*current)->key = getKR(*current);
				(*current)->value = getVR(*current);
			}
			get_middle(*current) = *current;
			return;
		}

		// case delete root
		if (st.size() == 1)
		{
			delete* current;
			*current = nullptr;
			return;
		}

		//other cases
		st.pop();
		typename AC<T1, T2>::Node** p;
		while (!st.empty())
		{
			p = st.top();
			st.pop();

			//case redistribute
			if (get_middle((*p)->left) != (*p)->left or get_middle((*p)->right) != (*p)->right\
				or get_middle(get_middle(*p)) != get_middle(*p))
			{
				redistribute(*p, *current);
				return;
			}

			// case double node parent
			if (get_middle(*p) != *p)
			{
				fix(*p, *current);
				return;
			}

			merge(*p, *current);
			current = p;
		}

		typename AC<T1, T2>::Node* tmp = (*current)->right;
		delete* current;
		*current = nullptr;
		this->root = tmp;
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

		hook_remove(st, current, key);
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
