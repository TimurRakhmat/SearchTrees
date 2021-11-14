#include<iostream>
#include "test.h"
#include "Relation.h"
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

        //test_rb();

    }
    catch (AC<int, int>::TreeException exc)
    {
        cout << exc.what() << " bad key: " << exc.key << endl;
    }

    try
    {
        Ñompare<Departament*>* myCmp = new SalaryCmp;
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
        Departament d4(19, "backend", 3500, 12, "LahtaCity center", 11);
        Departament d5(3, "gameDev", 2200, 11, "LahtaCity center", 4);
        Departament d6(8, "DataBase", 3450, 16, "LahtaCity center", 10);

        vector <string> m1 = { "Tom", "Bob", "Mark", "Tony" };
        vector <string> m2 = { "Jhon", "Mob", "halk", "Danil", "Alan" };
        vector <string> m3 = { "Sergey", "Anton", "Kirill", "Frank", "Karl", "Roma" };
        vector <string> m4 = { "Tom", "Bob", "Mark", "Tony, Gats" };
        vector <string> m5 = { "Gats", "Griffith", "Anton", "Kirill", "Karl", "Roma" };
        vector <string> m6 = { "Sergey", "Anton", "Kirill", "Frank", "Karl", "Roma" };

        Relation<Departament*, vector <string>> r;

        r.addIndex(Relation<Departament*, vector <string>>::B23T, &cmpS, "salary");
        r.insert(&d1, m1);
        r.addIndex(Relation<Departament*, vector <string>>::AVLT, &cmpCAS, "salary,count")\
            .addIndex(Relation<Departament*, vector <string>>::SPLAYT, &cmpALL, "name, count, salary, floor, address, time")\
            .insert(&d2, m2).insert(&d3, m3).insert(&d4, m4).insert(&d5, m5).insert(&d6, m6).remove(&d4);

        vector <string>* m;
        m = &r.find(&d5, "count ,salary");

        cout << "workers on the 3rd Departament:" << endl;
        for (auto st : *m)
            cout << st << endl;
        r.remove(&d3);
    }
    catch (AC<Departament*, vector <string>>::TreeException exc)
    {
        cout << exc.what() << endl;
    }
    catch (Relation<Departament*, vector <string>>::RealationException exc)
    {
        cout << exc.what() << endl;
    }
}
