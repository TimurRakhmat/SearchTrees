#pragma once

#include <algorithm>
#include <map>
#include <vector>
#include "Compare.h"

#include"B23.h"
#include"AVL.h"
#include"RB.h"
#include"Splay.h"
#include"BS.h"

template <class TKey, class TValue>
class Relation
{
private:
	map <string, AC<TKey, TValue>*> dict;

	class Builder {
		vector<string> cIndex;
		bool isCorrectIndex(const string& index);
		string my_strip(const string& line);
	public:
		void makeIndex(const string& index);
		Builder& addId(const string& index);
		string getIndex();
	};

public:
	enum TREE { BST, AVLT, SPLAYT, RBT, B23T };
	class RealationException : public exception
	{
	private:
		string error_text;
	public:
		RealationException(const string& _error_text) {
			error_text = _error_text;
		}

		const char* what() const noexcept {
			return error_text.c_str();
		}
	};

	Relation<TKey, TValue>& addIndex(TREE type, const Ñompare<TKey>* comp, const string& index);
	Relation<TKey, TValue>& removeIndex(const string& index);
	Relation<TKey, TValue>& insert(const TKey& key, TValue & value);
	Relation<TKey, TValue>& remove(const TKey& data);
	TValue& find(const TKey& key, const string& index);
};

template <class TKey, class TValue>
void Relation<TKey, TValue>::Builder::makeIndex(const string& index)
{
	string cIndexb = index;
	auto i = cIndexb.find(",");
	while (i != string::npos)
	{
		string temp = my_strip(cIndexb.substr(0, i));
		this->addId(temp);
		cIndexb = cIndexb.substr(i + 1);
		i = cIndexb.find(",");
	}
	cIndexb = my_strip(cIndexb);
	this->addId(cIndexb);
}

template<class TKey, class TValue>
typename Relation<TKey, TValue>::Builder& Relation<TKey, TValue>::Builder::addId(const string& index)
{
	if (!isCorrectIndex(index) or std::find(cIndex.begin(), cIndex.end(), index) != cIndex.end())
		throw RealationException("Index has not correct identifier, bad index - " + index);
	cIndex.push_back(index);
	return *this;
}


template <class TKey, class TValue>
bool Relation<TKey, TValue>::Builder::isCorrectIndex(const string& index)
{
	int len = index.length();
	if (len > 32 or len == 0)
		return false;
	if (!isalpha(index[0]))
		return false;
	for (int i = 0; i < len; i++)
	{
		if (!isalnum(index[i]))
			return false;
	}
	return true;
}

template<class TKey, class TValue>
string Relation<TKey, TValue>::Builder::my_strip(const string& line)
{
	int b = 0, end = -1;
	int ln = line.length();
	for (int i = 0; i < ln; i++)
		if (!isspace(line[i]))
		{
			b = i;
			break;
		}
	for (int i = ln - 1; i >= 0; i--)
		if (!isspace(line[i]))
		{
			end = i;
			break;
		}
	return line.substr(b, end - b + 1);
}

template<class TKey, class TValue>
inline string Relation<TKey, TValue>::Builder::getIndex()
{
	string ans = "";
	std::sort(cIndex.begin(), cIndex.end());
	for (auto str : cIndex)
		ans += str;
	return ans;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::addIndex(typename Relation<TKey, TValue>::TREE type,
	const Ñompare<TKey>* comp, const string& index)
{
	Builder b;
	b.makeIndex(index);
	string correctIndex = b.getIndex();
	if (this->dict.find(correctIndex) != this->dict.end())
		throw RealationException("Index already exists, bad index - " + index);
	AC <TKey, TValue>* tree = nullptr;
	if (type == this->BST)
		tree = new BS<TKey, TValue>(comp);
	else if (type == this->AVLT)
		tree = new AVL<TKey, TValue>(comp);
	else if (type == this->SPLAYT)
		tree = new Splay<TKey, TValue>(comp);
	else if (type == this->RBT)
		tree = new RB<TKey, TValue>(comp);
	else if (type == this->B23T)
		tree = new B23<TKey, TValue>(comp);
	if (not dict.empty())
	{
		auto first = dict.begin()->second;
		*tree = *first;
	}
	dict[correctIndex] = tree;
	return *this;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::removeIndex(const string& index)
{
	Builder b;
	b.makeIndex(index);
	string correctIndex = b.getIndex();
	if (dict.find(correctIndex) == dict.end())
		throw RealationException("Index not found, bad index - " + index);
	this->dict.erase(correctIndex);
	return *this;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::insert(const TKey& key, TValue& value)
{
	if (this->dict.empty())
		throw RealationException("Insert index before inserting data\n");
	for (auto it = this->dict.begin(); it != this->dict.end(); it++)
	{
		it->second->insert(key, value);
	}
	return *this;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::remove(const TKey& data)
{
	for (auto it = this->dict.begin(); it != this->dict.end(); it++)
	{
		(it->second)->remove(data);
	}
	return *this;
}

template <class TKey, class TValue>
TValue& Relation<TKey, TValue>::find(const TKey& key, const string& index)
{
	Builder b;
	b.makeIndex(index);
	if (this->dict.find(b.getIndex()) != this->dict.end())
		return this->dict[b.getIndex()]->find(key);
	throw RealationException("Index not found, bad index - " + index);
}
