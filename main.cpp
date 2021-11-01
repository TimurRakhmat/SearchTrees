#include<iostream>
#include "BS.h"
#include "AVL.h"
#include "RB.h"
#include "Splay.h"
#include <map>
#include <set>
#include <vector>

using namespace std;

template <class T1, class T2>
void print_tree(const T1& key, const T2& value, int depth) {
    for (int i = 0; i < depth; i++) {
        cout << '\t';
    }
    cout << key << endl;
}
template <class T1, class T2>
void print_nodes(const T1& key, const T2& value, int depth) {
    std::cout << "key " << key << " value: " << value << " depth: " << depth << '\n';
}


void test_rb()
{
    cout << "\nRB\n";
    IntCompare cmp;
    AC<int, int>* tra = new RB<int, int>(&cmp);
    for (int i = 0; i < 36; i += 4)
    {

        tra->insert(i, i * i);
        cout << "\n\ninfix\n\n";
        (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    }
    tra->insert(13, 243);
    tra->insert(10, 34);
    
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    tra->remove(20);
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    tra->remove(10);
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    tra->remove(8);
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    tra->remove(0);
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    delete tra;
}

void test_avl()
{
    cout << "\nAVL\n";
    IntCompare cmp;
    AC<int, int>* tra = new AVL<int, int>(&cmp);
    for (int i = 0; i < 36; i += 4)
    {
      
        tra->insert(i, i * i);
        cout << "\n\ninfix\n\n";
        tra->infix_pass(print_tree);
    }
    tra->insert(13, 243);
    tra->insert(10, 34);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    //tra->insert(30, 20);
    tra->remove(20);
    tra->remove(10);
    tra->remove(8);
    tra->remove(0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    tra->insert(14, 9);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    delete tra;
}

void test_bs()
{
    cout << "\nBS\n";
    IntCompare cmp;
    AC<int, int>* tra = new BS<int, int>(&cmp);
    for (int i = 0; i < 36; i += 4)
    {

        tra->insert(i, i * i);
    }
    tra->insert(13, 243);
    tra->insert(10, 34);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    //tra->insert(30, 20);
    tra->remove(13);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    delete tra;
}

void test_splay()
{
    cout << "\nSplay1" << endl;
    IntCompare cmp;
    AC<int, int>* tra = new Splay<int, int>(&cmp);
    for (int i = 0; i < 36; i += 4)
    {
        int pows = 1;
        for (int j = 0; j < i; j++)
            pows *= -1;
        tra->insert(i * pows, i * i);
        cout << "\n\ninfix\n\n";
        tra->infix_pass(print_tree);
    }
    tra->insert(13, 243);
    tra->insert(10, 34);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    //tra->insert(30, 20);
    tra->remove(13);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    delete tra;
}

void test_splay2()
{
    cout << "\nSplay1" << endl;
    IntCompare cmp;
    AC<int, int>* tra = new Splay<int, int>(&cmp);

    tra->insert(8, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(4, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(2, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(12, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(3, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->find(4);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(20, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(28, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->insert(26, 0);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->find(8);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    tra->remove(28);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    tra->remove(12);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    tra->remove(8);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);

    delete tra;
}

void test_rb2()
{
    cout << "\nRB\n";
    vector<int> keys = { 4, 2, 5, 12, 8, 7, 13, 3, 1, 6, 9, 15, 11 };
    vector<int> keys1 = { 8, 9, 15, 11, 2, 13, 6, 7, 4, 1, 3, 12, 5 };
    IntCompare cmp;
    AC<int, int>* tra = new RB<int, int>(&cmp);
    for (int i = 0; i < keys.size(); i++)
    {
        tra->insert(keys[i], 0);
    }
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    for (int i = 0; i < keys.size(); i++)
    {
        tra->remove(keys[keys.size() - 1 - i]);
        cout << "\n\ninfix\n\n";
        (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    }
    /*for (int i = 0; i < keys1.size(); i++)
    {
        tra->remove(keys1[i]);
        cout << "\n\ninfix\n\n";
        (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();
    }*/
    cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(tra))->print_colorfull_tree();

}

void test_rb1()
{
    cout << "\nAVL\n";
    IntCompare cmp;
    AC<int, int>* tra = new RB<int, int>(&cmp);
    tra->insert(4, 0);

    tra->remove(4);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    delete tra;
}

void test_rb_mull()
{
    cout << "\nAVL\n";
    IntCompare cmp;
    AC<int, int>* tra = new RB<int, int>(&cmp);

    for (int i = 0; i < 200000; i++)
    {
        tra->insert(i, i);
    }

    for (int i = 0; i < 200000; i++)
    {
        tra->remove(i);
    }
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    delete tra;
}

int main()
{
    try
    {
        test_rb();
        test_rb2();
        test_rb_mull();
        test_avl();
        test_bs();
        test_splay();
        test_splay2();
    }
    catch (TreeException exc)
    {
        cout << exc.what() << endl;
    }
}
