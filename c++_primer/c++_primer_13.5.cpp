#ifndef _HasPtr_
#define _HasPtr_

#include <string>
#include <iostream>

class HasPrt {
public:
    HasPrt(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) {}
    HasPrt(const HasPrt &);
    void show();
private:
    std::string *ps;
    int i;
};

#endif

HasPrt::HasPrt(const HasPrt& h)
{
    ps = new std::string(*(h.ps));
    i = h.i;
}

void HasPrt::show()
{
    std::cout << *ps << std::endl;
}

int main()
{
    HasPrt *hp = new HasPrt("test");
    HasPrt copy_hp = *hp;
    delete hp;
    copy_hp.show();
    return 0;
}
