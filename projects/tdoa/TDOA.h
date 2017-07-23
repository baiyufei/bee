#pragma once
#include <vector>
struct Coodinate
{
    double x;
    double y;
    double z;
};

class TDOA
{
public:
    TDOA();
    ~TDOA();
    Coodinate caculate(double t[5]);
    void simulate(double x, double y, double z);
private:
    Coodinate anchors_[5] = { { 0, 0, 0 },{ 100, 0, 0 },{ 100, 100, 1 },{ 0, 100, 0 },{ -100, 100, 0 } };
    double t_[5];
    double a_[3][3];
    double b_[3];
    const double v_ = 300;
    void build_coefficient(int i);
};
