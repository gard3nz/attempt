#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

//1
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

//2
class Calculator {
    public:
        double addition(double f, double s) { return f + s; }
        double subtraction(double f, double s) { return f - s; }
        double multiplication(double f, double s) { return f * s; }
        double division(double f, double s) { return f/s; };

};

//3
class Student{
    public:
        string name; int age; double avgmark;
        Student(string n, int a, double avg): name(n), age(a), avgmark(avg){};
        void display(){
            cout << "name: " << name << ", age: " << age << ", avg mark: " << avgmark << endl;
        }
        void read(){
            cin >> name >> age >> avgmark;
        }
};

class StudentManager {
public:
    vector<Student> students;
    void addstudent(Student s) {
        students.push_back(s);
    }
    void removestudent(int i){
        students.erase(students.begin() + i);
    }
    void display(){
        for (int i=0;i<students.size();i++){
            students[i].display();
        }
    }
    void read() {
        Student news("",0,0);
        news.read();
        addstudent(news);
    }
};
//4
class Book {
public:
    string title; string author; int year;
    Book(string t, string a, int y) : title(t), author(a), year(y) {};

    void display() {
        cout << "[" << year << "] " << title << " author: " << author << endl;
    }
    void read() {
        cin >> title >> author >> year;
    }
};

bool compareBooks(const Book &a, const Book &b) {
    return a.year < b.year;
}

//5
class BankAccount {
public:
    string id; double balance;
    BankAccount(string id_, double bal) : id(id_), balance(bal) {};

    void deposit(double amount) { balance += amount; }
    void undeposit(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }else {cout <<"Не хватает денег на балансе";}
    }
    void transfer(BankAccount &other, double amount) {
        undeposit(amount);
        other.deposit(amount);
    }
    void display() {
        cout << "Account: " << id << " | Balance: " << balance << endl;
    }
    void read() {
        cin >> id >> balance;
    }
};

int main() {
    BankAccount a1("001", 1000), a2("002", 500);
    a1.transfer(a2, 300);
    a1.display(); a2.display();
    
    // Point p(10, 10); p.move(5, 5); p.display();
    
    // Calculator c; cout << c.multiplication(5, 4) << endl; 
    // cout << c.division(10,2) << endl;


    // StudentManager sm;
    // sm.addstudent(Student("Ivan", 20, 4.5));
    // sm.addstudent(Student("Vlad", 19, 5));
    // sm.display();

    // vector<Book> books;
    // books.push_back(Book("C++", "Stroustrup", 1985));
    // books.push_back(Book("Hobbit", "Tolkien", 1937));
    // books.push_back(Book("Azbuka", "Tolstoy", 1964));
    // sort(books.begin(), books.end(), compareBooks);
    // for (auto &b : books) b.display();
    
}
