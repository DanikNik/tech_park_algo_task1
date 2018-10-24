#include <iostream>

using namespace std;


struct Point {
    int x;
    int y;
};


int main() {
    int n = 0;
    cin >> n;
    Point *coords = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> coords[i].x >> coords[i].y;
    }

    double  S = 0;
    for (int i = 0; i < n; ++i) {
        S += (coords[i].x + coords[(i + 1) % n].x) * (coords[i].y - coords[(i + 1) % n].y);
    }
    S *= 0.5;

    cout << S << endl;

    delete[] coords;
    return 0;
}