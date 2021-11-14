#pragma once
#include <cmath>
#include <string>

using namespace std;

template <typename T>
class Ñompare
{
public:
	virtual ~Ñompare() {}
	virtual int compare(const T& left, const T& right) const = 0;
};

class PointCompare : public Ñompare<string> // does not work
{
public:
	PointCompare() {}
	int compare(const string& left, const string& right) const {
		if (left > right)
			return 1;
		if (right > left)
			return -1;
		return 0;
	}
	/*int compare(const char* left, const char* right) const {
		if (*left > *right)
			return 1;
		if (*right > *left)
			return -1;
		return 0;
	}
	int compare(const char*& left, const char*& right) const {
		if (*left > *right)
			return 1;
		if (*right > *left)
			return -1;
		return 0;
	}*/
};

class IntCompare : public Ñompare<int>
{
public:
	IntCompare() {}
	int compare(const int& left, const int& right) const {
		if (left > right)
			return 1;
		if (right > left)
			return -1;
		return 0;
	}
};

class charCompare : public Ñompare<char>
{
public:
	charCompare() {}
	int compare(const char& left, const char& right) const {
		if (left > right)
			return 1;
		if (right > left)
			return -1;
		return 0;
	}
};

class DoubleCompare1 : public Ñompare<double>
{
public:
	DoubleCompare1() {}
	int compare(const double& left, const double& right) const;
};

class IntAbsCompare : public Ñompare <int> {
public:
	IntAbsCompare() {}
	int compare(const int& left, const int& right) const;
};

class StrCompare1 : public Ñompare<string>
{
public:
	StrCompare1() {}
	int compare(const string& left, const string& right) const;
};

class StrCompare2 : public Ñompare<string>
{
public:
	StrCompare2() {}
	int compare(const string& left, const string& right) const;
};
