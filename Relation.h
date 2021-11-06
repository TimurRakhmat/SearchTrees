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
	string doCorrectIndex(const string& index);
public:
	bool isCorrectIdentifier(const string& index);
	enum TREE { BST, AVLT, SPLAYT, RBT, B23T };
	class Exception : public exception
	{
	private:
		string error_text;
	public:
		Exception(const string& _error_text) {
			error_text = _error_text;
		}

		const char* what() const noexcept override {
			return error_text.c_str();
		}
	};

	/*struct IndexBuilder
	{
	private:
		vector<string> identifiers;
	public:
		IndexBuilder() = default;
		IndexBuilder& newIdentifier(std::string identifier)
		{
			if (not Relation<TKey, TValue>::isCorrectIdentifier(identifier))
				throw Exception("Index has not correct identifier\n");
			identifiers.push_back(identifier);
			return *this;
		}
		std::string		getResult()
		{
			string	res;
			sort(identifiers.begin(), identifiers.end());
			for (auto elem : identifiers)
				res += elem;
			return res;
		}
	};*/
	Relation<TKey, TValue>& addIndex(TREE type, const Ñompare<TKey>* comp, const string& index);
	Relation<TKey, TValue>& removeIndex(const std::string& index);
	Relation<TKey, TValue>& insert(const TKey& key, TValue & value);
	Relation<TKey, TValue>& remove(const TKey& data);
	TValue& find(const TKey& key, const string& index);
};

string strip(const string& line)
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

template <class TKey, class TValue>
string Relation<TKey, TValue>::doCorrectIndex(const string& index)
{
	string res = index;

	vector <string> vec;
	auto i = res.find(",");
	while (i != string::npos)
	{
		vec.push_back(strip(res.substr(0, i)));
		if (!isCorrectIdentifier(vec[vec.size() - 1]))
			throw Exception("Index has not correct identifier\n");
		res = res.substr(i + 1);
		i = res.find(",");
	}
	if (!isCorrectIdentifier(res))
		throw Exception("Index has not correct identifier\n");
	vec.push_back(res);
	res = "";
	std::sort(vec.begin(), vec.end());
	for (auto str : vec)
		res += str;
	return (res);
}

template <class TKey, class TValue>
bool Relation<TKey, TValue>::isCorrectIdentifier(const string& identifier)
{
	int len = identifier.length();
	if (len > 32 or len == 0)
		return false;
	if (!isalpha(identifier[0]))
		return false;
	for (int i = 0; i < len; i++)
	{
		if (!isalnum(identifier[i]))
			return false;
	}
	return true;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::addIndex(typename Relation<TKey, TValue>::TREE type,
	const Ñompare<TKey>* comp, const string& index)
{
	string correctIndex = doCorrectIndex(index);
	if (this->dict.find(correctIndex) != this->dict.end())
		throw Exception("Index already exists\n");
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
	string correctIndex = doCorrectIndex(index);
	if (dict.find(correctIndex) == dict.end())
		throw Exception("Index not found\n");
	this->dict.erase(correctIndex);
	return *this;
}

template <class TKey, class TValue>
Relation<TKey, TValue>& Relation<TKey, TValue>::insert(const TKey& key, TValue& value)
{
	if (this->dict.empty())
		throw Exception("Insert index before inserting data\n");
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
	return this->dict[doCorrectIndex(index)]->find(key);
}
