/*
	Name   : Chalearm Saelim
        Email  : chalearm90@gmail.com
        Purpose: to try to use the map library : map<int,int> case
        
        Compile: g++ mapTest.cpp -o mapTest
        run    : ./mapTest

*/
#include <iostream>
#include <iterator>
#include <map>

using namespace std;
int main(int argc,char  **argv)
{
    map<int,int> mapInt1;

    mapInt1.insert(pair<int,int>(1,40));
    mapInt1.insert(pair<int,int>(2,30));
    mapInt1.insert(pair<int,int>(3,20));
    mapInt1.insert(pair<int,int>(4,60));
    mapInt1.insert(pair<int,int>(5,50));

    map<int,int>::iterator itr;
    cout << "\nThe map mapInt1 is : \n";
    cout <<"\tKey\tElement\n";
    for (itr = mapInt1.begin() ; itr != mapInt1.end(); ++itr)
    {
        cout << '\t' << itr->first;
        cout << '\t' << itr->second << '\n';
    }
    cout << endl;

    map<int,int> mapInt2(mapInt1.begin(),mapInt1.end());
    cout << "\nThe map mapInt2 after"
         << " assign from mapInt1 is : \n";
    cout << "\tKey\tELement\n";
    for (itr = mapInt2.begin() ; itr != mapInt2.end(); ++itr)
    {
        cout << '\t' << itr->first;
        cout << '\t' << itr->second << '\n';
    }
    cout << endl;
    // remove all elements up to
    // element with key=4 in mapInt2
    cout << "\nmapInt2 after remove of"
         << "elements less than key=3 : \n";
    cout << "\tKey\tElement\n";
    mapInt2.erase(mapInt2.begin(), mapInt2.find(3));
    for (itr = mapInt2.begin(); itr != mapInt2.end(); ++itr)
    {
        cout << '\t' << itr->first;
        cout << '\t' << itr->second << '\n';
    }

    return 0;
}
