#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
//ifstream cin("x.txt");
//ofstream cout("x.out");
//ios_base::sync_with_stdio(false);

struct Point {
    int x,y;
    Point(){
        this->x = this->y = 0;
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
bool isParallel(Point a, Point b, Point c, Point d) {
    return (b.x - a.x) * (d.y-c.y) - (d.x-c.x)*(b.y-a.y) == 0;
}
int orientation(Point &a, Point &b, Point &c) {
    int v = (b.y-a.y)*(c.x-b.x) - (c.y-b.y) * (b.x-a.x);
    if (v == 0) return 0;
    else return v > 0 ? 1 : 2;
}
bool areColinear(Point &a, Point &b, Point &c) {
    return orientation(a, b, c) == 0;
}
int distSq(Point a, Point b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}
bool isRightTriangle(int edges[]) {
    sort(edges, edges + 3);
    return edges[0]+edges[1] == edges[2];
}
bool isEquilateral(int edges[]) {
    return edges[0] == edges[1] && edges[0] == edges[2];
}
bool isIsosceles(int edges[]) {
    return edges[0] == edges[1] || edges[0] == edges[2] || edges[1] == edges[2];
}
bool isRhombus(int e[]) {
    return e[0] == e[1] && e[0] == e[2] && e[0] && e[3];
}
bool isSq(Point d[], int edges[]) {
    if (isRhombus(edges)) {
        return (distSq(d[0],d[2]) == distSq(d[1],d[3]));
    } else return false;
}
bool isPara(int e[], Point d[]) {
    return (2 * (e[0] + e[1]) == distSq(d[0],d[2]) + distSq(d[1],d[3]));
}
bool isRec(int e[], Point d[]) {
    return isPara(e,d) && distSq(d[0], d[2]) == distSq(d[1], d[3]);
}
bool isTrapezoid(int e[], Point d[]) {
    return isParallel(d[0],d[1],d[2],d[3]) || isParallel(d[1],d[2],d[0],d[3]);
}
void findTriangle(Point dots[]) {
    int a = distSq(dots[0], dots[1]);
    int b = distSq(dots[1], dots[2]);
    int c = distSq(dots[0], dots[2]);
    int edges[] = {a,b,c};

    cout << "Trougao";
    bool hypenUsed = false;
    if (isEquilateral(edges)) {
        cout << " - Jednakokraki, Jednakostranicni";
    } else {
        bool isR = isRightTriangle(edges);
        bool isEq = isIsosceles(edges);
        if (isR && isEq) {
            cout << " - Jednakokraki, Pravougli";
        } else if (isR) {
            cout << " - Pravougli";
        } else if (isEq) {
            cout << " - Jednakokraki";
        }
    }
    cout << "\n";
}
void findQuadrilateral(Point dots[]) {
    int a = distSq(dots[0], dots[1]);
    int b = distSq(dots[1], dots[2]);
    int c = distSq(dots[2], dots[3]);
    int d = distSq(dots[0], dots[3]);
    int edges[] = {a,b,c,d};
    if (isSq(dots,edges)) {
        cout << "Cetvorougao - Paralelogram, Romb, Trapez, Pravougaonik, Kvadrat\n";
    } else if (isRhombus(edges)) {
        cout << "Cetvorougao - Paralelogram, Romb, Trapez\n";
    } else if (isPara(edges,dots)) {
        if (isRec(edges,dots)) {
            cout << "Cetvorougao - Paralelogram, Trapez, Pravougaonik\n";
        } else {
            cout << "Cetvorougao - Paralelogram, Trapez\n";
        }
    } else if (isTrapezoid(edges,dots)) {
        cout << "Cetvorougao - Trapez\n";
    } else cout << "Cetvorougao\n";

}

void findShape() {
    int n;
    cin >> n;
    int x,y;
    Point dots[15];
    int numberOfPoints = 2;
    for (int i = 0; i < 2; i++) {

        cin >> x >> y;
        dots[i] = Point(x,y);
    }
    for (int i = 2; i < n; i++) {
        cin >> x >> y;
        Point newPoint(x,y);
        if (areColinear(dots[numberOfPoints-2], dots[numberOfPoints-1], newPoint)){
            dots[numberOfPoints-1] = newPoint;
        } else {
            dots[numberOfPoints++] = newPoint;
        }
    }
    if (numberOfPoints > 2 && areColinear(dots[numberOfPoints-2],dots[numberOfPoints-1],dots[0])){ // ako su kolinearne  predposlednja,poslednja i prva izbaci poslednju
        numberOfPoints--;
    }
    if (numberOfPoints > 2 && areColinear(dots[numberOfPoints-1],dots[0],dots[1])){ //ako su kolinearne poslednja prva i druga
        for (int i = 1; i < numberOfPoints; i++) {
            dots[i-1] = dots[i];
        }
        numberOfPoints--;
    }
    if (numberOfPoints == 2) cout << "Duz\n";
    else if (numberOfPoints == 3) findTriangle(dots);
    else if (numberOfPoints == 4) findQuadrilateral(dots);
    else cout << "Ostalo\n";
}


int main() {


    int t;
    int n;
    cin >> t;
    while (t--) {
        findShape();
    }

    return 0;
}
