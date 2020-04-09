#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct point {
    double x, y;
    point() : x(0), y(0) {}
    point(const double &x, const double &y) : x(x), y(y) {}
};

struct color {
    double r, g, b;

    color() : r(0), g(0), b(0) {}
    color(const double &v) : r(v), g(v), b(v) {}
    color(const double &r, const double &g, const double &b) : r(r), g(g), b(b) {}

    void normalize() {
        r = int(255 * min(1., max(0., r)));
        g = int(255 * min(1., max(0., g)));
        b = int(255 * min(1., max(0., b)));
    }
};

struct rect {
    point p;
    double s;    // side size 
    color c;

    rect() : p(point()), s(0), c({}) {}
    rect(const point &p, const double &s) : p(p), s(s), c({}) {}
    rect(const point &p, const double &s, const color &c) : p(p), s(s), c(c) {}
};

ostream &operator<<(ostream &out, const rect& r) {
    out << "<rect x=\"" << r.p.x << "\" y=\"" << r.p.y << "\" "
            "width=\"" << r.s << "\" height=\"" << r.s << "\" "
            "fill=\"rgb(" << r.c.r << ", " << r.c.g << ", " << r.c.b << ")\" />";
    return out;
}

vector<rect> rects;
double size;
int depth;

// point, side size, color
void draw(const point &p, const double &s, const int &d) {
    if (d < 1) return;

    //rects.push_back(rect({p.x + s/3, p.y + s/3}, s/3, color(1. * d / depth)));
    rects.push_back(rect({p.x + s/3, p.y + s/3}, s/3, color(pow(2., -d + 1))));

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (x != 1 || y != 1) {
                draw({p.x + x*s/3, p.y + y*s/3}, s/3, d - 1);
            }
        }
    }
}

int main() {
    // input
    // size = 1000;
    // depth = 6;
    cout << "Enter a size of square (float): "; cin >> size;
    cout << "Enter a drawing depth (int): "; cin >> depth;

    // render carpet
    rects.push_back(rect({0, 0}, size, {0}));
    draw({0, 0}, size, depth);

    // write carpet to file
    ofstream fout("./out.svg");

    fout << "<svg width=\"" << size << "\" height=\"" << size << "\">";
    for (rect &r : rects) {
        r.c.normalize();
        fout << "    " << r << '\n';
    }
    fout << "</svg>";

    fout.close();
    cout << "Result has been saved to file \"out.svg\".\n";

    return 0;
}
