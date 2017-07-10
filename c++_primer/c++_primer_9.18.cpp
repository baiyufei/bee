#include <iostream>
#include <list>

using namespace std;

int main()
{
    string s;
    list<string> record;
    while (cin >> s) {
        record.push_back(s);
    }
    for (auto iter = record.cbegin(); iter != record.cend(); iter++) {
        cout << *iter << endl;
    }

    return 0;
}
