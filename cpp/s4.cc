#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool icompare_pred(unsigned char a, unsigned char b) 
{
    return tolower(a) == tolower(b);
}

struct cmp_key
{
    bool operator()( const string& lhs, const string& rhs ) const 
    {
        int i = 0;
        for (; i < lhs.size() && i < rhs.size(); i++) {
            char l = tolower(lhs[i]);
            char r = tolower(rhs[i]);
            if (l < r)
                return true;
            else if (l > r)
                return false;
        }
        if (i != rhs.size())
            return true;
        return false;        
    }
};

int main()
{
    map<string, int, cmp_key> m;
    m[string("ABC")] = 10;
    m[string("fjif0230923")] = 1;
    cout << m[string("abc")] << endl << m[string("fjiF0230923")] << endl;
    return 0;
}