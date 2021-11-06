#include<iostream>
#include "test.h"
#include <map>
#include <set>
#include <vector>

using namespace std;


int main()
{
    try
    {
        /*test_b23();
        test_rb();
        test_rb2();
        test_rb_mull();
        test_avl();
        test_bs();
        test_splay();
        test_splay2();*/

        //test_rb_mull();
    }
    catch (TreeException exc)
    {
        cout << exc.what() << endl;
    }

    try
    {
        PointCompare pcm;
        SalaryCmp cmpS;
        NameCmp cmpN;
        CountCmp cmpC;
        CountAndSalaryCmp cmpCAS;
        NameAndAddressAndCountCmp cmpNAC;
        ALLCmp cmpALL;


        Departament d1(4, "devops", 3000, 25, "MoscowCity center", 6);
        Departament d2(5, "marketing", 2000, 15, "MoscowCity center", 7);
        Departament d3(6, "frontend", 450, -15, "MoscowCity center", 9);

        vector <string> m1 = { "Tom", "Bob", "Mark", "Tony" };
        vector <string> m2 = { "Jhon", "Mob", "halk", "Danil", "Alan" };
        vector <string> m3 = { "Sergey", "Anton", "Kirill", "Frank", "Karl", "Roma" };

        Relation<Departament*, vector <string>> r;

        r.addIndex(Relation<Departament*, vector <string>>::B23T, &cmpS, "salary");
        r.insert(&d1, m1);
        r.addIndex(Relation<Departament*, vector <string>>::AVLT, &cmpCAS, "salary,count");
        r.addIndex(Relation<Departament*, vector <string>>::SPLAYT, &cmpALL, "name,count,salary,floor,address,time");

        
        //r.insert(&d2, m2);
        //r.insert(&d3, m3);

        vector <string>* m;
        m = &r.find(&d3, "count,salary");

        cout << "workers on the 3rd Departament:" << endl;
        for (auto st : *m)
            cout << st << endl;
        r.remove(&d3);
    }
    catch (TreeException exc)
    {
        cout << exc.what() << endl;
    }
    catch (Relation<int, int>::Exception exc)
    {
        cout << exc.what() << endl;
    }
}
