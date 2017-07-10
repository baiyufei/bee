#include <iostream>
#include <string>

using namespace std;

istream& foo(istream& in)
{
    string s;
    while (in >> s) {
        cout << s << endl;
    }
    in.clear();
    return in;
}

int main()
{
    foo(cin);
    return 0;
}
