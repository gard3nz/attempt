#include <bits/stdc++.h>
using namespace std;

//1
class Room{
public:
    double l, w, h;
    Room(double l, double w, double h) : l(l), w(w), h(h) {}
    double area() { return 2 * h * (l + w); } 
};

class OfficeSpace : public Room {
public:
    int n; double rashod;
    OfficeSpace(double l, double w, double h, int n, double r) : Room(l, w, h), n(n), rashod(r) {}
    double total() { return area() * n * rashod; }
};

//2
class Vector{
public:
    double x1, y1, x2, y2;
    Vector(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

class TwoVectors : public Vector {
public:
    double a, b;
    TwoVectors(double x1, double y1, double x2, double y2, double a, double b)
    : Vector(x1, y1, x2, y2), a(a), b(b){}
    double area() {
        double vx = x2 - x1;double vy = y2 - y1;
        return abs(vx * (-b) - vy * a);
    }
};

//3
class SalesData{
public:
    vector<double> s;
    void read(int n) {
        for(int i=0; i<n; i++) {
            double x; cin >> x; s.push_back(x); 
        }
    }
    double sum() {
        double res = 0;
        for(double x : s) res += x;
        return res;
    }
};

class AnalyzedSalesData : public SalesData {
public:
    double max_s() {
        return *max_element(s.begin(), s.end());
    }
};

//4
class Matrix{
public:
    int r, c;
    vector<vector<double>> m;
    Matrix(int r, int c) : r(r), c(c), m(r, vector<double>(c)) {}
    void read() { for(int i=0; i<r; i++) for(int j=0; j<c; j++) cin >> m[i][j]; }
    void display() {
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) cout << m[i][j] << " ";
            cout << endl;
        }
    }
};
class SquareMatrix : public Matrix{
public:
    SquareMatrix(int n) : Matrix(n, n) {}
    double det() {
        if(r == 1) return m[0][0];
        if(r == 2) return m[0][0]*m[1][1] - m[0][1]*m[1][0];
    }
};

//5
class SubstringSearcher{
public:
    string s;
    SubstringSearcher(string s) : s(s) {}
    int find_sub(string sub) { return s.find(sub); }
};

class UniqueCharacterCounter{
public:
    string s;
    UniqueCharacterCounter(string s) : s(s) {}
    int count_u(){
        set<char> st(s.begin(), s.end());
        return st.size();
    }
};

class StringProcessor : public SubstringSearcher, public UniqueCharacterCounter {
public:
    StringProcessor(string s) : SubstringSearcher(s), UniqueCharacterCounter(s){}
    void display(){ cout << SubstringSearcher::s << endl; }
};

int main() {
    // //1
    // OfficeSpace off(5, 4, 3, 2, 0.5);
    // cout << off.total() << endl;
    
    // //2
    // TwoVectors tv(0, 0, 3, 0, 0, 4);
    // cout << tv.area() << endl;
    
    // //3
    // AnalyzedSalesData asd;
    // asd.read(3);
    // cout << asd.sum() << " " << asd.max_s() << endl;
    
    // // 4
    // SquareMatrix sm(2);
    // sm.read();
    // sm.display();
    // cout << sm.det() << endl;
    
    // // 5
    // StringProcessor sp("hello world");
    // cout << sp.find_sub("lo") << " " << sp.count_u() << endl;
}
