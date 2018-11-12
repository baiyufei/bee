#include "TDOA.h"
#include <math.h>
#include <stdio.h>

double caculate_det(const double a[3][3])
{
    double ret = 0;
    ret += a[0][0] * a[1][1] * a[2][2];
    ret -= a[0][0] * a[1][2] * a[2][1];
    ret -= a[0][1] * a[1][0] * a[2][2];
    ret += a[0][1] * a[1][2] * a[2][0];
    ret += a[0][2] * a[1][0] * a[2][1];
    ret -= a[0][2] * a[1][1] * a[2][0];
    return ret;
}

Coodinate solve_3v_equation(double a[3][3], const double b[3])
{

    double d[4];
    d[3] = caculate_det(a);
    double temp[3];

    for (int i = 0; i < 3; i++) {
        if (i != 0) {
            for (int j = 0; j < 3; j++) {
                a[j][i - 1] = temp[j];
            }
        }
        for (int j = 0; j < 3; j++) {
            temp[j] = a[j][i];
        }
        for (int j = 0; j < 3; j++) {
            a[j][i] = b[j];
        }
        d[i] = caculate_det(a);
    }
    Coodinate ret;
    ret.x = d[0] / d[3];
    ret.y = d[1] / d[3];
    ret.z = d[2] / d[3];
    return ret;
}

TDOA::TDOA()
{

}


TDOA::~TDOA()
{
}

Coodinate TDOA::caculate(double t[5])
{
    for (int i = 0; i < 5; i++) {
        t_[i] = t[i];
    }
    for (int i = 0; i < 3; i++) {
        build_coefficient(i);
    }

    Coodinate ret;
    ret = solve_3v_equation(a_, b_);
    return ret;
}

void TDOA::build_coefficient(int i)
{
    const Coodinate& am = anchors_[i + 2];
    const Coodinate& a1 = anchors_[1];

    double dm = v_* t_[i + 2];
    double d1 = v_* t_[1];

    a_[i][0] = 2 * am.x / dm - 2 * a1.x / d1;
    a_[i][1] = 2 * am.y / dm - 2 * a1.y / d1;
    a_[i][2] = 2 * am.z / dm - 2 * a1.z / d1;
    double pm = ((am.x)*(am.x) + (am.y)*(am.y) + (am.z)*(am.z)) / dm;
    double p1 = ((a1.x)*(a1.x) + (a1.y)*(a1.y) + (a1.z)*(a1.z)) / d1;
    b_[i] = -dm + d1 + pm - p1;
}

double cal_distance(const Coodinate& l, const Coodinate &r)
{
    double t;
    t = pow(l.x - r.x, 2) + pow(l.y - r.y, 2) + pow(l.z - r.z, 2);
    return sqrt(t);
}

void TDOA::simulate(double x, double y, double z)
{
    Coodinate e;
    e.x = x;
    e.y = y;
    e.z = z;

    double d[5];
    double t[5];
    for (int i = 0; i < 5; i++) {
        d[i] = cal_distance(e, anchors_[i]);
        t[i] = (d[i] - d[0]) / v_;
    }

    Coodinate p = { 0,0,0 };
    p = caculate(t);
    printf("实际坐标点 x = %f, y = %f, z = %f\n", e.x, e.y, e.z);
    printf("计算坐标点 x = %f, y = %f, z = %f\n", p.x, p.y, p.z);
}
