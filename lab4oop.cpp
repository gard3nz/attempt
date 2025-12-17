#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

template <typename T>
bool find2d(vector<vector<T>> &v, T goal){
    for (int i=0;i<v.size();i++){
        for (int j=0;j<v[i].size();j++)
        if (v[i][j] == goal) return true;
    }
    return false;
}

template <typename T>
class Complex{
    public:
        T dp, mp;
        Complex(T d=0, T m=0):dp(d), mp(m){};
        void display(){
            cout << dp << " " << mp << "i\n";
        }
        Complex operator+(Complex& other){
            return Complex(dp + other.dp, mp + other.mp);
        }
        Complex operator/(int n){
            return Complex(dp/n, mp/n);
        }
};
template <typename T>
T getavg(vector<T>&v){
    T sum = v[0];
    for (int i=1;i<v.size();i++){
        sum = sum + v[i];
    }
    return sum/v.size();
}




template <typename T>
class Vector3d{
    public:
        T x,y,z;
        Vector3d(T xx, T yy, T zz):x(xx), y(yy), z(zz){};
        Vector3d operator+(Vector3d& vd){
            return Vector3d (x+vd.x, y+vd.y, z+vd.z);
        }
        Vector3d operator-(Vector3d& vd){
            return Vector3d (x-vd.x, y-vd.y, z-vd.z);
        }
        Vector3d operator*(T scal){
            return Vector3d (x*scal, y*scal, z*scal);
        }

        Vector3d vec(Vector3d& vd){
            return Vector3d(y*vd.z-z*vd.y, z*vd.x-x*vd.z, x*vd.y-y*vd.z);
        }
        void display() {
            cout << "x: " << x << " y: " << y << " z: " << z << endl;
        }
};

int main() {
    Vector3d v1(1, 0, 0), v2(0, 1, 0);
    Vector3d v3 = v1 + v2;
    v3.display();
    Vector3d v5 = v1*5;
    v5.display();
    Vector3d v4 = v1.vec(v2);
    v4.display();
    
    // vector<vector<int>> vv = {{1, 2}, {3, 4}}; cout <<  "Есть ли 3: " << find2d(vv, 3); 
    // cout <<  "Есть ли 5: " << find2d(vv, 5); 
    
    // //2
    // vector<int> vi = {1, 2, 3};
    // vector<double> vd = {1.5, 2.5, 3.5};
    // vector<Complex<int>> vc = {Complex(2, 4), Complex(4, 8)};
    // cout << "Avg int: " << getavg(vi) << endl;
    // cout << "Avg double: " << getavg(vd) << endl;
    // cout << "Avg Complex: "; getavg(vc).display();

    // //3
    Vector3d v1(1, 0, 0), v2(0, 1, 0);
    Vector3d v3 = v1 + v2;
    v3.display();
    Vector3d v5 = v1*5;
    v5.display();
    Vector3d v4 = v1.vec(v2);
    v4.display();

    // return 0;
    
    
    
}
        // T scalar(Vector3d& vd){
        //     return Vector3d (x*vd.x, y*vd.y, z*vd.z);
        // }
        
        // cout << "scalar: " << v1.scalar(v2) << endl;
