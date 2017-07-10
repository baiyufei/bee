#include <iostream>
#include <list>
#include <deque>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    list<int> nums;
    deque<int> evens, odds;

    for (int i = 1; i < argc; i++) {
        string temp(argv[i]);
        int num = stoi(temp);
        nums.push_back(num);
    }

    for (auto iter = nums.cbegin(); iter != nums.cend(); iter++) {
        if (*iter % 2) {
            odds.push_back(*iter);
        }
        else {
            evens.push_back(*iter);
        }
    }

    for (auto iter = odds.cbegin(); iter != odds.cend(); iter++) {
        cout << *iter << endl;
    }

    return 0;
}
