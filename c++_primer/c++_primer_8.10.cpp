#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    fstream f(argv[1], ios::in);
    if (!f) {
        return -1;
    }
    vector<string> lines;
    string s;
    while (getline(f, s)) {
        lines.push_back(s);
    }
    for (auto iter = lines.begin(); iter != lines.end(); iter++) {
        stringstream sstr(*iter);
        string word;
        while (sstr >> word) {
            cout << word << endl;
        }
    }

    return 0;
}
