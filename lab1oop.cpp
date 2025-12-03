#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

class Point{
    public:
        int x = 0, y = 0;
        void move(int xx, int yy){
            x+=xx; y+=yy;
        }
        Point(int xx, int yy):x(xx), y(yy){};
        void display(){
            cout << "x: " << x << "\ny: " << y << endl;
        }
        void read(){
            int a,b; cin >> a; cin >> b;
            x+=a;y+=b;
        }
};

class Calculator{
    public:
        double addition(double f, double s) { return f+s; };
        double subtraction(double f, double s) { return f-s; };
        double multiplication(double f, double s) { return f*s; };
        double division(double f, double s) { return f/s; };
};


class Student{
    public:
        string name; int age; double avgmark;
        Student(string n, int a, double avg): name(n), age(a), avgmark(avg){};
        void display(){
            cout << "name: " << name << "\nage: " << age << "\navg mark: " << avgmark << endl;
        }
        void read(){
            string n;int a;double avg;
            cin >> n; cin >> a;cin >> avg;
        }
};

class StudentManager{
    public:
        vector<Student>students;
        void addstudent(Student s){
            students.push_back(s);
        }
        void removestudent(int i){
            students.erase(students.begin() + index);
        }
        void Display(){
            for (int in=0;in<students.size();in++){
                students[i].display();
            }
        }
};

int main() {
	// your code goes here
    Point dot(13, 15); dot.move(3, 7); dot.display();
    Calculator c; cout << c.addition(15, 8);
    
    
}
