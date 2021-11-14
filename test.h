#pragma once
#include "BS.h"
#include "AVL.h"
#include "RB.h"
#include "B23.h"
#include "Splay.h"
#include <string>

#include "Relation.h"
#include <map>
#include <set>
#include <vector>

class Departament
{
public:
	int count = 0;
	string name = "";
	int salary = 0;
	int floor = 0;
	string address = "";
	int work_time = 0;

const int get_salary() const
{
	return salary;
}

Departament(int _count, string _name, int _salary, int _floor, string _address, int _work_time) :
	count(_count), name(_name), salary(_salary), floor(_floor), address(_address), work_time(_work_time) {}
};

class SalaryCmp : public Ñompare<Departament*>
{
	int compare(Departament* const& d1, Departament* const & d2) const
	{
		if (d1->get_salary() > d2->get_salary())
			return 1;
		if (d2->get_salary() > d1->get_salary())
			return -1;
		return 0;
	}
};
class CountCmp : public Ñompare<Departament*>
{
	int compare(Departament* const& d1, Departament* const & d2) const
	{
		if (d1->count > d2->count)
			return 1;
		if (d2->count > d1->count)
			return -1;
		return 0;
	}
};
class NameCmp : public Ñompare<Departament*>
{
	int compare( Departament* const& d1,  Departament*const& d2) const
	{
		if (d1->name > d2->name)
			return 1;
		if (d2->name > d1->name)
			return -1;
		return 0;
	}
};
class CountAndSalaryCmp : public Ñompare<Departament*>
{
	int compare( Departament*const& d1,  Departament*const& d2) const
	{
		if (d1->count == d2->count and d1->salary == d2->salary)
			return 0;
		if (d1->count > d2->count)
			return 1;
		else
			return -1;
		if (d1->salary > d2->salary)
			return 1;

		return -1;
	}
};
class NameAndAddressAndCountCmp: public Ñompare<Departament*>
{
	int compare( Departament* const& d1,  Departament* const& d2) const
	{
		if (d1->name == d2->name and d1->count == d2->count\
			and d1->address == d2->address)
			return 0;
		if (d1->name > d2->name)
			return 1;
		else
			return -1;
		if (d1->count > d2->count)
			return 1;
		else
			return -1;
		if (d1->address > d2->address)
			return 1;

		return -1;
	}
};
class ALLCmp : public Ñompare<Departament*>
{
	int compare( Departament* const& d1,  Departament* const& d2) const
	{
		if (d1->name == d2->name and d1->count == d2->count and d1->salary == d2->salary and d1->floor == d2->floor\
			and d1->address == d2->address and d1->work_time == d2->work_time)
			return 0;
		if (d1->name > d2->name)
			return 1;
		else
			return -1;
		if (d1->count > d2->count)
			return 1;
		else
			return -1;
		if (d1->salary > d2->salary)
			return 1;
		else
			return -1;
		if (d1->floor > d2->floor)
			return 1;
		else
			return -1;
		if (d1->address > d2->address)
			return 1;
		else
			return -1;
		if (d1->work_time > d2->work_time)
			return 1;
		
		return -1;
	}
};


void test_rb();
void test_avl();
void test_bs();
void test_splay();
void test_splay2();
void test_rb2();
void test_rb1();
void test_rb_mull();
void test_b23();