#include <iostream>
#include <vector>

int main()
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
    std::vector<int> odds;
    for (int i = 0; i < sizeof(ia) / sizeof(int); ++i) {
        odds.push_back(ia[i]);
    }

    auto iter = odds.begin();

    while (iter != odds.end()) {
        if (*iter % 2) {
            iter = odds.erase(iter);
            continue;
        }
        iter++;
    }

    for (auto iter = odds.begin(); iter != odds.end(); iter++) {
        std::cout << *iter << std::endl;
    }
    return 0;
}
