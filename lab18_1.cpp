#include<iostream>
using namespace std;

struct Rect{
    double x, y, w, h;
};

double overlap(Rect r1, Rect r2) {
    double x_overlap = max(0.0, min(r1.x + r1.w, r2.x + r2.w) - max(r1.x, r2.x));
    double y_overlap = max(0.0, min(r1.y + r1.h, r2.y + r2.h) - max(r1.y, r2.y));
    return x_overlap * y_overlap;
}