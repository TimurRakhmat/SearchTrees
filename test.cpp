#include"test.h"

//template <class T1, class T2>
//void print_tree(const T1& key, const T2& value, int depth) {
//    for (int i = 0; i < depth; i++) {
//        cout << '\t';
//    }
//    cout << key << endl;
//}
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
    AC<int, int>* tra = new AVL<int, int>(&cmp);

    for (int i = 0; i < 50; i++)
    {
        tra->insert(i, i);
    }

    tra->infix_pass(print_nodes);
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    

    AC<int, int>* trat = new B23<int, int>(&cmp);
    *trat = *tra;
    
    trat->infix_pass(print_nodes);
    
    cout << "\n\ninfix\n\n";
    trat->infix_pass(print_tree);
    /*cout << "\n\ninfix\n\n";
    (static_cast<RB<int, int>*>(trat))->print_colorfull_tree();*/

    delete tra;
    delete trat;
}

void test_b23()
{
    cout << "\nB2-3\n";
    IntCompare cmp;
    AC<int, int>* tra = new B23<int, int>(&cmp);
    //vector<int>keys = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 5, 15, 25, 8 };
    vector<int>keys = { 63, 31, 15, 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14, 23};

    for (int i = 0; i < keys.size(); i++)
    {
        cout << "\n\ninfix" << keys[i] << "\n\n";
        if (keys[i] == 23)
            cout << "";
        tra->insert(keys[i], 0);
        
        tra->infix_pass(print_tree);
    }
    cout << "\n\ninfix\n\n";
    tra->infix_pass(print_tree);
    vector<int> keys1 = { 5, 8, 10, 30, 15 };
    for (int i = 0; i < keys.size(); i++)
    {
        cout << "\n\ninfix" << keys[i] << "\n\n";
        if (keys[i] == 25)
            cout << "";
        tra->remove(keys[i]);
        
        tra->infix_pass(print_tree);
    }

    delete tra;
}