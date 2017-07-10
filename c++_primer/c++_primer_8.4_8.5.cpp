#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int filewords(string path, vector<string>& words)
{
    ifstream in;
    in.open(path.c_str());
    if (!in) {
        cout << "open file error" << endl;
        return -1;
    }
    string temp;
    while (in >> temp) {
        words.push_back(temp);
    }
    return 0;
}

int filelines(string path, vector<string> &lines)
{
    ifstream in(path.c_str(), ios::in);
    if (!in) {
        cout << "open file error" << endl;
        return -1;
    }
    string temp;
    while(getline(in, temp)) {
        lines.push_back(temp);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }
    string path(argv[1]);
    vector<string> lines;
    // int ret = filewords(path, lines);
    int ret = filelines(path, lines);
    if (ret == 0) {
        for (auto iter = lines.begin(); iter != lines.end(); iter++) {
            cout << *iter << endl;
        }
    }
    return 0;
}

