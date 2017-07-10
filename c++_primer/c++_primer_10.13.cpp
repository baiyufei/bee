#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool isLessThan5(string& s)
{
    return s.length() < 5 ? true : false;
}

int main()
{
    vector<string> words = { "this", "is", "lalalla", "who", "wewwwww", "he" };
    auto iter = partition(words.begin(), words.end(), isLessThan5);
    while (iter!= words.end()) {
        cout << *iter << endl;
        iter++;
    }

    return 0;
}
