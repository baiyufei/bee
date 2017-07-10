#include <iostream>

using namespace std;

int main()
{
    auto f = [](int a, int b){return a + b;};
    cout << f(1, 2) << endl;
    int a = 1;
    cout << ([a](int b){return a + b;})(4) << endl;

    a = 10;
    auto g = [&a]()->bool{a--; return a > 0;};
    while (g()) {
        cout << a << endl;
    }
    return 0;
}
